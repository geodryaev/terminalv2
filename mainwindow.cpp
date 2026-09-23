#include "QFile"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "passwd.h"
#include <QtCore/private/qzipreader_p.h>
#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QResizeEvent>

bool passwdCheack()
{
    passwd passwdsCheack;
    passwdsCheack.exec();
    return passwdsCheack.getStatus();
}

static bool appendHistory(const QString &departament)
{
    QFile file("history_dowload.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qWarning() << "Could not open history file:" << file.errorString();
        return false;
    }

    QJsonObject jObj;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isObject())
    {
        jObj = doc.object();
    }
    QJsonObject jObjHistory = jObj["history"].toObject();
    jObjHistory[QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch())] = departament;
    jObj["history"] = jObjHistory;

    file.resize(0);
    file.write(QJsonDocument(jObj).toJson());
    file.close();
    return true;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _countClick(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setTextPanel();

    _timer.setSingleShot(true);
    _timerClose.setSingleShot(true);
    _timerResetSelectDepart.setSingleShot(true);
    this->showFullScreen();
    this->setWindowModality(Qt::ApplicationModal);
    this->setStyleSheet("background-image: url(:/source/unnamed.jpg);  background-position: center; ");

    if (!QFileInfo::exists("settings.ini"))
    {
        _support.setDefaultSettings();
        qDebug() << " Сборос";
    }
    QList<QString> list = _support.getListDepartament();

    for (const QString &strElem : list)
    {
        new QListWidgetItem(strElem, ui->listDepartament);
    }

    ui->progressBar->hide();
    ui->menuBar->hide();
    ui->labelUnk->setStyleSheet("color: #FFCC66; font-size: 20px;");
    ui->centralWidget->setStyleSheet("background: transparent; color: #FFCC66; font-size: 16px;");
    ui->label_2->setStyleSheet("background: transparent; color: #FFCC66; font-size: 14px;");
    ui->listDepartament->setStyleSheet("background: transparent; color: #FFCC66; font-size: 14px;");
    ui->dowloadUP->setStyleSheet("background: transparent; color: #FFCC66; font-size: 14px; border: 3px solid #edff21; padding: 10px; border-radius: 5px;");
    ui->menuBar->setStyleSheet("background-color: black;color: white");




    QObject::connect(&_timer, &QTimer::timeout, this, [=](){
        _countClick = 0;
        qDebug() << "Первый таймер умер";

    });

    QObject::connect(&_timerClose, &QTimer::timeout, this, [=](){
        _countClick = 0;
        ui->menuBar->setVisible(false);
        qDebug() << "Второй таймер умер";
    });

    QObject::connect(ui->font2, &QPushButton::clicked, this, [=](){
        if(_countClick == 5 && _timer.isActive())
        {
            _timerClose.start(2*60*1000);
            ui->menuBar->setVisible(true);
            qDebug() << "Второй пошел";
        }
    });

    QObject::connect(ui->listDepartament, &QListWidget::itemSelectionChanged, this, [=](){
        if (!ui->listDepartament->selectedItems().isEmpty())
        {
            _timerResetSelectDepart.start(5000);
        }
    });

    QObject::connect(&_timerResetSelectDepart, &QTimer::timeout,this, [=](){
        ui->listDepartament->clearSelection();
        setTextPanel();
    });

}

MainWindow::~MainWindow()
{
    if (_zipThread)
    {
        _zipThread->quit();
        _zipThread->wait();
    }
    delete unzip;
    delete ui;
}

int CountDir(const QString &dirPath) {
    QDir dir(dirPath);
    int count = 0;
    if (!dir.exists()) {
        qWarning() << "Directory does not exist:" << dirPath;
        return 0;
    }

    // Считаем все файлы и директории рекурсивно (столько же шагов сделает removeDir)
    QFileInfoList files = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDir::DirsFirst);
    for (const QFileInfo &fileInfo : files) {
        count++;
        if (fileInfo.isDir()) {
            count += CountDir(fileInfo.absoluteFilePath());
        }
    }
    return count;
}

