#pragma once

#include <QtWidgets/QWidget>
#include "ui_xplay.h"

class Xplay : public QWidget
{
	Q_OBJECT

public:
	Xplay(QWidget *parent = Q_NULLPTR);
	void timerEvent(QTimerEvent *e);

public slots:
	void open();




private:
	Ui::XplayClass ui;
};
