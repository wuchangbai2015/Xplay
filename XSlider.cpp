#include "XSlider.h"
#include <QMouseEvent>


XSlider::XSlider(QWidget *p):QSlider(p) // 调用构造函数的时候，传参p，将其传给基类的构造函数
{
	
}


XSlider::~XSlider()
{
}

void XSlider::mousePressEvent(QMouseEvent *e)
{
	int value = ((float)e->pos().x() / (float)this->width()) * (maximum() + 1); 
	this->setValue(value);
	QSlider::mousePressEvent(e);

}
