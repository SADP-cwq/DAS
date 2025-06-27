#ifndef DEMODULATION_H
#define DEMODULATION_H

#define _USE_MATH_DEFINES

#include <QThread>
#include <QMutex>
#include <math.h>
#include <cmath>
#include "FIR.h"

class Demodulation : public QThread
{
    Q_OBJECT

public:
    explicit Demodulation(QObject *parent = nullptr);
    ~Demodulation();

    void stop();  // 停止线程的公共方法

    void setAlarmPosition(int pos); // 设置报警位置

signals:
    void processedAmplitudeDataReady(const QVector<double>& processedData);  // 处理完的数据发送给主线程

    void faultPositionsDetected(const QVector<int>& faultPositions);//异常信号位置
    void phasePhaseDataReady(const QVector<double>& phases);

public slots:
    void receiveData(const uint8_t* data, int length);  // 接收采集线程的数据

protected:
    void run() override;

private:
    bool m_stop;           // 控制线程停止的标志
    QMutex mutex;          // 用于线程安全的互斥锁
    QByteArray buffer;     // 数据缓冲区
    bool newDataAvailable; // 新数据可用标志

    //----Acquisition parameters
    double sampleRate = 250000000;//Sample rate in Hz
    double AOMfrequency = 80e6;
    unsigned int SegmentLen          = 4096;//number of samples per segment
    unsigned int TrigPulseWidth      = 100;//in step of sample clock period in ns；脉宽
    unsigned int TrigPulsePeriod     = 50000;//in step of sample clock period in ns；脉冲周期
    unsigned int TrigPulseFrequency =  1000000000/TrigPulsePeriod; //脉冲频率


    double full_range = 2.47 * 1000;  // 满量程电压(mV)
    double bit_num = 65536;          // 16位ADC (2^16)
    double voltage = static_cast<double>(full_range) / bit_num;

    // Pre-computed values
    QVector<double> t_x;     // 时间轴索引
    QVector<double> t;       // 时间轴
    QVector<double> refi;    // I通道参考信号
    QVector<double> refq;    // Q通道参考信号
    QVector<QVector<double>> volMatrix;  // 预分配电压矩阵
    QVector<QVector<double>> ri;         // 预分配I通道结果
    QVector<QVector<double>> rq;         // 预分配Q通道结果
    QVector<double> tempi;              // 预分配临时I通道
    QVector<double> tempq;              // 预分配临时Q通道
    QVector<QVector<double>> aresult;
    QVector<QVector<double>> presult;



    void initializeReferenceSignals();  // 初始化参考信号
    void processIQData(const uint8_t* data, int length);  // 数据处理函数


    // 创建滤波器实例
    CFilter_FIR firFilterI;
    CFilter_FIR firFilterQ;
    void initFilters();

    QVector<double> computeStdDev(const QVector<QVector<double>>& matrix); // 计算标准差
    QVector<double> phaseUnwrap(const QVector<double>& phases);

    QMutex mutex1;
    int alarmPos = -1; // 初始化为无效位置

};

#endif // DEMODULATION_H
