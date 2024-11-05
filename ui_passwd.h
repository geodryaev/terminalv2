/********************************************************************************
** Form generated from reading UI file 'passwd.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWD_H
#define UI_PASSWD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_passwd
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pb00;
    QPushButton *pb10;
    QPushButton *pb20;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pb01;
    QPushButton *pb11;
    QPushButton *pb21;
    QVBoxLayout *verticalLayout;
    QPushButton *pb02;
    QPushButton *pb12;
    QPushButton *pb22;
    QLabel *log_cheak;

    void setupUi(QDialog *passwd)
    {
        if (passwd->objectName().isEmpty())
            passwd->setObjectName(QStringLiteral("passwd"));
        passwd->resize(640, 480);
        label = new QLabel(passwd);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 631, 61));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(passwd);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 60, 581, 421));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pb00 = new QPushButton(layoutWidget);
        pb00->setObjectName(QStringLiteral("pb00"));
        pb00->setMinimumSize(QSize(50, 50));
        pb00->setMaximumSize(QSize(50, 50));

        verticalLayout_2->addWidget(pb00);

        pb10 = new QPushButton(layoutWidget);
        pb10->setObjectName(QStringLiteral("pb10"));
        pb10->setMinimumSize(QSize(50, 50));
        pb10->setMaximumSize(QSize(50, 50));

        verticalLayout_2->addWidget(pb10);

        pb20 = new QPushButton(layoutWidget);
        pb20->setObjectName(QStringLiteral("pb20"));
        pb20->setMinimumSize(QSize(50, 50));
        pb20->setMaximumSize(QSize(50, 50));

        verticalLayout_2->addWidget(pb20);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pb01 = new QPushButton(layoutWidget);
        pb01->setObjectName(QStringLiteral("pb01"));
        pb01->setMinimumSize(QSize(50, 50));
        pb01->setMaximumSize(QSize(50, 50));

        verticalLayout_3->addWidget(pb01);

        pb11 = new QPushButton(layoutWidget);
        pb11->setObjectName(QStringLiteral("pb11"));
        pb11->setMinimumSize(QSize(50, 50));
        pb11->setMaximumSize(QSize(50, 50));

        verticalLayout_3->addWidget(pb11);

        pb21 = new QPushButton(layoutWidget);
        pb21->setObjectName(QStringLiteral("pb21"));
        pb21->setMinimumSize(QSize(50, 50));
        pb21->setMaximumSize(QSize(50, 50));

        verticalLayout_3->addWidget(pb21);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        pb02 = new QPushButton(layoutWidget);
        pb02->setObjectName(QStringLiteral("pb02"));
        pb02->setMinimumSize(QSize(50, 50));
        pb02->setMaximumSize(QSize(50, 50));

        verticalLayout->addWidget(pb02);

        pb12 = new QPushButton(layoutWidget);
        pb12->setObjectName(QStringLiteral("pb12"));
        pb12->setMinimumSize(QSize(50, 50));
        pb12->setMaximumSize(QSize(50, 50));

        verticalLayout->addWidget(pb12);

        pb22 = new QPushButton(layoutWidget);
        pb22->setObjectName(QStringLiteral("pb22"));
        pb22->setMinimumSize(QSize(50, 50));
        pb22->setMaximumSize(QSize(50, 50));

        verticalLayout->addWidget(pb22);


        horizontalLayout->addLayout(verticalLayout);

        log_cheak = new QLabel(passwd);
        log_cheak->setObjectName(QStringLiteral("log_cheak"));
        log_cheak->setGeometry(QRect(420, 0, 221, 61));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setWeight(75);
        log_cheak->setFont(font1);

        retranslateUi(passwd);

        QMetaObject::connectSlotsByName(passwd);
    } // setupUi

    void retranslateUi(QDialog *passwd)
    {
        passwd->setWindowTitle(QApplication::translate("passwd", "Dialog", nullptr));
        label->setText(QApplication::translate("passwd", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        pb00->setText(QString());
        pb10->setText(QString());
        pb20->setText(QString());
        pb01->setText(QString());
        pb11->setText(QString());
        pb21->setText(QString());
        pb02->setText(QString());
        pb12->setText(QString());
        pb22->setText(QString());
        log_cheak->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class passwd: public Ui_passwd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWD_H
