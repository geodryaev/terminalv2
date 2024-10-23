#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtWidgets"
#include "QFileInfo"
#include "QJsonDocument"
#include "QJsonArray"
#include "QJsonObject"
#include <QDateTime>
#include <QList>
#include <QMessageBox>

#include "QMainWindow"
#include "dialogfromupdatefiles.h"
#include "dialogsetpathtosave.h"
#include "widgetdelegate.h"

namespace Ui {
class MainWindow;
}

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
