#ifndef DIALOGSETPATHTOSAVE_H
#define DIALOGSETPATHTOSAVE_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include <QSettings>

namespace Ui {
class dialogsetpathtosave;
}

class dialogsetpathtosave : public QDialog
{
    Q_OBJECT

public:
    explicit dialogsetpathtosave(QWidget *parent = nullptr);
    ~dialogsetpathtosave();

private slots:
    void on_pushButton_clicked();

private:
    Ui::dialogsetpathtosave *ui;
};

#endif // DIALOGSETPATHTOSAVE_H
