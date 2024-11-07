#include "QFile"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "passwd.h"
#include "QtGui/private/qzipreader_p.h"
#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QResizeEvent>

bool passwdCheack()
{
    passwd passwdsCheack;
    passwdsCheack.show();
    passwdsCheack.exec();
    return passwdsCheack.getStatus();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _countClick(0),
    ui(new Ui::MainWindow),
    _thread(new QThread)
{
    ui->setupUi(this);

    emit setTextPanel();

    _timer.setSingleShot(true);
    _timer.setSingleShot(true);
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

    QStringList qslis;
    for (QString strElem : list)
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
        if(_countClick == 5 and _timer.isActive())
        {
            _timerClose.start(2*60*1000);
            ui->menuBar->setVisible(true);
            qDebug() << "Второй пошел";
        }
    });

    QObject::connect(ui->listDepartament,&QListWidget::clicked, this,[=](){
        _timerResetSelectDepart.start(5000);
    });

    QObject::connect(&_timerResetSelectDepart, &QTimer::timeout,this, [=](){
        ui->listDepartament->reset();
        QSettings set ("settings.ini", QSettings::IniFormat);
        set.beginGroup("UpdateInfo");
        QDateTime timeLastUpdate( set.value("date", QDateTime::fromTime_t(50)).toDateTime());
        if (timeLastUpdate.date() == QDateTime::fromTime_t(50).date())
        {
            ui->dataUpdate->setText("Установите обновление");
        }
        else
        {
            ui->dataUpdate->setText("Дата: " + timeLastUpdate.date().toString() + "\nРазмер: " + QString::number(set.value("size", -1).toInt() / 1024 / 1024 ) + " MB");

        }
        qDebug() << timeLastUpdate.date().toString();
        set.endGroup();
    });

}

MainWindow::~MainWindow()
{
    delete unzip;
    delete ui;
}


QVector<QString> getDir(QString path)
{
    QVector<QString> answer;
    path = path.trimmed();
    path = path.remove(0, 4);
    qDebug() << path;
    while ( -1 != path.indexOf('/'))
    {
        QString str = path.left(path.indexOf('/'));
        if (str.indexOf('.') == -1){
            answer.push_back(str);
        }
        qDebug() << "Директрория"  << path.indexOf('/') <<str << path.indexOf('/')+1;
        path = path.remove(0, path.indexOf('/')+1);
    }
    if (path.indexOf('.') != -1){
        answer.push_back(path);
    }
    answer.push_back(path);

    return answer;
}

void mkDirs(QVector<QString> dirs, QString path)
{
    QString hereDir = path.left(4);
    foreach (QString dir, dirs) {
        QDir mkdirs(hereDir + dir);
        if (!mkdirs.exists())
        {
            mkdirs.mkdir(hereDir + dir);
        }
        hereDir+="\\"+dir;
    }
}

int CountDir(const QString &dirPath) {
    QDir dir(dirPath);
    int count = 1;
    if (!dir.exists()) {
        qWarning() << "Directory does not exist:" << dirPath;
        return 0;
    }

    // Удаляем все файлы и директории рекурсивно
    QFileInfoList files = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDir::DirsFirst);
    for (const QFileInfo &fileInfo : files) {
        if (fileInfo.isDir()) {
            // Рекурсивно удаляем подкаталог
            count += CountDir(fileInfo.absoluteFilePath());
        } else
        {
            count++;
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


    ui->progressBar->setVisible(true);
    QList <QListWidgetItem *> item = ui->listDepartament->selectedItems();
    if (item.isEmpty())
    {
        QMessageBox::information(nullptr, "Внимание","Вы не выбрали свое подразделение");
        ui->progressBar->hide();
    }
    else
    {
        QFile fileUpload("fileDir/update.zip");
        if (!fileUpload.exists())
        {
            QMessageBox::information(nullptr, "Внимание", "Файла для загрузки нет!");
            ui->progressBar->hide();
        }
        else {
            QSettings set("settings.ini", QSettings::IniFormat);
            set.beginGroup("AboutApp");
            QString pathToSave = set.value("pathToSave", "-112").toString();


            if (pathToSave == "-112")
            {
                QMessageBox::information(nullptr, "Ошибка пути", "Нет пути сохранения, обращаемся к админу");
                ui->progressBar->hide();
                return;
            }
            QDir cheakDir (pathToSave);
            if (!cheakDir.exists())
            {
                QMessageBox::information(nullptr, "Ошибка", "Хулиган, вставь флешку !!!");
                ui->progressBar->hide();
                return;
            }
            QFile file("history_dowload.json");
            if (file.open(QIODevice::ReadWrite) | QIODevice::Text)
            {
                QJsonDocument doc ;
                QJsonObject jObj;
                QJsonObject jObjHistory;
                if (file.size()>0)
                {
                    file.seek(0);
                    QByteArray read = file.readAll();
                    doc = QJsonDocument::fromJson(read);
                    if (doc.isObject())
                    {
                        jObj = doc.object();
                    }
                }
                jObjHistory = jObj["history"].toObject();
                jObjHistory [QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch())] = item[0]->text();
                jObj["history"] = jObjHistory;
                doc = QJsonDocument(jObj);
                file.resize(0);
                file.write(doc.toJson());
                file.close();
            }

            QMessageBox::information(nullptr,"Внимание","Обнволение началось");

            unzip = new ThreadZip(pathToSave+ "Обновление Dr.Web");
            ui->progressBar->setVisible(true);
            ui->progressBar->setValue(0);
            QThread *thread = new QThread(this);
            unzip->moveToThread(thread);
            connect(thread, &QThread::started, this, [=](){
                ui->dowloadUP->setDisabled(true);
                qDebug() << "Disable Button";
            });
            connect(thread, &QThread::started, unzip, &ThreadZip::unZip);

            connect(unzip,&ThreadZip::complateOperation,this, [=](){
                QMessageBox::information(nullptr,"Внимание","Обновление успешно загруженно");
                ui->progressBar->hide();
                ui->dowloadUP->setEnabled(true);
            });

            connect(unzip,&ThreadZip::changePB, this,[=](int k)
            {
                ui->progressBar->setValue(k);
            });

            connect(unzip,&ThreadZip::setPB, this, [=](int k){
                ui->progressBar->setRange(0,k);
            });
            thread->start();
        }
    }
}

