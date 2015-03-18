#include "PSerialCommand.h"
#include <QDebug>
#include <QApplication>
#include <QSettings>

PSerialCommand::PSerialCommand(QObject *parent) :
    QObject(parent)
{
    //初始化ASCII对照表
    initASCII();

    //初始化串口配置
    m_pComCtrl = new PSerialCtrl;
    initComConfigData();
}

PSerialCommand::~PSerialCommand()
{
    if(m_pComCtrl)
    {
        delete m_pComCtrl;
        m_pComCtrl = NULL;
    }
}

//设置消费数据
void PSerialCommand::setConsumptionData(PSerialCommand::eConsumptionType eType, const QString &sPrice)
{
    if(m_pComCtrl)
    {
        QByteArray commdArray;
        QByteArray ledArray;
        QString sCommand, sLedComd;
        switch(eType)
        {
        case eMonovalentType:   //单价
        case eTotalType:        //总计
        case eReceiptType:      //收款
        case eChangeType:       //找零
            sCommand = QString("ESC Q A ") + sPrice + QString(" CR");
            getCommand(sCommand, commdArray);
            sLedComd = QString("ESC s ") + QString::number(eType);
            getCommand(sLedComd, ledArray);
            break;
        case eClearAllType:     //清空灯状态
            sLedComd = QString("ESC s 0");
            getCommand(sLedComd, ledArray);
            break;
        case eClearScreenType:  //清屏
            sLedComd = QString("ESC s 0");
            getCommand(sLedComd, ledArray);
            sCommand = QString("ESC Q A ") + QString("0.00") + QString(" CR");
            getCommand(sCommand, commdArray);
            break;
        case eInitComType: //初始化
            sLedComd = QString("ESC @");
            getCommand(sLedComd, ledArray);
        default:
            break;
        }

        //发送灯状态
        bool bRet = false;
        if(!sLedComd.isEmpty())
        {
            bRet = m_pComCtrl->sendComd(ledArray);
            if(bRet)
            {
                qDebug() << "Send LED Status SuccesssFully@!Q!!";
            }
            else
            {
                qDebug() << "Send LED Status Error!!!!!";
            }
        }

        //发送消费数据
        bRet = false;
        if(!sCommand.isEmpty())
        {
            bRet = m_pComCtrl->sendComd(commdArray);

            if(bRet)
            {
                qDebug() << "Send Message SuccesssFully@!Q!!";
            }
            else
            {
                qDebug() << "Send Message Error!!!!!";
            }
        }
    }
}

//初始化ASCII对照表
void PSerialCommand::initASCII()
{
    m_mapASCII.clear();
    m_mapASCII.insert("ESC",    QString(QChar(0x1B)));
    m_mapASCII.insert("CAN",    QString(QChar(0x18)));
    m_mapASCII.insert("STX",    QString(QChar(0x02)));
    m_mapASCII.insert("CLR",    QString(QChar(0x11)));
    m_mapASCII.insert("CR",     QString(QChar(0x0D)));
    m_mapASCII.insert("_",      QString(QChar(0x5F)));
    m_mapASCII.insert("B",      QString(QChar(66)));
    m_mapASCII.insert("M",      QString(QChar(77)));
    m_mapASCII.insert("L",      QString(QChar(76)));
    m_mapASCII.insert("@",      QString(QChar(64)));
    m_mapASCII.insert("Q",      QString(QChar(81)));
    m_mapASCII.insert("s",      QString(QChar(115)));
    m_mapASCII.insert("A",      QString(QChar(65)));
    m_mapASCII.insert("I",      QString(QChar(73)));
}

//初始化串口配置数据
void PSerialCommand::initComConfigData()
{
    QString sConfigFile = qApp->applicationDirPath() + "./Config/Verson.ini";
    qDebug() << "Config path... " << sConfigFile;

    QString sComPort, sBaudRate;
    QSettings *settings = new QSettings(sConfigFile, QSettings::IniFormat);
    //settings->setIniCodec("UTF8");
    //读取本地配置数据
    sComPort = settings->value("COM/COM_PORT").toString();
    sBaudRate = settings->value("COM/BaudRate").toString();

    if(sComPort.isEmpty())
    {
        sComPort = QString("COM2");
        settings->beginGroup("COM");
        settings->setValue("COM_PORT", sComPort);
        settings->endGroup();
    }

    if(sBaudRate.isEmpty())
    {
        sBaudRate = QString("2400");
        settings->beginGroup("COM");
        settings->setValue("BaudRate", sBaudRate);
        settings->endGroup();
    }

    //设置串口
    if(m_pComCtrl)
    {
        qDebug() << "ComPort:" << sComPort << " Baud:" << sBaudRate;
        bool bRet = m_pComCtrl->openComPort(sComPort, sBaudRate);

        if(bRet)
        {
            setConsumptionData(eInitComType, QString());
            qDebug() << "Open Com Successfully!!!";
        }
        else
        {
            qDebug() << "Open Com Error!!!";
        }
    }
}

//通过原始命令转成要发送的命令数据
void PSerialCommand::getCommand(const QString &sCommand, QByteArray &comdArray)
{
    comdArray.clear();
    //根据参数个数组织发送数据
    QStringList lCommand = sCommand.split(" ");
    const int nArgv = lCommand.count();

    qDebug() << "Command List ... " << lCommand << nArgv;
    //根据参数个数设置命令格式内容
    switch(nArgv)
    {
    case 1:
    {
        comdArray.append(m_mapASCII.value(lCommand.at(0)).toUtf8());
    }
        break;
    case 2:
    {
       comdArray.append(m_mapASCII.value(lCommand.at(0)).toUtf8());
       comdArray.append(m_mapASCII.value(lCommand.at(1)).toUtf8());
    }
        break;
    case 3:
    {
        comdArray.append(m_mapASCII.value(lCommand.at(0)).toUtf8());
        comdArray.append(m_mapASCII.value(lCommand.at(1)).toUtf8());
        comdArray.append(lCommand.at(2).toUtf8());
    }
        break;
//    case 4:
//    {
//        comdArray.append(m_mapASCII.value(lCommand.at(0)).toUtf8());
//        comdArray.append(m_mapASCII.value(lCommand.at(1)).toUtf8());
//        comdArray.append(m_mapASCII.value(lCommand.at(2)).toUtf8());
//        comdArray.append(m_mapASCII.value(lCommand.at(3)).toUtf8());
//    }
//        break;
    case 5:
    {
        comdArray.append(m_mapASCII.value(lCommand.at(0)).toUtf8());
        comdArray.append(m_mapASCII.value(lCommand.at(1)).toUtf8());
        comdArray.append(m_mapASCII.value(lCommand.at(2)).toUtf8());
        comdArray.append(lCommand.at(3).toUtf8());
        comdArray.append(m_mapASCII.value(lCommand.at(4)).toUtf8());
    }
        break;
    default:
        qDebug() << "Is Empty....";
        break;
    }
}
