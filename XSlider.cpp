#include "XSlider.h"
#include <QMouseEvent>


XSlider::XSlider(QWidget *p):QSlider(p) // ���ù��캯����ʱ�򣬴���p�����䴫������Ĺ��캯��
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
