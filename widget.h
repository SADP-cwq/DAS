#ifndef WIDGET_H
#define WIDGET_H

#include <QMetaType>
#include <QWidget>
//include standard header
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <QtGlobal>
#include<QtDebug>
#include"mythread.h"
#include"demodulation.h"
#include<QString>
#include "qcustomplot.h"
#include <QtCore/QVector>
#include <cstdint>

  using namespace QTApi;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QMyThread fifomultiplethreadA;
    Demodulation IQthreadA;
    void iniGloplt(QCustomPlot *plt);
    void iniAmplitudeplt(QCustomPlot *plt);
    void iniPhaseplt(QCustomPlot *plt);

private:

    double full_range = 2.47*1000;
    double bit_num = 2 << 16;
    QVector<double> DealData(const uint8_t* data, int size);

    void addDataToGloChart(QCustomPlot *plt, QVector<double> data);
    void addDataToAmplitudeChart(QCustomPlot *plt,const QVector<double>& amplitude);
    void addDataToPhaseChart(QCustomPlot *plt,const QVector<double>& amplitude);

private slots:
    void ReceiveData(const uint8_t* data, int size);

    void ReceiveAmplitudeData(const QVector<double>& amplitude);

    void ReceiveFaultPositions(const QVector<int>& positions);

    void ReceivePhaseData(const QVector<double>& phase);

    void on_btn_start_clicked();
    void on_btn_stop_clicked();
    void on_btn_ini_clicked();
    void on_btn_close_clicked();



    void on_btn_IQ_clicked();



    void on_btn_IQ_close_clicked();


    void on_btn_set_alarm_pos_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
