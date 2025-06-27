#ifndef MYTHREAD_H
#define MYTHREAD_H


#include <QThread>
#include"QTDevice.h"
#include"QTfmCommon.h"
#include"QT_IMPORT.h"
//include standard header
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include<QtDebug>
#include<QMutex>
#include<QDir>
#include<QDate>
#include<QDataStream>
#include<QVector>
#include <QQueue>
#include <memory>
#include <QtMath>
#include <QVector>

//struct LocalOscillatorSignal {
//    QVector<double> sine;    // 正弦信号
//    QVector<double> cosine;  // 余弦信号
//};

// IQ解调函数
struct IQResult {
    QVector<double> I;
    QVector<double> Q;
};

struct SignalProperties {
    QVector<double> amplitude;  // 幅值
    QVector<double> phase;      // 相位（弧度）
};

class QMyThread: public QThread
{
     Q_OBJECT


private:

    bool    i_stop=false; //停止线程
    bool    acq_Pause = true;//采集

    //----Clock parameters
    unsigned int Fref                      = 100000000;//Reference clock frequency.
    QTFM_COMMON_CLOCK_REFERENCE RefClkMode = QTFM_COMMON_CLOCK_REF_MODE_2;//Change to QTFM_COMMON_CLOCK_REF_MODE_1 if external reference clock is required.
    QTFM_COMMON_ADC_CLOCK ADCClkMode       = QTFM_COMMON_ADC_CLOCK_MODE_0;//Change to QTFM_COMMON_ADC_CLOCK_MODE_1 if external sampling clock is required.

    QTFM_INPUT_RANGE   CurrInputRange = QTFM_INPUT_RANGE_4;//+full-scale in mV
    double              OffSet         = 0;//[-fullscale,+fullscale] in uV


    //----Acquisition parameters
    double sampleRate = 250000000;//Sample rate in Hz
    double AOMfrequency = 80e6;
    unsigned int SegmentLen          = 4096;//number of samples per segment
    unsigned int TrigPulseWidth      = 100;//in step of sample clock period in ns；脉宽
    unsigned int TrigPulsePeriod     = 50000;//in step of sample clock period in ns；脉冲周期
    unsigned int TrigPulseFrequency =  1000000000/TrigPulsePeriod; //脉冲频率
    unsigned int TrigDelay           = 200;//in step of sample clock period in ns
    unsigned int NotifySizeB         = 1024;//The NotifySizeB defines the amount of bytes after which an interrupt should be generated.
    unsigned int PreTriggerLen       = 0;//pre-trigger length in samples
    char         DataFormat          = 1;//0:offset binary; 1:two's complement
    int          SaveFile            = 1;
    double fullRange = 2.47, bitNum = 65536;

    //Internal variables
    int nRet = -1;//Default return value
    char szFilePathName[MAX_PATH]/* = {0}*/;
    unsigned int ClockDivider = 0;
    unsigned int Memsize = 0;
    unsigned char *pszBuf = NULL;
    __int64 RecvDataLen=0;
    __int64 AvailableData=0;//No. of available sample data bytes in buffer
    int BufOverflow=-1;//buffer overflow flag
    unsigned int NoBytesOverwritten=0;//No. of overwritten sample data bytes
    FILE *fp = NULL;
    unsigned __int64 TotalData=0;
    unsigned int PerBufSize = 0;


    QString rootPath;
    QString datePath;
    QString fileName;

    int ini = 0;

    ST_CARDINFO stCardInfo[_QTFIRMWARE_NUM_OF_CARD];//card info for per each card on PC mainboard
    void InitCard(ST_CARDINFO *pstCardInfo,unsigned int unBoardIndex);
    void QT_FifoMultiple_Trigout (ST_CARDINFO *pstCardInfo);
    void creatpszBuf();
    void INITBOARD();
    QString makeDataDir_root();
    void saveDataAsBin();


protected:
    void run() override;  //线程任务
public:
    QMyThread();
    void    acqBegin();//开始采集
    void    acqPause();//暂停

    void    stopThread(); //结束线程

    QString makeDataDir_date();
    QString makeDataFile_time();


public slots:

    void receiveQT_PCI_Parameter(unsigned int clockInfo_SRate,double length, unsigned int segmentLen,int saveFile,unsigned int TrigPulseWidth, unsigned int TrigPulsePulse);

signals:
    void acquisitionIfo(QString ifo);
    void SendData(const uint8_t* data, int size);

};


#endif // MYTHREAD_H
