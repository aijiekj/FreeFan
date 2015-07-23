#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->openBtn, SIGNAL(clicked()),
            this, SLOT(slot_OpenModelFileBtn_Clicked()));
    connect(ui->replaceBtn, SIGNAL(clicked()),
            this, SLOT(slot_ReplaceSourceBtn_Clicked()));
    connect(ui->exportFileBtn, SIGNAL(clicked()),
            this, SLOT(slot_ExportFileBtn_Clicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slot_OpenModelFileBtn_Clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开模板文件"),
                                                    ".",
                                                    tr("All Files (*.*)"));
    ui->modelFileLdt->setText(fileName);
    ui->destCodeTxtBwor->clear();

    if(!fileName.isEmpty())
    {
        QFile openFile(fileName);

        if(openFile.exists())
        {
            if (!openFile.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                return;
            }

            ui->sourceCodeTxtBwor->setText(QString::fromUtf8(openFile.readAll()));

            openFile.close();
        }
    }
}

void Widget::slot_ReplaceSourceBtn_Clicked()
{
    QString sTmp = ui->destCodeTxtBwor->toPlainText();
    if(sTmp.isEmpty())
    {
        sTmp = ui->sourceCodeTxtBwor->toPlainText();
    }

    sTmp = sTmp.replace(ui->findSourceLdt->text(),
                 ui->replaceSourceLdt->text());

    ui->destCodeTxtBwor->setText(sTmp);
}

void Widget::slot_ExportFileBtn_Clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("导出文件"),
                                                    ".",
                                                    tr("All Files (*.*)"));
    ui->exportFileNameLdt->setText(fileName);

    if(!fileName.isEmpty())
    {
        QFile saveFile(fileName);

        if (!saveFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        {
            return;
        }

        saveFile.write(ui->destCodeTxtBwor->toPlainText().toUtf8());
        saveFile.close();
    }
}
