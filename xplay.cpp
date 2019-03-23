#include "xplay.h"
#include <QFileDialog>
#include "XFFmpeg.h"
#include <QMessageBox>
//#include <iostream>
//using namespace std;

static bool isPressSlider = false; //静态的全局变量只能在该cpp文件中被访问到 
static bool isPlay = true;

#define PAUSE "QPushButton{border-image: url(:/Xplay/Resources/ooopic_1552920403.png);}"
#define PLAY "QPushButton{border-image: url(:/Xplay/Resources/ooopic_1552921240.png);}"

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
	isPlay = false;
	play();


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
		
		// 精度条被按下就不能自己去刷进度了，只有在没有被按下的时候才能自己显示进度
		if (!isPressSlider)
		{
			ui.playSlider->setValue(rate * 1000);
		}
		
	}
}

void Xplay::sliderPress()
{
	isPressSlider = true;
}

void Xplay::sliderRelease()
{
	isPressSlider = false;
	float pos = 0;
	pos = (float)ui.playSlider->value() / (float)(ui.playSlider->maximum()+1);
	XFFmpeg::Get()->Seek(pos);

}

void Xplay::play() // 暂停按钮的槽
{
	isPlay = !isPlay;
	XFFmpeg::Get()->isPlay = isPlay;
	if (isPlay)
	{
		//Pause
		ui.playButton->setStyleSheet(PAUSE);
	}
	else
	{
		ui.playButton->setStyleSheet(PLAY);
	}


}