bool ThreadZip::removeDir(const QString &dirPath, int * step)
{
    QDir dir(dirPath);

    if (!dir.exists()) {
        qWarning() << "Directory does not exist:" << dirPath;
        return false;
    }

    QFileInfoList files = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDir::DirsFirst);
    for (const QFileInfo &fileInfo : files) {
        emit changePB(++(*step));
        if (fileInfo.isDir()) {
            if (!removeDir(fileInfo.absoluteFilePath(), step)) {
                return false;
            }
        } else {
            if (!QFile::remove(fileInfo.absoluteFilePath())) {
                qWarning() << "Could not remove file:" << fileInfo.absoluteFilePath();
                return false;
            }
        }
    }

    // Удаляем саму папку после очистки
    return dir.rmdir(dirPath);
}

void MainWindow::on_dowloadUP_clicked()
{
    if (_zipThread)
    {
        return;
    }

    QList <QListWidgetItem *> item = ui->listDepartament->selectedItems();
    if (item.isEmpty())
    {
        QMessageBox::information(nullptr, "Внимание","Вы не выбрали свое подразделение");
        return;
    }

    if (!QFile::exists("fileDir/update.zip"))
    {
        QMessageBox::information(nullptr, "Внимание", "Файла для загрузки нет!");
        return;
    }

    QSettings set("settings.ini", QSettings::IniFormat);
    set.beginGroup("AboutApp");
    QString pathToSave = set.value("pathToSave", "-112").toString();
    set.endGroup();

    if (pathToSave == "-112")
    {
        QMessageBox::information(nullptr, "Ошибка пути", "Нет пути сохранения, обращаемся к админу");
        return;
    }
    QDir cheakDir (pathToSave);
    if (!cheakDir.exists())
    {
        QMessageBox::information(nullptr, "Ошибка", "Хулиган, вставь флешку !!!");
        return;
    }

    const QString departament = item[0]->text();

    QMessageBox::information(nullptr,"Внимание","Обнволение началось");

    unzip = new ThreadZip(cheakDir.filePath("Обновление Dr.Web"));
    _zipThread = new QThread(this);
    unzip->moveToThread(_zipThread);

    ui->dowloadUP->setDisabled(true);
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(true);

    connect(_zipThread, &QThread::started, unzip, &ThreadZip::unZip);

    connect(unzip, &ThreadZip::complateOperation, this, [=](bool success, const QString &message){
        _zipThread->quit();
        if (success)
        {
            appendHistory(departament);
            QMessageBox::information(nullptr, "Внимание", "Обновление успешно загруженно");
        }
        else
        {
            QMessageBox::warning(nullptr, "Ошибка", message);
        }
        ui->progressBar->hide();
        ui->dowloadUP->setEnabled(true);
    });

    connect(_zipThread, &QThread::finished, this, [=](){
        delete unzip;
        unzip = nullptr;
        _zipThread->deleteLater();
        _zipThread = nullptr;
    });

    connect(unzip,&ThreadZip::changePB, this,[=](int k)
    {
        ui->progressBar->setValue(k);
    });

    connect(unzip,&ThreadZip::setPB, this, [=](int k){
        ui->progressBar->setRange(0,k);
    });
    _zipThread->start();
}

ThreadZip::ThreadZip(const QString outputDir)
{
    _outDir = outputDir;
}

