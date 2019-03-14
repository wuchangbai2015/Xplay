/********************************************************************************
** Form generated from reading UI file 'xplay.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPLAY_H
#define UI_XPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XplayClass
{
public:

    void setupUi(QWidget *XplayClass)
    {
        if (XplayClass->objectName().isEmpty())
            XplayClass->setObjectName(QStringLiteral("XplayClass"));
        XplayClass->resize(600, 400);

        retranslateUi(XplayClass);

        QMetaObject::connectSlotsByName(XplayClass);
    } // setupUi

    void retranslateUi(QWidget *XplayClass)
    {
        XplayClass->setWindowTitle(QApplication::translate("XplayClass", "Xplay", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class XplayClass: public Ui_XplayClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPLAY_H
