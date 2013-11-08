/********************************************************************************
** Form generated from reading UI file 'hostedit.ui'
**
** Created: Thu May 30 15:52:43 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOSTEDIT_H
#define UI_HOSTEDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *vert_main;
    QHBoxLayout *horiz_main;
    QVBoxLayout *vert_Address;
    QLabel *lblAddress;
    QLineEdit *linAddress;
    QVBoxLayout *vert_Port;
    QLabel *lblPort;
    QLineEdit *linPort;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(436, 95);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        vert_main = new QVBoxLayout();
        vert_main->setObjectName(QString::fromUtf8("vert_main"));
        horiz_main = new QHBoxLayout();
        horiz_main->setObjectName(QString::fromUtf8("horiz_main"));
        vert_Address = new QVBoxLayout();
        vert_Address->setObjectName(QString::fromUtf8("vert_Address"));
        lblAddress = new QLabel(Dialog);
        lblAddress->setObjectName(QString::fromUtf8("lblAddress"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblAddress->sizePolicy().hasHeightForWidth());
        lblAddress->setSizePolicy(sizePolicy);

        vert_Address->addWidget(lblAddress);

        linAddress = new QLineEdit(Dialog);
        linAddress->setObjectName(QString::fromUtf8("linAddress"));
        sizePolicy.setHeightForWidth(linAddress->sizePolicy().hasHeightForWidth());
        linAddress->setSizePolicy(sizePolicy);

        vert_Address->addWidget(linAddress);


        horiz_main->addLayout(vert_Address);

        vert_Port = new QVBoxLayout();
        vert_Port->setObjectName(QString::fromUtf8("vert_Port"));
        lblPort = new QLabel(Dialog);
        lblPort->setObjectName(QString::fromUtf8("lblPort"));
        sizePolicy.setHeightForWidth(lblPort->sizePolicy().hasHeightForWidth());
        lblPort->setSizePolicy(sizePolicy);
        lblPort->setMaximumSize(QSize(200, 16777215));

        vert_Port->addWidget(lblPort);

        linPort = new QLineEdit(Dialog);
        linPort->setObjectName(QString::fromUtf8("linPort"));
        sizePolicy.setHeightForWidth(linPort->sizePolicy().hasHeightForWidth());
        linPort->setSizePolicy(sizePolicy);
        linPort->setMaximumSize(QSize(200, 16777215));

        vert_Port->addWidget(linPort);


        horiz_main->addLayout(vert_Port);


        vert_main->addLayout(horiz_main);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        vert_main->addWidget(buttonBox);


        gridLayout->addLayout(vert_main, 0, 0, 1, 1);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        lblAddress->setText(QApplication::translate("Dialog", "Server Address", 0, QApplication::UnicodeUTF8));
        linAddress->setText(QApplication::translate("Dialog", "localhost", 0, QApplication::UnicodeUTF8));
        lblPort->setText(QApplication::translate("Dialog", "Port", 0, QApplication::UnicodeUTF8));
        linPort->setText(QApplication::translate("Dialog", "15000", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOSTEDIT_H
