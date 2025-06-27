#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    iniGloplt(ui->global_plt);
    iniAmplitudeplt(ui->amplitude_plt);
    iniPhaseplt(ui->phase_plt);
    connect(&fifomultiplethreadA,&QMyThread::SendData,this,&Widget::ReceiveData);

    connect(&fifomultiplethreadA,&QMyThread::SendData,&IQthreadA,&Demodulation::receiveData);
    qRegisterMetaType<QVector<double> >("QVector<double>");
    connect(&IQthreadA,&Demodulation::processedAmplitudeDataReady,this,&Widget::ReceiveAmplitudeData);
    connect(&IQthreadA, &Demodulation::faultPositionsDetected, this, &Widget::ReceiveFaultPositions);
    connect(&IQthreadA,&Demodulation::phasePhaseDataReady,this,&Widget::ReceivePhaseData);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::iniGloplt(QCustomPlot *plt)
{
    QFont font;
    font.setFamily("楷体");
    plt->legend->setFont(font);
    plt->xAxis->setLabelFont(font);
    plt->xAxis->setTickLabelFont(font);
    plt->yAxis->setTickLabelFont(font);
    plt->yAxis->setLabelFont(font);
    plt->xAxis->setLabel("距离");
    plt->yAxis->setLabel("幅值");
    plt->addGraph(); // red line
    plt->graph(0)->setPen(QColor(66,188,216));
    plt->graph(0)->setAntialiasedFill(true);
    plt->graph(0)->setName("原始RBS曲线");
    //plt->yAxis->setRange(lowTemp,highTemp);
//    QColor color(16,36,52);
//    plt->setBackground(color);
    // 允许用户用鼠标拖动轴范围，用鼠标滚轮缩放，点击选择图形:
    plt->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plt->legend->setVisible(true); // 显示图例
    plt->legend->setBrush(QColor(255, 255, 255, 150));
    //坐标轴使用点数刻度
    plt->axisRect()->setupFullAxesBox();
    //设置y轴范围
    plt->xAxis->setBasePen(QPen(QColor(255,255,255),1));
    plt->xAxis2->setBasePen(QPen(QColor(255,255,255),1));
    plt->yAxis->setBasePen(QPen(QColor(255,255,255),1));
    plt->yAxis2->setBasePen(QPen(QColor(255,255,255),1));
    plt->xAxis->setLabelColor(QColor(255,255,255));
    plt->xAxis2->setLabelColor(QColor(255,255,255));
    plt->yAxis->setLabelColor(QColor(255,255,255));
    plt->yAxis2->setLabelColor(QColor(255,255,255));
    plt->xAxis->setBasePen(QColor(255,255,255));
    plt->xAxis->setTickPen(QColor(255,255,255));
    plt->xAxis->setLabelColor(QColor(255,255,255));
    plt->xAxis->setTickLabelColor(QColor(255,255,255));
    plt->yAxis->setBasePen(QColor(255,255,255));
    plt->yAxis->setTickPen(QColor(255,255,255));
    plt->yAxis->setLabelColor(QColor(255,255,255));
    plt->yAxis->setTickLabelColor(QColor(255,255,255));
    plt->yAxis->setRange(-100,100);
}

