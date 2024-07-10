/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *encodeButton;
    QPushButton *decodeButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 400);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label->setMargin(10);

        verticalLayout->addWidget(label);

        encodeButton = new QPushButton(centralwidget);
        encodeButton->setObjectName("encodeButton");
        encodeButton->setMinimumSize(QSize(200, 50));

        verticalLayout->addWidget(encodeButton);

        decodeButton = new QPushButton(centralwidget);
        decodeButton->setObjectName("decodeButton");
        decodeButton->setMinimumSize(QSize(200, 50));

        verticalLayout->addWidget(decodeButton);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "File Compressor", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; font-style:italic; color:#3c50aa;\">Welcome to the File Compressor</span></p></body></html>", nullptr));
        encodeButton->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: #4CAF50; color: white; padding: 10px; border: none; border-radius: 5px; font-size: 16px; } QPushButton:hover { background-color: #45a049; }", nullptr));
        encodeButton->setText(QCoreApplication::translate("MainWindow", "Encode a File", nullptr));
        decodeButton->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: #008CBA; color: white; padding: 10px; border: none; border-radius: 5px; font-size: 16px; } QPushButton:hover { background-color: #007bb5; }", nullptr));
        decodeButton->setText(QCoreApplication::translate("MainWindow", "Decode a File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
