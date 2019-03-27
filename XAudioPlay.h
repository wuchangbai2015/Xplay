#pragma once
class XAudioPlay
{
public:

	virtual ~XAudioPlay();
	XAudioPlay *Get();
	//影藏一些信息 用了virtual 即使是内部音频的实现被换掉了 调用者不需要做任何的改变
	virtual bool Start() = 0;
	virtual void  Stop() = 0;
	virtual void Play(bool isplay) = 0;
	virtual bool Write(const char *data, int datasize) = 0;
	virtual int GetFree() = 0;
	//int sampleRate = 48000;     // 1s钟采集了48000个音频 理论上越高越好
	//int sampleSize = 16;        // 16位即65535
	//int channelCount = 2;       // 声道   双声道
protected:
	XAudioPlay(); // 

};

