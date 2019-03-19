#pragma once

// 引用c语言的头文件
extern"C" {
	#include <libavformat\avformat.h>
	#include <libswscale\swscale.h>
}
#include <string>
#include <QMutex> // qt的互斥变量

using namespace std;

class XFFmpeg
{
public:
	static XFFmpeg *Get()
	{
		static XFFmpeg ff;
		return &ff;
	}

	bool Open(const char *path);
	void Close();
	string GetError();
	int	 totalMs = 0;
	int fps = 0;
	AVPacket Read();// 读取视频

	AVFrame *Decode(const AVPacket *pkt);
	bool ToRGB(char *out, int outwidth, int outheight);

	virtual ~XFFmpeg();
	int videoStream = 0;

protected:
	char errorbuf[1024];
	AVFormatContext *ic = NULL;    //存放打开视频或者流的信息
	QMutex mutex;// 声明一个互斥变量


	
	AVFrame *yuv = NULL;
	SwsContext *cCtx = NULL;
	XFFmpeg();
};

