/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *btn_ini;
    QPushButton *btn_start;
    QPushButton *btn_stop;
    QPushButton *btn_close;
    QCustomPlot *global_plt;
    QCustomPlot *phase_plt;
    QCustomPlot *amplitude_plt;
    QPushButton *btn_IQ;
    QPushButton *btn_IQ_close;
    QLineEdit *lineEdit_alarm_pos;
    QPushButton *btn_set_alarm_pos;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1024, 600);
        btn_ini = new QPushButton(Widget);
        btn_ini->setObjectName(QString::fromUtf8("btn_ini"));
        btn_ini->setGeometry(QRect(10, 0, 75, 23));
        btn_start = new QPushButton(Widget);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));
        btn_start->setGeometry(QRect(10, 30, 75, 23));
        btn_stop = new QPushButton(Widget);
        btn_stop->setObjectName(QString::fromUtf8("btn_stop"));
        btn_stop->setGeometry(QRect(10, 60, 75, 23));
        btn_close = new QPushButton(Widget);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setGeometry(QRect(10, 90, 75, 23));
        global_plt = new QCustomPlot(Widget);
        global_plt->setObjectName(QString::fromUtf8("global_plt"));
        global_plt->setGeometry(QRect(109, 9, 891, 171));
        phase_plt = new QCustomPlot(Widget);
        phase_plt->setObjectName(QString::fromUtf8("phase_plt"));
        phase_plt->setGeometry(QRect(120, 400, 881, 161));
        amplitude_plt = new QCustomPlot(Widget);
        amplitude_plt->setObjectName(QString::fromUtf8("amplitude_plt"));
        amplitude_plt->setGeometry(QRect(120, 210, 881, 151));
        btn_IQ = new QPushButton(Widget);
        btn_IQ->setObjectName(QString::fromUtf8("btn_IQ"));
        btn_IQ->setGeometry(QRect(10, 120, 75, 23));
        btn_IQ_close = new QPushButton(Widget);
        btn_IQ_close->setObjectName(QString::fromUtf8("btn_IQ_close"));
        btn_IQ_close->setGeometry(QRect(10, 150, 75, 23));
        lineEdit_alarm_pos = new QLineEdit(Widget);
        lineEdit_alarm_pos->setObjectName(QString::fromUtf8("lineEdit_alarm_pos"));
        lineEdit_alarm_pos->setGeometry(QRect(10, 380, 113, 21));
        btn_set_alarm_pos = new QPushButton(Widget);
        btn_set_alarm_pos->setObjectName(QString::fromUtf8("btn_set_alarm_pos"));
        btn_set_alarm_pos->setGeometry(QRect(130, 380, 75, 23));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        btn_ini->setText(QCoreApplication::translate("Widget", "\345\210\235\345\247\213\345\214\226", nullptr));
        btn_start->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        btn_stop->setText(QCoreApplication::translate("Widget", "\345\201\234\346\255\242\351\207\207\351\233\206", nullptr));
        btn_close->setText(QCoreApplication::translate("Widget", "\345\205\263\351\227\255\346\235\277\345\215\241", nullptr));
        btn_IQ->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213\350\247\243\350\260\203", nullptr));
        btn_IQ_close->setText(QCoreApplication::translate("Widget", "\345\205\263\351\227\255\350\247\243\350\260\203", nullptr));
        btn_set_alarm_pos->setText(QCoreApplication::translate("Widget", "\344\275\215\347\275\256\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
