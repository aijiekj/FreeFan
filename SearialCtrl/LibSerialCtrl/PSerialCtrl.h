#ifndef CSERIALCTRL_H
#define CSERIALCTRL_H

#include "libserialctrl_global.h"
#include <QObject>
#include <QMap>
#include <QSerialPort>

class LIBSERIALCTRLSHARED_EXPORT PSerialCtrl : public QObject
{
    Q_OBJECT
public:
    explicit PSerialCtrl(QObject *parent = 0);
    ~PSerialCtrl();

    /*
     *   @Description:打开串口
     *
     *   @Function:  bool openComPort(const QString &sName, const QString &sBaud);
     *
     *   @parameter:const QString &sName    端口设备名称,如COM1,必须大写
     *              const QString &sBaud    波特率         2400,9600
     *
     *   @return:    打开设备成功返回true,否则为false;
     *
     */
    bool openComPort(const QString &sName, const QString &sBaud);

    /*
    *   @Description:  发送数据
    *
    *   @Function: bool sendCommand(const QByteArray &data);
    *
    *   @parameter: const QByteArray &data  要发送数据
    *
    *   @return:    如果数据发送成功返回true,否则为false;
    */
    bool sendComd(const QByteArray &data);

public slots:

private:
    /*
    *
    *   @Description:初始化波特率列表
    *
    *   @Description: void initBauRate();
    *
    */
    void intitBaudRate();

    //关闭串口
    void closeComPort();

    /*
     *  @description: 清空串口数据
     *
     *  @function:  void clearComData();
     *
     **/
    void clearComData();

private:
    QSerialPort     *m_pComCtrl;      //串口控制
    QMap<QString, QSerialPort::BaudRate>  m_mapBaud;    //波特率
};

#endif // CSERIALCTRL_H
