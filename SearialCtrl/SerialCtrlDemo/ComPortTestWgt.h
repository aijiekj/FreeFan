#ifndef COMPORTTESTWGT_H
#define COMPORTTESTWGT_H

#include <QWidget>
#include "PSerialCommand.h"

namespace Ui {
class ComPortTestWgt;
}

class ComPortTestWgt : public QWidget
{
    Q_OBJECT

public:
    explicit ComPortTestWgt(QWidget *parent = 0);
    ~ComPortTestWgt();

private slots:
    void slot_SendCommandBtn_Clicked();

private:
    Ui::ComPortTestWgt *ui;

    PSerialCommand      *m_pSerilComd;
};

#endif // COMPORTTESTWGT_H