ThreadZip::ThreadZip(const QString outputDir)
{
    _outDir = outputDir;
}

void ThreadZip::unZip()
{
    QZipReader read("fileDir/update.zip");
    if (read.isReadable()) {
        if (!read.exists()) {
            return;
        }

        QString outputDirPath = _outDir;
        QDir outputDir(outputDirPath);

        if (!outputDir.exists()) {
            outputDir.mkpath(outputDirPath);
        }
        else
        {
            emit setPB(CountDir(outputDirPath));
            int step = 0;
            removeDir(outputDirPath, &step);
            outputDir.mkpath(outputDirPath);
            //            QApplication::processEvents();
        }

        const QVector<QZipReader::FileInfo> allFiles = read.fileInfoList();
        int totalFiles = allFiles.size(), processedFiles = 0;

        setPB(totalFiles);
        changePB(0);

        for (const QZipReader::FileInfo &fileInfo : allFiles) {
            QString filePath = outputDirPath + "/" + fileInfo.filePath;

            if (fileInfo.isDir) {
                QDir().mkpath(filePath);
            } else if (fileInfo.isFile) {
                QFile outFile(filePath);
                if (outFile.open(QIODevice::WriteOnly)) {
                    outFile.write(read.fileData(fileInfo.filePath));
                    outFile.close();
                }
            }
            processedFiles++;
            changePB(processedFiles);
        }
        read.close();

        complateOperation();
    } else {
        complateOperation();
        return;
    }
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
    {
        QSettings set ("settings.ini", QSettings::IniFormat);
        set.beginGroup("UpdateInfo");
        QDateTime timeLastUpdate( set.value("date", QDateTime::fromTime_t(50)).toDateTime());
        if (timeLastUpdate.date() == QDateTime::fromTime_t(50).date())
        {
            ui->dataUpdate->setText("Установите обновление");
        }
        else
        {
            ui->dataUpdate->setText("Дата: " + timeLastUpdate.date().toString() + "\nРазмер: " + QString::number(set.value("size", -1).toInt() / 1024 / 1024 ) + " MB");

        }
        qDebug() << timeLastUpdate.date().toString();
        set.endGroup();
    }
}
void MainWindow::on_men_updat_triggered()
{
    //    if (passwdCheack())                 ---- заменить
    if (passwdCheack())
    {
        dialogfromupdatefiles dil;
        connect(&dil, &dialogfromupdatefiles::changeData, this, &MainWindow::setTextPanel);

        dil.show();
        dil.exec();
    }
}

void MainWindow::on_path_to_save_triggered()
{
    if (passwdCheack())
    {
        dialogsetpathtosave dil;
        dil.show();
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
    dil.show();
    dil.exec();
    }
}

void MainWindow::on_about_po_triggered()
{
    if (passwdCheack())
    {
    aboutMe dil;
    dil.show();
    dil.exec();
    }
}
