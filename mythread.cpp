#include "mythread.h"


QMyThread::QMyThread()
{
//    connect(this,&QMyThread::SendData,this,&QMyThread::DealData);
//    DEMOdata_flash = make_shared<CirQueue<float>>(PerBufSize); //1s数据量 * 1000
}

void QMyThread::acqBegin()
{
    //开始采集
    acq_Pause = false;
    //QTStart(stCardInfo,QTFM_COMMON_TRANSMIT_DIRECTION_BRD2PC,1,0xffffffff,0);

}

void QMyThread::acqPause()
{
    //暂停采集
    acq_Pause=true;
    //QTStart(stCardInfo,QTFM_COMMON_TRANSMIT_DIRECTION_BRD2PC,0,0xffffffff,0);
}

void QMyThread::stopThread()
{
    i_stop = true;//停止线程,停止采集
}

void QMyThread::InitCard(ST_CARDINFO *pstCardInfo, unsigned int unBoardIndex)
{
    //----Open card
    QTOpenBoard (pstCardInfo,unBoardIndex);
    QTResetBoard (pstCardInfo);

    //Take max sample rate as default. Users feel free to change it by uncomment this line then assign new value.
    pstCardInfo->ClockInfo.SRate = 250000000;//Sample rate in Hz

    if (pstCardInfo->ProdInfo.product_number == 0x1142)
    {
      int res = -1;
      while (res)
      {
        res=QTSyncOp(pstCardInfo,Fref,1,QTFM_COMMON_CLOCK_VCO_MODE_0,RefClkMode,ADCClkMode,pstCardInfo->ClockInfo.SRate,0,0);
      }
    }
    else
    {
      //----Setup clock
      QTClockSet (pstCardInfo,Fref,1,(pstCardInfo->ClockInfo.SRate),QTFM_COMMON_CLOCK_VCO_MODE_0,RefClkMode,ADCClkMode,1);
      //----Setup AFE
      if (pstCardInfo->ProdInfo.product_number!=0x1125)
      {
        QTAdcModeSet (pstCardInfo,0,(pstCardInfo->stAI.bForceIOdelay)?0:(1<<8), 0);
      }
    }

    //----Setup Input range and offset
    if (pstCardInfo->ProdInfo.couple_type==0xDC)
    {
      //----Set analog input range first then offset
      QTChannelRangeSet(pstCardInfo,-1,CurrInputRange);
      //----Set analog offset
      QTChannelOffsetSet(pstCardInfo,-1,OffSet);
    }
}

void QMyThread::QT_FifoMultiple_Trigout(ST_CARDINFO *pstCardInfo)
{
    //Reset to clear FIFO in FPGA
     QTResetBoard (pstCardInfo);
      //Set notify size in byte
     QTSetNotifySizeB(pstCardInfo,NotifySizeB);
      //Analog input enable. Run the command multiple times for other channels
     QTInputChannelSet (pstCardInfo,CHANNEL_0,0,0,0,0,1);//Channel 0
      //Select data format between offset binary code and two's complement
     QTDataFormatSet(pstCardInfo,DataFormat);//offset binary or two's complement
      //----Setup work mode, acquisition parameters
     QTABAModeSet(pstCardInfo,ABA_NORMAL_MODE,48,1);
     QTWorkModeSet (pstCardInfo,SegmentLen,PreTriggerLen,0,QTFM_COMMON_BOARD_WORK_MODE_FIFO_MULTIPLE_LOOPBUF|QTFM_COMMON_TRIGGER_MODE_EDGE,0,0);
     QTTimestampSet (pstCardInfo,0,0,0,(pstCardInfo->ClockInfo.SRate),0);
     //----Setup trigger source and types
     //Internal periodic pulse for multiple trigger events
     QTPulseTriggerSet (pstCardInfo,QTFM_COMMON_TRIGGER_TYPE_RISING_EDGE,TrigPulseWidth/(1000000000/(pstCardInfo->ClockInfo.SRate)),TrigPulsePeriod/(1000000000/(pstCardInfo->ClockInfo.SRate)),1);
     QTTriggerSourceMaskSet (pstCardInfo,QTFM_COMMON_TRIGGER_SOURCE_MASK_OR,0,0);//trigger delay
     QTGPIOWrite(pstCardInfo,-1,3);
}

void QMyThread::creatpszBuf()
{
//    qDebug() << TrigPulseFrequency;
    //----Define the total amount of data and allocate memory as an intermediate buffer
//    TotalData =(unsigned __int64) 1024*1024; //320000000; //320MB
    // should be aligned with pstCardInfo->dib.EachTransferLen_Tx  每次在虚拟内存vifo内取一秒的数据，相当于板卡内存达到1秒的数据量就传输一次  一秒的数据量太大
    qDebug() << SegmentLen;
    PerBufSize = 0.1*SegmentLen*TrigPulseFrequency;
    qDebug() << PerBufSize;
    //----Calculate the amount of data and allocate buffer
    if (stCardInfo->ProdInfo.product_number == 0x1142)
      Memsize = SegmentLen;
    else
      Memsize = SegmentLen*2;
//    pszBuf = (unsigned char*) malloc(sizeof(char)*Memsize);
    pszBuf = (unsigned char*) malloc(sizeof(char)*PerBufSize);
}

