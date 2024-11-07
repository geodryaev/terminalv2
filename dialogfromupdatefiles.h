#ifndef DIALOGFROMUPDATEFILES_H
#define DIALOGFROMUPDATEFILES_H

#include <QDialog>
#include <QFileDialog>
#include <QDir>
#include <QSettings>
#include <QDateTime>
namespace Ui {
class dialogfromupdatefiles;
}

class dialogfromupdatefiles : public QDialog
{
    Q_OBJECT

public:
    explicit dialogfromupdatefiles(QWidget *parent = nullptr);
    ~dialogfromupdatefiles();

private slots:
    void on_update_clicked();

signals:
    void changeData();

private:
    Ui::dialogfromupdatefiles *ui;
};

#endif // DIALOGFROMUPDATEFILES_H
