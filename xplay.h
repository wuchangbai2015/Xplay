#pragma once

#include <QtWidgets/QWidget>
#include "ui_xplay.h"

class Xplay : public QWidget
{
	Q_OBJECT

public:
	Xplay(QWidget *parent = Q_NULLPTR);
	void timerEvent(QTimerEvent *e);

	// 重构控制窗口大小的函数
	void resizeEvent(QResizeEvent *e);



public slots:
	void open();
	void sliderPress();
	void sliderRelease();
	void play();





private:
	Ui::XplayClass ui;
};
