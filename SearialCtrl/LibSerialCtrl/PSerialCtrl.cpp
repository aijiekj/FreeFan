#include "PSerialCtrl.h"

PSerialCtrl::PSerialCtrl(QObject *parent) :
    QObject(parent)
{
    m_pComCtrl = NULL;

    //初始化波特率对照列表
    intitBaudRate();
}

PSerialCtrl::~PSerialCtrl()
{
    closeComPort();

    if(m_pComCtrl)
    {
        delete m_pComCtrl;
        m_pComCtrl = NULL;
    }
}

//打开COM设备
bool PSerialCtrl::openComPort(const QString &sName, const QString &sBaud)
{
    bool bRet = false;

    m_pComCtrl = new QSerialPort(sName);
    bRet = m_pComCtrl->open(QIODevice::ReadWrite);  //读写打开

    if(bRet)
    {
        m_pComCtrl->setBaudRate(m_mapBaud.value(sBaud));  //波特率
        m_pComCtrl->setDataBits(QSerialPort::Data8);     //数据位
        m_pComCtrl->setParity(QSerialPort::NoParity);    //无奇偶校验
        m_pComCtrl->setStopBits(QSerialPort::OneStop);   //无停止位
        m_pComCtrl->setFlowControl(QSerialPort::NoFlowControl);  //无控制
    }

    return bRet;
}

//发送数据
bool PSerialCtrl::sendComd(const QByteArray &data)
{
    bool bRet = false;

    if(m_pComCtrl && m_pComCtrl->isOpen())
    {
        int nWrite = m_pComCtrl->write(data.constData());

        bRet = (nWrite == data.size());
    }

    return bRet;
}

//关闭COM
void PSerialCtrl::closeComPort()
{
    if(m_pComCtrl && m_pComCtrl->isOpen())
    {
        m_pComCtrl->clear();
        m_pComCtrl->close();
    }
}

//清空串口数据
void PSerialCtrl::clearComData()
{
    if(m_pComCtrl && m_pComCtrl->isOpen())
    {
        m_pComCtrl->clear();
    }
}

//初始化波特率列表
void PSerialCtrl::intitBaudRate()
{
    m_mapBaud.insert("9600", QSerialPort::Baud9600);
    m_mapBaud.insert("2400", QSerialPort::Baud2400);
}
