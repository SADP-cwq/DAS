#include "demodulation.h"
#include <QDebug>


Demodulation::Demodulation(QObject *parent)
    : QThread(parent)
    , m_stop(false)
    , newDataAvailable(false)

{

}

Demodulation::~Demodulation()
{
    stop();
    wait();  // 等待线程结束
}

void Demodulation::stop()
{
    QMutexLocker locker(&mutex);
    m_stop = true;
}

void Demodulation::setAlarmPosition(int pos)
{
    QMutexLocker locker(&mutex1);
    alarmPos = pos;
}

void Demodulation::receiveData(const uint8_t* data, int length)
{
    QMutexLocker locker(&mutex);
    // 将接收到的数据存入缓冲区
    buffer.append((const char*)data, length);
    newDataAvailable = true;
}

void Demodulation::run()
{
    // 在参数设置时初始化参考信号
    initializeReferenceSignals();
    initFilters();
    while (!m_stop)
    {
        if (newDataAvailable)
        {
            QByteArray dataToProcess;
            {
                QMutexLocker locker(&mutex);
                dataToProcess = buffer;  // 获取缓冲区数据
                buffer.clear();         // 清空缓冲区
                newDataAvailable = false;
            }

            // 处理数据
            processIQData((const uint8_t*)dataToProcess.constData(), dataToProcess.size());
        }
        else
        {
            // 没有新数据时短暂休眠，避免CPU占用过高
            msleep(10);
        }
    }
}

void Demodulation::initializeReferenceSignals()
{

    refi.clear();
    refi.clear();
    int pos_N = SegmentLen;

    // 时间轴索引
    t_x.resize(pos_N);
    for (int i = 0; i < pos_N; i++) {
        t_x[i] = i + 1;
    }

    // 时间轴
    double t_daq = 1.0 / sampleRate;
    t.resize(pos_N);
    for (int i = 0; i < pos_N; i++) {
        t[i] = t_x[i] * t_daq;  // 逐元素乘法
    }

    // 参考信号
    refi.resize(pos_N);
    refq.resize(pos_N);
    for (int i = 0; i < pos_N; i++) {
        double x = 2 * M_PI * AOMfrequency * t_daq * t_x[i];
        refi[i] = cos(x);
        refq[i] = sin(x);
    }
    qDebug() << "解调开始";

    const int maxRows = 200;

    tempi.resize(pos_N);
    tempq.resize(pos_N);

    // 在循环前确保这些二维数组有足够大小
    volMatrix.resize(maxRows);
    ri.resize(maxRows);
    rq.resize(maxRows);
    aresult.resize(maxRows);
    presult.resize(maxRows);

    for (int i = 0; i < maxRows; i++) {
        volMatrix[i].resize(pos_N);
        ri[i].resize(pos_N);
        rq[i].resize(pos_N);
        aresult[i].resize(pos_N);
        presult[i].resize(pos_N);
    }

}