void Widget::iniAmplitudeplt(QCustomPlot *plt)
{
    QFont font;
    font.setFamily("楷体");
    plt->legend->setFont(font);
    plt->xAxis->setLabelFont(font);
    plt->xAxis->setTickLabelFont(font);
    plt->yAxis->setTickLabelFont(font);
    plt->yAxis->setLabelFont(font);
    plt->xAxis->setLabel("距离");
    plt->yAxis->setLabel("幅值");
    plt->addGraph(); // red line
    plt->graph(0)->setPen(QColor(66,188,216));
    plt->graph(0)->setAntialiasedFill(true);
    plt->graph(0)->setName("全局强度曲线");
    //plt->yAxis->setRange(lowTemp,highTemp);
//    QColor color(16,36,52);
//    plt->setBackground(color);
    // 允许用户用鼠标拖动轴范围，用鼠标滚轮缩放，点击选择图形:
    plt->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plt->legend->setVisible(true); // 显示图例
    plt->legend->setBrush(QColor(255, 255, 255, 150));
    //坐标轴使用点数刻度
    plt->axisRect()->setupFullAxesBox();
    //设置y轴范围
    plt->xAxis->setBasePen(QPen(QColor(255,255,255),1));
    plt->xAxis2->setBasePen(QPen(QColor(255,255,255),1));
    plt->yAxis->setBasePen(QPen(QColor(255,255,255),1));
    plt->yAxis2->setBasePen(QPen(QColor(255,255,255),1));
    plt->xAxis->setLabelColor(QColor(255,255,255));
    plt->xAxis2->setLabelColor(QColor(255,255,255));
    plt->yAxis->setLabelColor(QColor(255,255,255));
    plt->yAxis2->setLabelColor(QColor(255,255,255));
    plt->xAxis->setBasePen(QColor(255,255,255));
    plt->xAxis->setTickPen(QColor(255,255,255));
    plt->xAxis->setLabelColor(QColor(255,255,255));
    plt->xAxis->setTickLabelColor(QColor(255,255,255));
    plt->yAxis->setBasePen(QColor(255,255,255));
    plt->yAxis->setTickPen(QColor(255,255,255));
    plt->yAxis->setLabelColor(QColor(255,255,255));
    plt->yAxis->setTickLabelColor(QColor(255,255,255));
    plt->yAxis->setRange(0,1);
}

void Widget::iniPhaseplt(QCustomPlot *plt)
{
    QFont font;
    font.setFamily("楷体");
    plt->legend->setFont(font);
    plt->xAxis->setLabelFont(font);
    plt->xAxis->setTickLabelFont(font);
    plt->yAxis->setTickLabelFont(font);
    plt->yAxis->setLabelFont(font);
    plt->xAxis->setLabel("时间");
    plt->yAxis->setLabel("相位");
    plt->addGraph(); // red line
    plt->graph(0)->setPen(QColor(66,188,216));
    plt->graph(0)->setAntialiasedFill(true);
    plt->graph(0)->setName("单点相位曲线");
    //plt->yAxis->setRange(lowTemp,highTemp);
//    QColor color(16,36,52);
//    plt->setBackground(color);
    // 允许用户用鼠标拖动轴范围，用鼠标滚轮缩放，点击选择图形:
    plt->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plt->legend->setVisible(true); // 显示图例
    plt->legend->setBrush(QColor(255, 255, 255, 150));
    //坐标轴使用点数刻度
    plt->axisRect()->setupFullAxesBox();
    //设置y轴范围
    plt->xAxis->setBasePen(QPen(QColor(255,255,255),1));
    plt->xAxis2->setBasePen(QPen(QColor(255,255,255),1));
    plt->yAxis->setBasePen(QPen(QColor(255,255,255),1));
    plt->yAxis2->setBasePen(QPen(QColor(255,255,255),1));
    plt->xAxis->setLabelColor(QColor(255,255,255));
    plt->xAxis2->setLabelColor(QColor(255,255,255));
    plt->yAxis->setLabelColor(QColor(255,255,255));
    plt->yAxis2->setLabelColor(QColor(255,255,255));
    plt->xAxis->setBasePen(QColor(255,255,255));
    plt->xAxis->setTickPen(QColor(255,255,255));
    plt->xAxis->setLabelColor(QColor(255,255,255));
    plt->xAxis->setTickLabelColor(QColor(255,255,255));
    plt->yAxis->setBasePen(QColor(255,255,255));
    plt->yAxis->setTickPen(QColor(255,255,255));
    plt->yAxis->setLabelColor(QColor(255,255,255));
    plt->yAxis->setTickLabelColor(QColor(255,255,255));
    plt->yAxis->setRange(-3,3);
}

QVector<double> Widget::DealData(const uint8_t *data, int size)
{

    // 计算实际读取的采样点数（不超过4096）
    int samplesToRead = qMin(size/2, 4096);
    QVector<double> samples;
    samples.reserve(samplesToRead);

    for (int i = 0; i < samplesToRead*2; i += 2) {
        // 确保不会越界
        if (i + 1 >= size) {
            break;
        }
        // 小端模式
        int16_t value = static_cast<int16_t>(data[i + 1]) << 8 |
                         static_cast<int16_t>(data[i]);
        // 转换为电压值
        double voltage = (full_range / bit_num) * static_cast<double>(value);
        samples.append(voltage);

    }
//    qDebug() << samples;

    return samples;
}

