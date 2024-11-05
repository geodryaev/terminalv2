#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QThread>
#include "QtWidgets"
#include "QFileInfo"
#include "QJsonDocument"
#include "QJsonArray"
#include "QJsonObject"
#include <QDateTime>
#include <QList>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include "QMainWindow"
#include "dialogfromupdatefiles.h"
#include "dialogsetpathtosave.h"
#include "widgetdelegate.h"
#include "qtimer.h"
#include <listgansta.h>
#include <QThread>
#include <QDateTime>

namespace Ui {
class MainWindow;
}


class ThreadZip: public QObject
{
    Q_OBJECT

public:
    explicit ThreadZip(const QString outputDir);
    ~ThreadZip(){}
public slots:
    void unZip();
    bool removeDir(const QString &dirPath, int * step);
signals:
    void changePB(int);
    void setPB(int);
    void complateOperation();
    private:
        QString _outDir;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_dowloadUP_clicked();

    void on_men_updat_triggered();

    void on_path_to_save_triggered();

    void on_set_default_triggered();

    void on_font1_clicked();

    void on_font2_clicked();

    void on_view_gansta_triggered();

private:
    QTimer _timer,_timerClose, _timerResetSelectDepart;
    int _countClick;
    Ui::MainWindow *ui;
    myWidget _support;
    QThread _thread;
    ThreadZip * unzip;
};


#endif // MAINWINDOW_H
