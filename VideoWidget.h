#pragma once
#include <QtWidgets/qwidget.h>
#include <QOpenGLWidget>

class VideoWidget:public QOpenGLWidget
{
public:
	VideoWidget(QWidget *p = NULL);
	void paintEvent(QPaintEvent *e);
	void timerEvent(QTimerEvent *e);
	virtual ~VideoWidget();
};

