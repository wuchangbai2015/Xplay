#pragma once

// ����c���Ե�ͷ�ļ�
extern"C" {
	#include <libavformat\avformat.h>
	#include <libswscale\swscale.h>
	// ��Ƶ�ز���
	#include <libswresample/swresample.h>
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

	// return pts
	int Decode(const AVPacket *pkt);
	bool ToRGB(char *out, int outwidth, int outheight); // ��Ƶ

	int  ToPCM(char *out);  // ��Ƶ return ��С

	bool Seek(float pos);// pos 0~1   �����϶�����

	virtual ~XFFmpeg();
	int videoStream = 0;

	bool isPlay = false;

	int audioStream = 1;// ��¼��Ƶ��������
	int sampleRate = 48000;     // 1s�Ӳɼ���48000����Ƶ ������Խ��Խ��
	int sampleSize = 16;        // 16λ��65535
	int channelCount = 2;       // ����   ˫����

protected:
	char errorbuf[1024];
	AVFormatContext *ic = NULL;    //��Ŵ���Ƶ����������Ϣ
	QMutex mutex;// ����һ���������


	
	AVFrame *yuv = NULL;// ����ռ����ڴ�Ž�������Ƶ
	SwsContext *cCtx = NULL; // ��Ƶ��

	SwrContext *aCtx = NULL; // ��Ƶ�ز�����Ԥ��

	XFFmpeg();

	AVFrame *pcm = NULL;// ����ռ����ڴ�Ž�������Ƶ
};