void Demodulation::processIQData(const uint8_t* data, int size)
{
    // 转换为电压矩阵并归一化到[-1,1]
    const int maxRows = 200;
    int closs = SegmentLen * 2;
    int rowSizeBytes = SegmentLen * sizeof(int16_t);

    // 使用 QVector 定义二维数组
    QVector<QVector<double>> volMatrix(maxRows);

    // 找绝对值最大值并填充电压值
    double maxAbsVal = 0.0;

    for (int row = 0; row < maxRows; ++row) {
        volMatrix[row].resize(closs / 2);
        for (int col = 0; col < closs; col += 2) {
            int16_t value = (static_cast<int16_t>(data[row * rowSizeBytes + col + 1]) << 8) |
                           static_cast<int16_t>(data[row * rowSizeBytes + col]);
            double volt = value;
            volMatrix[row][col / 2] = volt;
            maxAbsVal = std::max(maxAbsVal, std::abs(volt));
        }
    }

    // 归一化到[-1,1]
    if (maxAbsVal == 0) maxAbsVal = 1.0;  // 防止除以0

    for (int row = 0; row < maxRows; ++row) {
        for (int col = 0; col < closs / 2; ++col) {
            volMatrix[row][col] /= maxAbsVal;
        }
    }

    // IQ解调使用预分配缓冲区
    int trace_N = maxRows;
    int pos_N = SegmentLen;

    for (int i = 0; i < trace_N; i++) {
        for (int j = 0; j < pos_N; j++) {
            // 执行乘法并转换为double
            tempi[j] = static_cast<double>(volMatrix[i][j]) * refi[j];
            tempq[j] = static_cast<double>(volMatrix[i][j]) * refq[j];

            // 执行滤波
            ri[i][j] = firFilterI.filter(tempi[j]);
            rq[i][j] = firFilterQ.filter(tempq[j]);
        }
    }
//    qDebug() << "滤波信号：" << ri[10];

//    // 相位正交解调
    for (int j = 0; j < trace_N; j++) {
        for (int i = 0; i < pos_N; i++) {
            aresult[j][i] = sqrt(ri[j][i] * ri[j][i] + rq[j][i] * rq[j][i]);
//            presult[j][i] = atan2(rq[j][i], ri[j][i]);
        }
    }
    QVector<double> varonce = computeStdDev(aresult);
    QVector<double> intensityArray(pos_N);

    // 计算varonce的均值
//    double meanVar = std::accumulate(varonce.begin(), varonce.end(), 0.0) / pos_N;
//    for (int i = 0; i < pos_N; i++) {
//        intensityArray[i] = varonce[i] - meanVar;
//    }
    // 归一化
    double maxVar = *std::max_element(varonce.begin(), varonce.end());
    for (int i = 0; i < pos_N; i++) {
        intensityArray[i] = varonce[i] / maxVar;
    }

    // 设置RMS阈值（例如0.5），标记异常点
    double threshold = 0.5; // 根据论文设置阈值；阈值需要在现场确定(需确定托辊故障时的标准差阈值)
    QVector<int> faultPositions; // 存储异常位置索引

    for (int i = 0; i < pos_N; i++) {
        intensityArray[i] = varonce[i] / maxVar; // 归一化后的强度值
        if (intensityArray[i] > threshold) {
            faultPositions.append(i); // 记录异常点位置
        }
    }

    emit faultPositionsDetected(faultPositions);

    emit processedAmplitudeDataReady(intensityArray);

    // 获取当前报警位置
    int currentAlarmPos;
    {
        QMutexLocker locker(&mutex1);
        currentAlarmPos = alarmPos;
    }

    // 仅处理有效位置的相位
    if (currentAlarmPos >= 0 && currentAlarmPos < pos_N) {
        QVector<double> phases(trace_N);
        for (int j = 0; j < trace_N; j++) {
            double I = ri[j][currentAlarmPos];
            double Q = rq[j][currentAlarmPos];
            phases[j] = atan2(Q, I); // 计算原始相位
        }
        QVector<double> unwrappedPhases = phaseUnwrap(phases); // 解缠绕
        emit phasePhaseDataReady(phases); // 发送数据
    }
}

void Demodulation::initFilters()
{
    // MATLAB fir1(8, 3e3/(250e6/2)) 生成的系数
    // 注意：实际系数应该从MATLAB导出精确值
    double b[] = {0.0181818179550321,0.0488024725909034	,0.122727272591849	,0.196652072920570	,
                  0.227272727883290	,0.196652072920570	,0.122727272591849	,0.0488024725909034	,0.0181818179550321};
    int order = sizeof(b)/sizeof(b[0]) - 1; // 滤波器阶数

    firFilterI.setPara(b, order);
    firFilterQ.setPara(b, order);

    // 重置滤波器状态
    firFilterI.reset();
    firFilterQ.reset();
}

QVector<double> Demodulation::computeStdDev(const QVector<QVector<double> > &matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();
    QVector<double> stdDev(cols, 0.0);

    // 计算每列均值
    QVector<double> means(cols, 0.0);
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            means[j] += matrix[i][j];
        }
        means[j] /= rows;
    }

    // 计算每列标准差
    for (int j = 0; j < cols; j++) {
        double sumSqDiff = 0.0;
        for (int i = 0; i < rows; i++) {
            double diff = matrix[i][j] - means[j];
            sumSqDiff += diff * diff;
        }
        stdDev[j] = sqrt(sumSqDiff / (rows - 1));  // 使用样本标准差
    }

    return stdDev;
}

// 相位解缠绕函数
QVector<double> Demodulation::phaseUnwrap(const QVector<double>& phases) {
    QVector<double> unwrapped(phases.size());
    if (phases.isEmpty()) return unwrapped;
    unwrapped[0] = phases[0];
    for (int i = 1; i < phases.size(); i++) {
        double delta = phases[i] - phases[i-1];
        if (delta > M_PI) {
            unwrapped[i] = unwrapped[i-1] + (delta - 2*M_PI);
        } else if (delta < -M_PI) {
            unwrapped[i] = unwrapped[i-1] + (delta + 2*M_PI);
        } else {
            unwrapped[i] = unwrapped[i-1] + delta;
        }
    }
    return unwrapped;
}
