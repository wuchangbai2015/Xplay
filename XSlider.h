
// ���ؽ���������� ʵ�ֵ��������ĳλ�þͿ����ò��ŵĽ���
#pragma once
#include <qslider.h>

// �����������һ���ӿ���  ��ȥ�ṩʵ��
class XSlider : public QSlider // ���м̳���������Ǹ���
{
		Q_OBJECT //  qt��ͷ�ļ�����Ҫ��������һ������
public:
	XSlider(QWidget *p = NULL);// ��ӹ��캯��
	virtual ~XSlider();
	//��������¼�
	void mousePressEvent(QMouseEvent *e);
};

