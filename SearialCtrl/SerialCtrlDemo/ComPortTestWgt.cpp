#include "ComPortTestWgt.h"
#include "ui_ComPortTestWgt.h"

ComPortTestWgt::ComPortTestWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComPortTestWgt)
{
    ui->setupUi(this);

    m_pSerilComd = new PSerialCommand;

    connect(ui->sendCommandBtn, SIGNAL(clicked()),
            this, SLOT(slot_SendCommandBtn_Clicked()));
}

ComPortTestWgt::~ComPortTestWgt()
{
    delete ui;
}

void ComPortTestWgt::slot_SendCommandBtn_Clicked()
{
    if(m_pSerilComd)
    {
        m_pSerilComd->setConsumptionData((PSerialCommand::eConsumptionType)ui->ledStatusCmBx->currentIndex(),
                                         ui->comboBox->currentText());
    }
}