void QMyThread::INITBOARD()
{
    InitCard(&stCardInfo[0],0);
    QT_FifoMultiple_Trigout (&stCardInfo[0]);
    creatpszBuf();
    makeDataFile_time();
    QTStart(stCardInfo,QTFM_COMMON_TRANSMIT_DIRECTION_BRD2PC,1,0xffffffff,0);
    ini = 1;

}

//void QMyThread::SendData(const uint8_t *data, size_t size)
//{
//    qDebug() << "Sending byte: " << size << static_cast<unsigned int>(data[1000]);

//}

QString QMyThread::makeDataDir_root()
{
    QString path=QDir::currentPath()+"/Data";
    QDir dir(path);//构造函数将path设置为当前目录
    if(!dir.exists())
    {
        dir.mkdir(path);//在当前目录下新建path表示的子目录
    }
    rootPath=path;
    return path;

}

QString QMyThread::makeDataDir_date()
{
    makeDataDir_root();
    QDate tim;
    QString time=tim.currentDate().toString("yyyy_MM_dd");
    QString path=rootPath+"/"+time;
    QDir dir(path);//构造函数将path设置为当前目录
    if(!dir.exists())
    {
        dir.mkdir(path);//在当前目录下新建path表示的子目录
    }
    datePath=path;
    return path;

}
QString QMyThread::makeDataFile_time()
{
    makeDataDir_date();
    QTime tim;
    QString time=tim.currentTime().toString("hh_mm_ss");
    QString path=datePath+"/"+time+".bin";
    QFile file(path);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        file.close();
    }
    fileName=path;
    return path;
}




void QMyThread::receiveQT_PCI_Parameter(unsigned int clockInfo_SRate,double length, unsigned int segmentLen,int savefile,unsigned int trigPulseWidth, unsigned int trigPulsePulse)
{
    SegmentLen = segmentLen;
    SaveFile = savefile;
    TrigPulseWidth = trigPulseWidth;
    TrigPulsePeriod = trigPulsePulse;
    qDebug()<<     SegmentLen <<
    SaveFile <<
    TrigPulseWidth <<
                   TrigPulsePeriod ;
}


void QMyThread::saveDataAsBin()
{
    QFile file(fileName); // 指定类指向的文件名
    if (!file.open(QIODevice::Append)) { // 使用 Append 模式打开文件
        qDebug() << "File open failed: " << fileName;
    } else {
        qDebug() << "File opened successfully";
        // 使用 QDataStream 来写入数据
        QDataStream out(&file);
        out.writeRawData((const char*)pszBuf, PerBufSize);

        // 如果需要发送数据，调用相应的函数
        emit SendData((const uint8_t*)pszBuf, PerBufSize);

        // 确保所有数据都被写入到文件
        file.flush();
        // 关闭文件
        file.close();
        qDebug() << "fwrite: Data written to file";
    }
}

void QMyThread::run()
{
    i_stop=false;//启动线程时令m_stop=false

    while(!i_stop)
    {
        if(ini==0){
            INITBOARD();
        }

        if(!acq_Pause){
            Sleep(100);
            QTBufStatusGet(stCardInfo,&AvailableData,&BufOverflow,&NoBytesOverwritten);
            if (BufOverflow || NoBytesOverwritten) break;
            RecvDataLen += NoBytesOverwritten;
//            qDebug() << "AvailableData: "<<AvailableData;
            if (AvailableData<PerBufSize) continue;
//            qDebug() << "PerBufSize: "<<PerBufSize;
            QTBufSDataGet(stCardInfo,&pszBuf[0],(int)PerBufSize);
//             qDebug() << "QTBufSDataGet: ";

//            qint64 timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch(); //毫秒级
//            qDebug() << timestamp;

            if (SaveFile)
            {
                saveDataAsBin();
            }

            RecvDataLen += PerBufSize;
//            qDebug() << "Received %d(MB),vfifo %d(MB)\n"<< RecvDataLen << AvailableData;

        }

    }

    //Print error Info if overflows during acquisition

    if (BufOverflow)
    {
    qDebug() << BufOverflow << ("Samples data were lost! Either speed up buffer read rate or reduce sample rate\n");
    }
    if (NoBytesOverwritten)
    {
    qDebug()  << NoBytesOverwritten << ("11Samples data could be corrupted by overwritten!Either speed up buffer read rate or reduce sample rate\n");
    }

    free(pszBuf);
    qDebug() << "freeBuf";
    pszBuf = NULL;

    qDebug() << "stopacq";
    QTStart(stCardInfo,QTFM_COMMON_TRANSMIT_DIRECTION_BRD2PC,0,0xffffffff,0);

    QTCloseBoard (&stCardInfo[0]);

    quit();//相当于  exit(0),退出线程的事件循环
}

