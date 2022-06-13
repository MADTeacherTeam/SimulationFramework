#include "HeaderWidget.h"
#include "ui_HeaderWidget.h"
#include "QIcon"
#include "QDebug"

#include "Core/Logger.h"

HeaderWidget::HeaderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeaderWidget)
{
    ui->setupUi(this);
    setDatetime(ServiceTime::getInstance());
}

HeaderWidget::~HeaderWidget()
{
    delete ui;
}

void HeaderWidget::on_startPause_button_clicked(bool checked)
{
    if (checked) {
        this->ui->startPause_button->setIcon(QIcon(":/header_icons/pause.png"));
        Logger() << "Start simulation";
        emit startSimulation();
    } else {
        this->ui->startPause_button->setIcon(QIcon(":/header_icons/play.png"));
        Logger() << "Pause simulation";
        emit stopSimulation();
    }
}

void HeaderWidget::setDatetime(ServiceTime * time)
{
    auto date {time->getDays()};
    auto hours{time->getHours()};
    auto minutes{time->getMinutes()};
    auto seconds{time->getSeconds()};
    auto month{time->getMonth()};
    auto year{time->getYear()};
    QString toRet = " Day: %1 Month: %2 Year: %3 Time: %4:%5:%6 ";

    this->ui->datetime_label->setText(toRet.arg(date, 2, 10, QLatin1Char('0')).arg(month, 2, 10, QLatin1Char('0')).arg(year, 4, 10, QLatin1Char('0')).arg(hours, 2, 10, QLatin1Char('0')).arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0')));
    this->update();
}

void HeaderWidget::on_increase_button_clicked()
{
    ServiceTime::getInstance()->increaseStepTime();
}



void HeaderWidget::on_decrease_button_clicked()
{
    ServiceTime::getInstance()->decreaseStepTime();
}
