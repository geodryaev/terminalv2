#include "passwd.h"
#include "ui_passwd.h"

QPair<int,int> getIDbutton(QPushButton *btn)
{
    QString str = btn->objectName();
    if (btn->objectName() == "pb00")
    {
        return QPair<int, int>(0,0);
    }
    if (btn->objectName() == "pb01")
    {
        return QPair<int, int>(0,1);
    }
    if (btn->objectName() == "pb02")
    {
        return QPair<int, int>(0,2);
    }

    if (btn->objectName() == "pb10")
    {
        return QPair<int, int>(1,0);
    }
    if (btn->objectName() == "pb11")
    {
        return QPair<int, int>(1,1);
    }
    if (btn->objectName() == "pb12")
    {
        return QPair<int, int>(1,2);
    }

    if (btn->objectName() == "pb20")
    {
        return QPair<int, int>(2,0);
    }
    if (btn->objectName() == "pb21")
    {
        return QPair<int, int>(2,1);
    }
    if (btn->objectName() == "pb22")
    {
        return QPair<int, int>(2,2);
    }

    return QPair<int,int>(-1,-1);
}

bool acceptFirst(QVector<QPair<int, int>> send)
{
    QVector<QPair<int, int>> answerFirst = {{0,0},{1,1},{2,2},{2,0},{0,2}};
    return send == answerFirst;
}

bool acceptSecond(QVector<QPair<int, int>> send)
{
    QVector<QPair<int, int>> answerFirst = {{0,0},{1,1},{0,2},{2,0}};
    return send == answerFirst;
}

bool acceptThird(QVector<QPair<int, int>> send)
{
    QVector<QPair<int, int>> answerFirst = {{0,0},{1,0},{2,0},{1,1},{0,2},{1,2},{2,2}};
    return send == answerFirst;
}

passwd::passwd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::passwd),
    _result(false),
    _status(p_first)
{
    ui->setupUi(this);
    setModal(true);
    _vbtn.append(ui->pb00);
    _vbtn.append(ui->pb01);
    _vbtn.append(ui->pb02);
    _vbtn.append(ui->pb10);
    _vbtn.append(ui->pb11);
    _vbtn.append(ui->pb12);
    _vbtn.append(ui->pb20);
    _vbtn.append(ui->pb21);
    _vbtn.append(ui->pb22);
    clearBtn();
    connect(ui->pb00,&QPushButton::clicked, this, &passwd::setResult);
    connect(ui->pb01,&QPushButton::clicked, this, &passwd::setResult);
    connect(ui->pb02,&QPushButton::clicked, this, &passwd::setResult);
    connect(ui->pb10,&QPushButton::clicked, this, &passwd::setResult);
    connect(ui->pb11,&QPushButton::clicked, this, &passwd::setResult);
    connect(ui->pb12,&QPushButton::clicked, this, &passwd::setResult);
    connect(ui->pb20,&QPushButton::clicked, this, &passwd::setResult);
    connect(ui->pb21,&QPushButton::clicked, this, &passwd::setResult);
    connect(ui->pb22,&QPushButton::clicked, this, &passwd::setResult);
    _countEnter =0;
}

void passwd::setResult()
{
    QPushButton *btn;
    _countEnter++;
    if (_countEnter < 9)
    {
        switch (_status) {
        case p_first:
            btn = qobject_cast<QPushButton*>(sender());
            _send.push_back(getIDbutton(btn));
            btn->setStyleSheet("background-color: green");
            if (acceptFirst(_send))
            {
                _send = {};
                ui->log_cheak->setText("☺");
                _countEnter = 0;
                _status = p_second;
                clearBtn();
            }
            break;
        case p_second:
            btn = qobject_cast<QPushButton*>(sender());
            _send.push_back(getIDbutton(btn));
            btn->setStyleSheet("background-color: green");
            if (acceptSecond(_send))
            {
                _send = {};
                ui->log_cheak->setText("☺☺");
                _countEnter = 0;
                _status = p_third;
                clearBtn();
            }
            break;
        case p_third:
            btn = qobject_cast<QPushButton*>(sender());
            _send.push_back(getIDbutton(btn));
            btn->setStyleSheet("background-color: green");
            if (acceptThird(_send))
            {
                _send = {};
                ui->log_cheak->setText("☺☺☺");
                _countEnter = 0;
                _status = p_second;
                clearBtn();
                QMessageBox::information(nullptr, "Password","Успешно");
                _result
                        = true;
                close();
            }
            break;
        default:
            return;
        }

    }
    else
    {
        close();
    }
}

void passwd::clearBtn()
{
    ui->pb00->setStyleSheet("background-color: white");
    ui->pb01->setStyleSheet("background-color: white");
    ui->pb02->setStyleSheet("background-color: white");
    ui->pb10->setStyleSheet("background-color: white");
    ui->pb11->setStyleSheet("background-color: white");
    ui->pb12->setStyleSheet("background-color: white");
    ui->pb20->setStyleSheet("background-color: white");
    ui->pb21->setStyleSheet("background-color: white");
    ui->pb22->setStyleSheet("background-color: white");
}
passwd::~passwd()
{
    delete ui;
}