void ThreadZip::unZip()
{
    QZipReader read("fileDir/update.zip");
    if (!read.exists() || !read.isReadable()) {
        emit complateOperation(false, "Не удалось открыть архив обновления");
        return;
    }

    QDir outputDir(_outDir);

    if (outputDir.exists()) {
        emit setPB(CountDir(_outDir));
        int step = 0;
        if (!removeDir(_outDir, &step)) {
            emit complateOperation(false, "Не удалось удалить старое обновление:\n" + _outDir);
            return;
        }
    }
    if (!QDir().mkpath(_outDir)) {
        emit complateOperation(false, "Не удалось создать папку:\n" + _outDir);
        return;
    }

    const QString rootPath = QDir::cleanPath(outputDir.absolutePath()) + "/";
    const QVector<QZipReader::FileInfo> allFiles = read.fileInfoList();
    int totalFiles = allFiles.size(), processedFiles = 0;

    emit setPB(totalFiles);
    emit changePB(0);

    for (const QZipReader::FileInfo &fileInfo : allFiles) {
        const QString filePath = QDir::cleanPath(outputDir.absoluteFilePath(fileInfo.filePath));

        // Не даём архиву писать за пределы папки назначения ("../")
        if (!filePath.startsWith(rootPath, Qt::CaseInsensitive)) {
            emit complateOperation(false, "Недопустимый путь в архиве:\n" + fileInfo.filePath);
            return;
        }

        if (fileInfo.isDir) {
            if (!QDir().mkpath(filePath)) {
                emit complateOperation(false, "Не удалось создать папку:\n" + filePath);
                return;
            }
        } else if (fileInfo.isFile) {
            QDir().mkpath(QFileInfo(filePath).absolutePath());
            QFile outFile(filePath);
            const QByteArray data = read.fileData(fileInfo.filePath);
            if (!outFile.open(QIODevice::WriteOnly) || outFile.write(data) != data.size()) {
                emit complateOperation(false, "Не удалось записать файл:\n" + filePath);
                return;
            }
            outFile.close();
        }
        processedFiles++;
        emit changePB(processedFiles);
    }
    read.close();

    emit complateOperation(true, QString());
}

void MainWindow::on_font1_clicked()
{
    ui->menuBar->setVisible(false);
    if (!_timer.isActive())
    {
        _timer.start(5000);
        qDebug() << "Первый пошел";
        _countClick++;
    }
    else if (_countClick == 4)
    {
        _countClick = 0;
        _timer.stop();
    }
    else
    {
        _countClick++;
    }
    qDebug() << "Кол-во нажатий" << _countClick;
}

void MainWindow::on_font2_clicked()
{
    if (_countClick == 4)
    {
        _countClick++;
    }
    else
    {
        _timer.stop();
        _countClick = 0;
        ui->menuBar->setVisible(false);
    }
}

void MainWindow::setTextPanel()
{
    QSettings set ("settings.ini", QSettings::IniFormat);
    set.beginGroup("UpdateInfo");
    QDateTime timeLastUpdate = set.value("date").toDateTime();
    if (!timeLastUpdate.isValid())
    {
        ui->dataUpdate->setText("Установите обновление");
    }
    else
    {
        const double sizeMB = set.value("size", 0).toLongLong() / 1024.0 / 1024.0;
        ui->dataUpdate->setText("Дата: " + timeLastUpdate.date().toString("dd.MM.yyyy") + "\nРазмер: " + QString::number(sizeMB, 'f', 1) + " MB");
    }
    set.endGroup();
}

void MainWindow::on_men_updat_triggered()
{
    if (passwdCheack())
    {
        dialogfromupdatefiles dil;
        connect(&dil, &dialogfromupdatefiles::changeData, this, &MainWindow::setTextPanel);
        dil.exec();
    }
}

void MainWindow::on_path_to_save_triggered()
{
    if (passwdCheack())
    {
        dialogsetpathtosave dil;
        dil.exec();
    }
}

void MainWindow::on_set_default_triggered()
{
    if (passwdCheack())
    {
        _support.setDefaultSettings();
        QMessageBox::information(nullptr,"Внимание", "Настройки сброшены");
    }
}

void MainWindow::on_view_gansta_triggered()
{
    if (passwdCheack())
    {
        listgansta dil;
        dil.exec();
    }
}

void MainWindow::on_about_po_triggered()
{
    if (passwdCheack())
    {
        aboutMe dil;
        dil.exec();
    }
}
