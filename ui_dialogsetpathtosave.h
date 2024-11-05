/********************************************************************************
** Form generated from reading UI file 'dialogsetpathtosave.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSETPATHTOSAVE_H
#define UI_DIALOGSETPATHTOSAVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialogsetpathtosave
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *dialogsetpathtosave)
    {
        if (dialogsetpathtosave->objectName().isEmpty())
            dialogsetpathtosave->setObjectName(QStringLiteral("dialogsetpathtosave"));
        dialogsetpathtosave->resize(600, 250);
        buttonBox = new QDialogButtonBox(dialogsetpathtosave);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 200, 581, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(dialogsetpathtosave);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 50, 581, 33));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(20);
        font.setBold(true);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        retranslateUi(dialogsetpathtosave);
        QObject::connect(buttonBox, SIGNAL(accepted()), dialogsetpathtosave, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dialogsetpathtosave, SLOT(reject()));

        QMetaObject::connectSlotsByName(dialogsetpathtosave);
    } // setupUi

    void retranslateUi(QDialog *dialogsetpathtosave)
    {
        dialogsetpathtosave->setWindowTitle(QApplication::translate("dialogsetpathtosave", "Dialog", nullptr));
        label->setText(QApplication::translate("dialogsetpathtosave", "\320\222\321\213\320\261\320\265\321\200\320\270 \321\204\320\273\320\265\321\210\320\272\321\203", nullptr));
        pushButton->setText(QApplication::translate("dialogsetpathtosave", "\320\236\320\261\320\267\320\276\321\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dialogsetpathtosave: public Ui_dialogsetpathtosave {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSETPATHTOSAVE_H
