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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "videowidget.h"

QT_BEGIN_NAMESPACE

class Ui_XplayClass
{
public:
    VideoWidget *openGLWidget;
    QPushButton *openButton;
    QPushButton *playButton;

    void setupUi(QWidget *XplayClass)
    {
        if (XplayClass->objectName().isEmpty())
            XplayClass->setObjectName(QStringLiteral("XplayClass"));
        XplayClass->setEnabled(true);
        XplayClass->resize(600, 400);
        XplayClass->setMaximumSize(QSize(600, 400));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Xplay/Resources/ooopic_1552920168.ico"), QSize(), QIcon::Normal, QIcon::Off);
        XplayClass->setWindowIcon(icon);
        openGLWidget = new VideoWidget(XplayClass);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 600, 400));
        openButton = new QPushButton(XplayClass);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(210, 300, 51, 51));
        openButton->setStyleSheet(QLatin1String("QPushButton:!hover{border-image: url(:/Xplay/Resources/ooopic_1552920567.png);}\n"
"QPushButton:hover{border-image: url(:/Xplay/Resources/ooopic_1552920542.png);}"));
        playButton = new QPushButton(XplayClass);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(330, 310, 51, 43));
        playButton->setStyleSheet(QLatin1String("QPushButton:!hover{border-image: url(:/Xplay/Resources/ooopic_1552921240.png);}\n"
"QPushButton:hover{border-image: url(:/Xplay/Resources/ooopic_1552920333.png);}"));

        retranslateUi(XplayClass);

        QMetaObject::connectSlotsByName(XplayClass);
    } // setupUi

    void retranslateUi(QWidget *XplayClass)
    {
        XplayClass->setWindowTitle(QApplication::translate("XplayClass", "Xplay", Q_NULLPTR));
        openButton->setText(QString());
        playButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class XplayClass: public Ui_XplayClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPLAY_H
