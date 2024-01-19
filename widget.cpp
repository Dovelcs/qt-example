#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    worker = new Worker;
    workerThread = new QThread(this);
    worker->moveToThread(workerThread);

    connect(workerThread, &QThread::started, worker, &Worker::worker);
    connect(worker,&Worker::textChanged,this,&Widget::updateTextBrowser);
}

Widget::~Widget()
{
    workerThread->quit();
    workerThread->wait();
    delete ui;
}


void Widget::updateTextBrowser(const QString &text)
{
    ui->text->append(text);
}

void Widget::on_start_clicked()
{
    if(!workerThread->isRunning())
    {
        workerThread->start();
    }

}

void Widget::on_stop_clicked()
{
    if(workerThread->isRunning())
    {
        worker->StopWork();
        workerThread->quit();
        workerThread->wait();
    }
}

void Widget::on_clear_clicked()
{
    ui->text->clear();
}
