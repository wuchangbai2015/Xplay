
// 重载进度条这个类 实现点击进度条某位置就可设置播放的进度
#pragma once
#include <qslider.h>

// 把这个类做成一个接口类  不去提供实现
class XSlider : public QSlider // 共有继承他本身的那个类
{
		Q_OBJECT //  qt的头文件都需要添加这个做一个处理
public:
	XSlider(QWidget *p = NULL);// 添加构造函数
	virtual ~XSlider();
	//重载鼠标事假
	void mousePressEvent(QMouseEvent *e);
};

