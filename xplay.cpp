#include "xplay.h"
#include <QFileDialog>
#include "XFFmpeg.h"
#include <QMessageBox>
//#include <iostream>
//using namespace std;

Xplay::Xplay(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	startTimer(40);
}

void Xplay::open()
{
	// 打开文件找到视频
	QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择视频文件")); 
	if (name.isEmpty())
	{
		return;
	}
	this->setWindowTitle(name);
	int totalMs = XFFmpeg::Get()->Open(name.toLocal8Bit());
	if (totalMs <= 0)
	{
		QMessageBox::information(this, "err", "file open failed!");
		return;
	}

	// 显示总时间
	char buf[1024] = {0};
	int min = (totalMs / 1000) / 60;
	int sec = (totalMs / 1000) % 60;
	sprintf(buf, "%03d:%02d", min, sec);
	ui.totalTime->setText(buf);
	XFFmpeg::Get()->totalMs = totalMs;


}

void Xplay::timerEvent(QTimerEvent *e)
{
	// 播放的时间
	int min = (XFFmpeg::Get()->pts / 1000) / 60;
	int sec = (XFFmpeg::Get()->pts / 1000) % 60;
	char buf[1024] = {0};
	sprintf(buf, "%03d:%02d", min, sec);
	ui.playTime->setText(buf);

	//cout << "pts--------->" << XFFmpeg::Get()->pts << endl;
	//cout << "total------->" << XFFmpeg::Get()->totalMs << endl;

	// 进度条
	if (XFFmpeg::Get()->totalMs > 0)
	{


		float rate = ((float)XFFmpeg::Get()->pts) / ((float)XFFmpeg::Get()->totalMs);
		ui.playSlider->setValue(rate * 1000);
	}
}






