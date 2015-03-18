#ifndef PSERIALCOMMAND_H
#define PSERIALCOMMAND_H

#include <QObject>
#include "PSerialCtrl.h"
#include "libserialctrl_global.h"

class LIBSERIALCTRLSHARED_EXPORT PSerialCommand : public QObject
{
    Q_OBJECT
public:
    explicit PSerialCommand(QObject *parent = 0);
    ~PSerialCommand();

    //消费类型
    enum eConsumptionType
    {
        eClearAllType = 0,  //全灭
        eMonovalentType,    //单价
        eTotalType,         //总计
        eReceiptType,       //收款
        eChangeType,        //找零
        eClearScreenType,   //清屏, 显示结果为0.00,且各种灯灭
        eInitComType,       //初始化,显示结果为0.00,且各种灯灭
        eConsumptionCount
    };


    /*
     *   @Description: 设置消费数据
     *
     *   @Function:  void setConsumptionData(PSerialCommand::eConsumptionType eType, const QString &sPrice);
     *
     *   @parameter:  PSerialCommand::eConsumptionType eType    消费类型
     *                const QString &sPrice                     价格
     *
     *   @return:    无
     *
     */
    void setConsumptionData(PSerialCommand::eConsumptionType eType, const QString &sPrice);

signals:

public slots:
private:
    /*
    *
    *   @Description: 初始化ASCII表
    *
    */
    void initASCII();

    /*
    *
    *   @description:   初始化串口配置信息
    *
    *   @function:      void initComConfigData();
    *
    */
    void initComConfigData();


    /*
     *  @description: 获取命令数据
     *
     *  @function: void getCommand(const QString &sCommand, QByteArray &comdArray);
     *
     *  @parameter: const QString &sCommand,    命令原型,如:ESC Q A 23111.78 CR, 注意条个参数之间使用空格隔开
     *
     *              QByteArray &comdArray       转码之后的命令,用于向串口发送的数据,注:命令中有些字符是非打印字符,
     *                                          所以在打印输出时会显示不出来
     *
     *  @return:    无
    **/
    void getCommand(const QString &sCommand, QByteArray &comdArray);

private:
    PSerialCtrl     *m_pComCtrl;    //端口控制
    QMap<QString, QString> m_mapASCII;  //ASCII对照表
};

#endif // PSERIALCOMMAND_H
