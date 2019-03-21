#include "xplay.h"
#include <QFileDialog>
#include "XFFmpeg.h"
#include <QMessageBox>

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


}

void Xplay::timerEvent(QTimerEvent *e)
{
	// ���ŵ�ʱ��
	int min = (XFFmpeg::Get()->pts / 1000) / 60;
	int sec = (XFFmpeg::Get()->pts / 1000) % 60;
	char buf[1024] = {0};
	sprintf(buf, "%03d:%02d", min, sec);
	ui.playTime->setText(buf);

	// ������
	if (XFFmpeg::Get()->totalMs > 0)
	{
		float rate = ((float)XFFmpeg::Get()->pts) / ((float)XFFmpeg::Get()->totalMs);
		ui.playSlider->setValue(rate * 1000);
	}
}






