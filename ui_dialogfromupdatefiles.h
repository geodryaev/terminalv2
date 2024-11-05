/********************************************************************************
** Form generated from reading UI file 'dialogfromupdatefiles.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGFROMUPDATEFILES_H
#define UI_DIALOGFROMUPDATEFILES_H

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

class Ui_dialogfromupdatefiles
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *update;

    void setupUi(QDialog *dialogfromupdatefiles)
    {
        if (dialogfromupdatefiles->objectName().isEmpty())
            dialogfromupdatefiles->setObjectName(QStringLiteral("dialogfromupdatefiles"));
        dialogfromupdatefiles->resize(600, 250);
        buttonBox = new QDialogButtonBox(dialogfromupdatefiles);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(0, 180, 561, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(dialogfromupdatefiles);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 40, 591, 33));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(20);
        font.setBold(true);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        update = new QPushButton(layoutWidget);
        update->setObjectName(QStringLiteral("update"));

        horizontalLayout->addWidget(update);


        retranslateUi(dialogfromupdatefiles);
        QObject::connect(buttonBox, SIGNAL(accepted()), dialogfromupdatefiles, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dialogfromupdatefiles, SLOT(reject()));

        QMetaObject::connectSlotsByName(dialogfromupdatefiles);
    } // setupUi

    void retranslateUi(QDialog *dialogfromupdatefiles)
    {
        dialogfromupdatefiles->setWindowTitle(QApplication::translate("dialogfromupdatefiles", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260 \320\276\320\261\320\275\320\276\320\262\320\273\320\265\320\275\320\270\321\217", nullptr));
        label->setText(QApplication::translate("dialogfromupdatefiles", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\260\321\200\321\205\320\270\320\262 .rar", nullptr));
        update->setText(QApplication::translate("dialogfromupdatefiles", "\320\236\320\261\320\267\320\276\321\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dialogfromupdatefiles: public Ui_dialogfromupdatefiles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGFROMUPDATEFILES_H
