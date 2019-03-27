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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "videowidget.h"
#include "xslider.h"

QT_BEGIN_NAMESPACE

class Ui_XplayClass
{
public:
    VideoWidget *openGLWidget;
    QPushButton *openButton;
    QPushButton *playButton;
    QLabel *totalTime;
    QLabel *playTime;
    QLabel *sp;
    XSlider *playSlider;

    void setupUi(QWidget *XplayClass)
    {
        if (XplayClass->objectName().isEmpty())
            XplayClass->setObjectName(QStringLiteral("XplayClass"));
        XplayClass->setEnabled(true);
        XplayClass->resize(600, 400);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Xplay/Resources/ooopic_1552920168.ico"), QSize(), QIcon::Normal, QIcon::Off);
        XplayClass->setWindowIcon(icon);
        openGLWidget = new VideoWidget(XplayClass);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 600, 400));
        openButton = new QPushButton(XplayClass);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(490, 350, 51, 41));
        openButton->setStyleSheet(QLatin1String("QPushButton:!hover{border-image: url(:/Xplay/Resources/ooopic_1552920567.png);}\n"
"QPushButton:hover{border-image: url(:/Xplay/Resources/ooopic_1552920542.png);}"));
        playButton = new QPushButton(XplayClass);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(540, 352, 51, 41));
        playButton->setStyleSheet(QLatin1String("QPushButton:!hover{border-image: url(:/Xplay/Resources/ooopic_1552921240.png);}\n"
"QPushButton:hover{border-image: url(:/Xplay/Resources/ooopic_1552920333.png);}"));
        totalTime = new QLabel(XplayClass);
        totalTime->setObjectName(QStringLiteral("totalTime"));
        totalTime->setGeometry(QRect(100, 370, 61, 16));
        totalTime->setStyleSheet(QString::fromUtf8("\n"
"\n"
"color: rgb(255, 255, 255);\n"
"\n"
"font: 12pt \"\351\273\221\344\275\223\";"));
        playTime = new QLabel(XplayClass);
        playTime->setObjectName(QStringLiteral("playTime"));
        playTime->setGeometry(QRect(40, 370, 61, 16));
        playTime->setStyleSheet(QString::fromUtf8("\n"
"\n"
"color: rgb(255, 255, 255);\n"
"\n"
"font: 12pt \"\351\273\221\344\275\223\";"));
        sp = new QLabel(XplayClass);
        sp->setObjectName(QStringLiteral("sp"));
        sp->setGeometry(QRect(90, 370, 16, 16));
        sp->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 14pt \"\351\273\221\344\275\223\";"));
        playSlider = new XSlider(XplayClass);
        playSlider->setObjectName(QStringLiteral("playSlider"));
        playSlider->setGeometry(QRect(20, 340, 561, 22));
        playSlider->setStyleSheet(QStringLiteral("font: 7pt \"Arial\";"));
        playSlider->setMaximum(999);
        playSlider->setPageStep(100);
        playSlider->setOrientation(Qt::Horizontal);

        retranslateUi(XplayClass);
        QObject::connect(openButton, SIGNAL(clicked()), XplayClass, SLOT(open()));
        QObject::connect(playSlider, SIGNAL(sliderPressed()), XplayClass, SLOT(sliderPress()));
        QObject::connect(playSlider, SIGNAL(sliderReleased()), XplayClass, SLOT(sliderRelease()));
        QObject::connect(playButton, SIGNAL(clicked()), XplayClass, SLOT(play()));

        QMetaObject::connectSlotsByName(XplayClass);
    } // setupUi

    void retranslateUi(QWidget *XplayClass)
    {
        XplayClass->setWindowTitle(QApplication::translate("XplayClass", "Xplay", Q_NULLPTR));
        openButton->setText(QString());
        playButton->setText(QString());
        totalTime->setText(QApplication::translate("XplayClass", "000:00", Q_NULLPTR));
        playTime->setText(QApplication::translate("XplayClass", "000:00", Q_NULLPTR));
        sp->setText(QApplication::translate("XplayClass", "/", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class XplayClass: public Ui_XplayClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPLAY_H
