#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include <QThread>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
class Worker;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_start_clicked();

    void on_stop_clicked();

    void on_clear_clicked();

private:
    Ui::Widget *ui;
    QThread *workerThread;
    Worker *worker;
    void updateTextBrowser(const QString &text);
};

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker(){

    }

    void worker(){
        continueRuning = true;
        while (continueRuning)
        {
            emit textChanged("hello world");
            QThread::msleep(1);
        }

    }

    void StopWork(){
        continueRuning = false;
    }


signals:
    void textChanged(const QString &text);

private:
    std::atomic<bool> continueRuning;

};

#endif // WIDGET_H
