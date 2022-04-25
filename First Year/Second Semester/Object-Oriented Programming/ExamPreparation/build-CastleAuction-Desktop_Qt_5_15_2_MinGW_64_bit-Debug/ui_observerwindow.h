/********************************************************************************
** Form generated from reading UI file 'observerwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBSERVERWINDOW_H
#define UI_OBSERVERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObserverWindow
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QWidget *ObserverWindow)
    {
        if (ObserverWindow->objectName().isEmpty())
            ObserverWindow->setObjectName(QString::fromUtf8("ObserverWindow"));
        ObserverWindow->resize(550, 473);
        verticalLayoutWidget = new QWidget(ObserverWindow);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 531, 451));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableView = new QTableView(verticalLayoutWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(ObserverWindow);

        QMetaObject::connectSlotsByName(ObserverWindow);
    } // setupUi

    void retranslateUi(QWidget *ObserverWindow)
    {
        ObserverWindow->setWindowTitle(QCoreApplication::translate("ObserverWindow", "Form", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ObserverWindow", "Add $10k", nullptr));
        pushButton->setText(QCoreApplication::translate("ObserverWindow", "Add $100k", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ObserverWindow: public Ui_ObserverWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBSERVERWINDOW_H