void Widget::addDataToGloChart(QCustomPlot *plt, QVector<double> data)
{   
    // 清空图表中的数据
    plt->graph(0)->data()->clear();

    // 设置X轴的范围
    plt->xAxis->setRange(0, data.size());

    // 添加新数据
    for (int i = 0; i < data.size(); i++)
    {
        plt->graph(0)->addData(i, data[i]);
    }

    // 重新绘制图表
    plt->replot(QCustomPlot::rpQueuedReplot);
}

void Widget::addDataToAmplitudeChart(QCustomPlot *plt, const QVector<double>& amplitude)
{
    // 清空图表中的数据
    plt->graph(0)->data()->clear();

    // 设置X轴的范围
    plt->xAxis->setRange(0, amplitude.size());

    // 自动调整坐标轴范围
    plt->graph(0)->rescaleAxes(true); // true 表示只调整这个图关联的坐标轴

    // 添加新数据
    for (int i = 0; i < amplitude.size(); i++)
    {
        plt->graph(0)->addData(i, amplitude[i]);
    }

    // 重新绘制图表
    plt->replot(QCustomPlot::rpQueuedReplot);
}

void Widget::addDataToPhaseChart(QCustomPlot *plt, const QVector<double> &phase)
{
    // 清空图表中的数据
    plt->graph(0)->data()->clear();

    // 设置X轴的范围
    plt->xAxis->setRange(0, phase.size());

    // 自动调整坐标轴范围
    plt->graph(0)->rescaleAxes(true); // true 表示只调整这个图关联的坐标轴

    // 添加新数据
    for (int i = 0; i < phase.size(); i++)
    {
        plt->graph(0)->addData(i, phase[i]);
    }

    // 重新绘制图表
    plt->replot(QCustomPlot::rpQueuedReplot);
}


void Widget::ReceiveData(const uint8_t *data, int size)
{
    addDataToGloChart(ui->global_plt, DealData(data,size));
}


void Widget::ReceiveAmplitudeData(const QVector<double>& amplitude)
{
    qDebug() << "过来了" << amplitude.size() << amplitude[100];


    addDataToAmplitudeChart(ui->amplitude_plt, amplitude);
}

void Widget::ReceiveFaultPositions(const QVector<int> &positions)
{
    qDebug() << "异常位置：" << positions;
    // 可在地图或图表中标记位置
}

void Widget::ReceivePhaseData(const QVector<double> &phase)
{
    qDebug() << phase;
    addDataToPhaseChart(ui->phase_plt,phase);
}


void Widget::on_btn_start_clicked()
{
    fifomultiplethreadA.acqBegin();

    ui->btn_ini->setEnabled(false);
    ui->btn_start->setEnabled(false);
    ui->btn_stop->setEnabled(true);
    ui->btn_close->setEnabled(true);

}
void Widget::on_btn_stop_clicked()
{
    fifomultiplethreadA.acqPause();
    ui->btn_ini->setEnabled(false);
    ui->btn_start->setEnabled(true);
    ui->btn_stop->setEnabled(false);
    ui->btn_close->setEnabled(true);
}


void Widget::on_btn_ini_clicked()
{
    fifomultiplethreadA.start();
    ui->btn_ini->setEnabled(false);
    ui->btn_start->setEnabled(true);
    ui->btn_stop->setEnabled(false);
    ui->btn_close->setEnabled(true);
}

void Widget::on_btn_close_clicked()
{
    fifomultiplethreadA.stopThread();
    fifomultiplethreadA.wait();
    ui->btn_ini->setEnabled(true);
    ui->btn_start->setEnabled(false);
    ui->btn_stop->setEnabled(false);
    ui->btn_close->setEnabled(false);
}

void Widget::on_btn_IQ_clicked()
{
    IQthreadA.start();
}

void Widget::on_btn_IQ_close_clicked()
{
    IQthreadA.stop();
}



void Widget::on_btn_set_alarm_pos_clicked()
{
    int pos = ui->lineEdit_alarm_pos->text().toInt();
    IQthreadA.setAlarmPosition(pos); // 传递给解调线程
}
