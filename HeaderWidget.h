#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>

#include "Core/ServiceTime.h"

namespace Ui {
class HeaderWidget;
}

class HeaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderWidget(QWidget *parent = nullptr);
    ~HeaderWidget();

private slots:
    void on_startPause_button_clicked(bool checked);
    void on_increase_button_clicked();

    void on_decrease_button_clicked();

public slots:
    void setDatetime(ServiceTime *);

signals:
    void sendLogMessage(QString msg);
    void startSimulation();
    void stopSimulation();

private:
    Ui::HeaderWidget *ui;


};

#endif // HEADERWIDGET_H
