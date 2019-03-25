#include "xplay.h"
#include <QFileDialog>
#include "XFFmpeg.h"
#include <QMessageBox>
//#include <iostream>
//using namespace std;

static bool isPressSlider = false; //��̬��ȫ�ֱ���ֻ���ڸ�cpp�ļ��б����ʵ� 
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
	// ���ļ��ҵ���Ƶ
	QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("ѡ����Ƶ�ļ�")); 
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

	// ��ʾ��ʱ��
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
	// ���ŵ�ʱ��
	int min = (XFFmpeg::Get()->pts / 1000) / 60;
	int sec = (XFFmpeg::Get()->pts / 1000) % 60;
	char buf[1024] = {0};
	sprintf(buf, "%03d:%02d", min, sec);
	ui.playTime->setText(buf);



	//cout << "pts--------->" << XFFmpeg::Get()->pts << endl;
	//cout << "total------->" << XFFmpeg::Get()->totalMs << endl;

	// ������
	if (XFFmpeg::Get()->totalMs > 0)
	{
		float rate = ((float)XFFmpeg::Get()->pts) / ((float)XFFmpeg::Get()->totalMs);
		
		// �����������¾Ͳ����Լ�ȥˢ�����ˣ�ֻ����û�б����µ�ʱ������Լ���ʾ����
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

void Xplay::play() // ��ͣ��ť�Ĳ�
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

void Xplay::resizeEvent(QResizeEvent *e)
{
	// ��Ƶ���ڷ����仯��ʱ��������Ҳ������Ƶ���ڷ����仯
	ui.openGLWidget->resize(size()); // �����Ļ� ���ڻ�崻��ģ�ԭ��������ڴ治����
	// �������ڿ����ƶ��ģ�������������ô�ƶ���Ӧ���������
	ui.playButton->move(this->width()/2 + 50, this->height() - 40);
	ui.openButton->move(this->width() / 2 - 50, this->height() - 40);
	ui.playSlider->move(25, this->height() - 50);
	ui.playSlider->resize(this->width() - 50, ui.playSlider->height());
	ui.playTime->move(25, ui.playButton->y() + 12);
	ui.sp->move(ui.playTime->x()-20 + ui.playTime->width() + 5, ui.playTime->y());
	ui.totalTime->move(80, ui.playButton->y() + 12);


}






