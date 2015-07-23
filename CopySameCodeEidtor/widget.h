#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void slot_OpenModelFileBtn_Clicked();
    void slot_ReplaceSourceBtn_Clicked();
    void slot_ExportFileBtn_Clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
