/********************************************************************************
** Form generated from reading UI file 'communicationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMUNICATIONWINDOW_H
#define UI_COMMUNICATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CommunicationWindow
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Cancel;
    QPushButton *pushButton_Continue;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_Search;
    QPushButton *pushButton_Connect;
    QPushButton *pushButton_Disconnect;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLabel *label_ConnectionStatus;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QComboBox *comboBox_Devices;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_Bluetooth;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line_2;
    QFrame *line;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_Baud;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *comboBox_Bits;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *comboBox_Parity;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *comboBox_Stop;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *comboBox_Control;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QTextBrowser *textBrowser_Logs;
    QPushButton *pushButton_Clear;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *CommunicationWindow)
    {
        if (CommunicationWindow->objectName().isEmpty())
            CommunicationWindow->setObjectName(QString::fromUtf8("CommunicationWindow"));
        CommunicationWindow->resize(900, 649);
        CommunicationWindow->setMinimumSize(QSize(900, 649));
        CommunicationWindow->setMaximumSize(QSize(900, 649));
        gridLayout = new QGridLayout(CommunicationWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        pushButton_Cancel = new QPushButton(CommunicationWindow);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));

        horizontalLayout_9->addWidget(pushButton_Cancel);

        pushButton_Continue = new QPushButton(CommunicationWindow);
        pushButton_Continue->setObjectName(QString::fromUtf8("pushButton_Continue"));

        horizontalLayout_9->addWidget(pushButton_Continue);


        gridLayout->addLayout(horizontalLayout_9, 9, 0, 1, 4);

        groupBox_3 = new QGroupBox(CommunicationWindow);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        pushButton_Search = new QPushButton(groupBox_3);
        pushButton_Search->setObjectName(QString::fromUtf8("pushButton_Search"));

        horizontalLayout_7->addWidget(pushButton_Search);

        pushButton_Connect = new QPushButton(groupBox_3);
        pushButton_Connect->setObjectName(QString::fromUtf8("pushButton_Connect"));

        horizontalLayout_7->addWidget(pushButton_Connect);

        pushButton_Disconnect = new QPushButton(groupBox_3);
        pushButton_Disconnect->setObjectName(QString::fromUtf8("pushButton_Disconnect"));

        horizontalLayout_7->addWidget(pushButton_Disconnect);


        gridLayout_3->addLayout(horizontalLayout_7, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        label_ConnectionStatus = new QLabel(groupBox_3);
        label_ConnectionStatus->setObjectName(QString::fromUtf8("label_ConnectionStatus"));

        horizontalLayout_6->addWidget(label_ConnectionStatus);


        gridLayout_3->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_8->addWidget(label_7);

        comboBox_Devices = new QComboBox(groupBox_3);
        comboBox_Devices->setObjectName(QString::fromUtf8("comboBox_Devices"));

        horizontalLayout_8->addWidget(comboBox_Devices);


        gridLayout_3->addLayout(horizontalLayout_8, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_3, 6, 0, 1, 2);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_Bluetooth = new QLabel(CommunicationWindow);
        label_Bluetooth->setObjectName(QString::fromUtf8("label_Bluetooth"));
        label_Bluetooth->setMinimumSize(QSize(0, 0));

        horizontalLayout_10->addWidget(label_Bluetooth);

        label_8 = new QLabel(CommunicationWindow);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QFont font;
        font.setPointSize(13);
        label_8->setFont(font);

        horizontalLayout_10->addWidget(label_8);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_10, 0, 0, 1, 4);

        line_2 = new QFrame(CommunicationWindow);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 1, 0, 2, 4);

        line = new QFrame(CommunicationWindow);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 8, 0, 1, 4);

        groupBox = new QGroupBox(CommunicationWindow);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox_Baud = new QComboBox(groupBox);
        comboBox_Baud->addItem(QString());
        comboBox_Baud->addItem(QString());
        comboBox_Baud->addItem(QString());
        comboBox_Baud->addItem(QString());
        comboBox_Baud->addItem(QString());
        comboBox_Baud->addItem(QString());
        comboBox_Baud->addItem(QString());
        comboBox_Baud->addItem(QString());
        comboBox_Baud->setObjectName(QString::fromUtf8("comboBox_Baud"));
        comboBox_Baud->setMinimumSize(QSize(200, 0));

        horizontalLayout->addWidget(comboBox_Baud);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        comboBox_Bits = new QComboBox(groupBox);
        comboBox_Bits->addItem(QString());
        comboBox_Bits->addItem(QString());
        comboBox_Bits->addItem(QString());
        comboBox_Bits->addItem(QString());
        comboBox_Bits->addItem(QString());
        comboBox_Bits->setObjectName(QString::fromUtf8("comboBox_Bits"));
        comboBox_Bits->setMinimumSize(QSize(200, 0));

        horizontalLayout_2->addWidget(comboBox_Bits);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        comboBox_Parity = new QComboBox(groupBox);
        comboBox_Parity->addItem(QString());
        comboBox_Parity->addItem(QString());
        comboBox_Parity->addItem(QString());
        comboBox_Parity->addItem(QString());
        comboBox_Parity->addItem(QString());
        comboBox_Parity->addItem(QString());
        comboBox_Parity->setObjectName(QString::fromUtf8("comboBox_Parity"));
        comboBox_Parity->setMinimumSize(QSize(200, 0));

        horizontalLayout_3->addWidget(comboBox_Parity);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        comboBox_Stop = new QComboBox(groupBox);
        comboBox_Stop->addItem(QString());
        comboBox_Stop->addItem(QString());
        comboBox_Stop->addItem(QString());
        comboBox_Stop->addItem(QString());
        comboBox_Stop->setObjectName(QString::fromUtf8("comboBox_Stop"));
        comboBox_Stop->setMinimumSize(QSize(200, 0));

        horizontalLayout_4->addWidget(comboBox_Stop);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        comboBox_Control = new QComboBox(groupBox);
        comboBox_Control->addItem(QString());
        comboBox_Control->addItem(QString());
        comboBox_Control->addItem(QString());
        comboBox_Control->addItem(QString());
        comboBox_Control->setObjectName(QString::fromUtf8("comboBox_Control"));
        comboBox_Control->setMinimumSize(QSize(200, 0));

        horizontalLayout_5->addWidget(comboBox_Control);


        verticalLayout->addLayout(horizontalLayout_5);


        gridLayout->addWidget(groupBox, 4, 0, 1, 2);

        groupBox_2 = new QGroupBox(CommunicationWindow);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        textBrowser_Logs = new QTextBrowser(groupBox_2);
        textBrowser_Logs->setObjectName(QString::fromUtf8("textBrowser_Logs"));

        gridLayout_2->addWidget(textBrowser_Logs, 0, 0, 1, 1);

        pushButton_Clear = new QPushButton(groupBox_2);
        pushButton_Clear->setObjectName(QString::fromUtf8("pushButton_Clear"));

        gridLayout_2->addWidget(pushButton_Clear, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 4, 3, 3, 1);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 3, 0, 1, 4);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 7, 0, 1, 4);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 4, 2, 3, 1);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 5, 0, 1, 2);


        retranslateUi(CommunicationWindow);

        QMetaObject::connectSlotsByName(CommunicationWindow);
    } // setupUi

    void retranslateUi(QDialog *CommunicationWindow)
    {
        CommunicationWindow->setWindowTitle(QApplication::translate("CommunicationWindow", "\305\201\304\205czenie", nullptr));
        pushButton_Cancel->setText(QApplication::translate("CommunicationWindow", "Anuluj", nullptr));
        pushButton_Continue->setText(QApplication::translate("CommunicationWindow", "Dalej", nullptr));
        groupBox_3->setTitle(QApplication::translate("CommunicationWindow", "Obs\305\202uga po\305\202\304\205czenia", nullptr));
        pushButton_Search->setText(QApplication::translate("CommunicationWindow", "Szukaj urz\304\205dze\305\204", nullptr));
        pushButton_Connect->setText(QApplication::translate("CommunicationWindow", "Po\305\202\304\205cz", nullptr));
        pushButton_Disconnect->setText(QApplication::translate("CommunicationWindow", "Roz\305\202\304\205cz", nullptr));
        label_6->setText(QApplication::translate("CommunicationWindow", "Status po\305\202\304\205czenia:", nullptr));
        label_ConnectionStatus->setText(QApplication::translate("CommunicationWindow", "brak", nullptr));
        label_7->setText(QApplication::translate("CommunicationWindow", "Znalezione urz\304\205dzenia:", nullptr));
        label_Bluetooth->setText(QApplication::translate("CommunicationWindow", "Bluetooth.png", nullptr));
        label_8->setText(QApplication::translate("CommunicationWindow", "Nawi\304\205zywanie po\305\202\304\205czenia bezprzewodowego z robotem", nullptr));
        groupBox->setTitle(QApplication::translate("CommunicationWindow", "Parametry transmisji", nullptr));
        label->setText(QApplication::translate("CommunicationWindow", "Szybko\305\233\304\207 transmisji:", nullptr));
        comboBox_Baud->setItemText(0, QApplication::translate("CommunicationWindow", "1200", nullptr));
        comboBox_Baud->setItemText(1, QApplication::translate("CommunicationWindow", "4800", nullptr));
        comboBox_Baud->setItemText(2, QApplication::translate("CommunicationWindow", "9600", nullptr));
        comboBox_Baud->setItemText(3, QApplication::translate("CommunicationWindow", "19200", nullptr));
        comboBox_Baud->setItemText(4, QApplication::translate("CommunicationWindow", "38400", nullptr));
        comboBox_Baud->setItemText(5, QApplication::translate("CommunicationWindow", "57600", nullptr));
        comboBox_Baud->setItemText(6, QApplication::translate("CommunicationWindow", "115200", nullptr));
        comboBox_Baud->setItemText(7, QApplication::translate("CommunicationWindow", "Nieznane", nullptr));

        label_2->setText(QApplication::translate("CommunicationWindow", "Ilo\305\233\304\207 bit\303\263w:", nullptr));
        comboBox_Bits->setItemText(0, QApplication::translate("CommunicationWindow", "5 bit\303\263w", nullptr));
        comboBox_Bits->setItemText(1, QApplication::translate("CommunicationWindow", "6 bit\303\263w", nullptr));
        comboBox_Bits->setItemText(2, QApplication::translate("CommunicationWindow", "7 bit\303\263w", nullptr));
        comboBox_Bits->setItemText(3, QApplication::translate("CommunicationWindow", "8 bit\303\263w", nullptr));
        comboBox_Bits->setItemText(4, QApplication::translate("CommunicationWindow", "Nieznane", nullptr));

        label_3->setText(QApplication::translate("CommunicationWindow", "Kontrola parzysto\305\233ci:", nullptr));
        comboBox_Parity->setItemText(0, QApplication::translate("CommunicationWindow", "Brak", nullptr));
        comboBox_Parity->setItemText(1, QApplication::translate("CommunicationWindow", "Pozytywna", nullptr));
        comboBox_Parity->setItemText(2, QApplication::translate("CommunicationWindow", "Negatywna", nullptr));
        comboBox_Parity->setItemText(3, QApplication::translate("CommunicationWindow", "Bit parzysto\305\233ci zawsze 1", nullptr));
        comboBox_Parity->setItemText(4, QApplication::translate("CommunicationWindow", "Bit parzysto\305\233ci zawsze 0", nullptr));
        comboBox_Parity->setItemText(5, QApplication::translate("CommunicationWindow", "Nieznane", nullptr));

        label_4->setText(QApplication::translate("CommunicationWindow", "Bit stopu:", nullptr));
        comboBox_Stop->setItemText(0, QApplication::translate("CommunicationWindow", "Jeden", nullptr));
        comboBox_Stop->setItemText(1, QApplication::translate("CommunicationWindow", "Dwa", nullptr));
        comboBox_Stop->setItemText(2, QApplication::translate("CommunicationWindow", "P\303\263\305\202tora", nullptr));
        comboBox_Stop->setItemText(3, QApplication::translate("CommunicationWindow", "Nieznane", nullptr));

        label_5->setText(QApplication::translate("CommunicationWindow", "Kontrola przep\305\202ywu:", nullptr));
        comboBox_Control->setItemText(0, QApplication::translate("CommunicationWindow", "Brak", nullptr));
        comboBox_Control->setItemText(1, QApplication::translate("CommunicationWindow", "Sprz\304\231towa", nullptr));
        comboBox_Control->setItemText(2, QApplication::translate("CommunicationWindow", "Programowa", nullptr));
        comboBox_Control->setItemText(3, QApplication::translate("CommunicationWindow", "Nieznane", nullptr));

        groupBox_2->setTitle(QApplication::translate("CommunicationWindow", "Komunikaty", nullptr));
        pushButton_Clear->setText(QApplication::translate("CommunicationWindow", "Wyczy\305\233\304\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CommunicationWindow: public Ui_CommunicationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMUNICATIONWINDOW_H
