#pragma once

// 引用c语言的头文件
extern"C" {
	#include <libavformat\avformat.h>
	#include <libswscale\swscale.h>
	// 音频重采样
	#include <libswresample/swresample.h>
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

	int Open(const char *path);
	void Close();
	string GetError();
	int	 totalMs = 0;
	int fps = 0;
	int pts = 0; // 获取当前的播放时间
	AVPacket Read();// 读取视频

	// return pts
	int Decode(const AVPacket *pkt);
	bool ToRGB(char *out, int outwidth, int outheight); // 视频

	int  ToPCM(char *out);  // 音频 return 大小

	bool Seek(float pos);// pos 0~1   拉动拖动条的

	virtual ~XFFmpeg();
	int videoStream = 0;

	bool isPlay = false;

	int audioStream = 1;// 记录音频流的索引
	int sampleRate = 48000;     // 1s钟采集了48000个音频 理论上越高越好
	int sampleSize = 16;        // 16位即65535
	int channelCount = 2;       // 声道   双声道

protected:
	char errorbuf[1024];
	AVFormatContext *ic = NULL;    //存放打开视频或者流的信息
	QMutex mutex;// 声明一个互斥变量


	
	AVFrame *yuv = NULL;// 这个空间用于存放解码后的视频
	SwsContext *cCtx = NULL; // 视频的

	SwrContext *aCtx = NULL; // 音频重采样的预设

	XFFmpeg();

	AVFrame *pcm = NULL;// 这个空间用于存放解码后的音频
};

