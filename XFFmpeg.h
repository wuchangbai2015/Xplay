#pragma once

// ����c���Ե�ͷ�ļ�
extern"C" {
	#include <libavformat\avformat.h>
	#include <libswscale\swscale.h>
}
#include <string>
#include <QMutex> // qt�Ļ������

using namespace std;

class XFFmpeg
{
public:
	static XFFmpeg *Get()
	{
		static XFFmpeg ff;
		return &ff;
	}

	int Open(const char *path);
	void Close();
	string GetError();
	int	 totalMs = 0;
	int fps = 0;
	int pts = 0; // ��ȡ��ǰ�Ĳ���ʱ��
	AVPacket Read();// ��ȡ��Ƶ

	AVFrame *Decode(const AVPacket *pkt);
	bool ToRGB(char *out, int outwidth, int outheight);

	bool Seek(float pos);// pos 0~1   �����϶�����

	virtual ~XFFmpeg();
	int videoStream = 0;

	bool isPlay = false;

protected:
	char errorbuf[1024];
	AVFormatContext *ic = NULL;    //��Ŵ���Ƶ����������Ϣ
	QMutex mutex;// ����һ���������


	
	AVFrame *yuv = NULL;
	SwsContext *cCtx = NULL;
	XFFmpeg();
};

