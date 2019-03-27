#pragma once
class XAudioPlay
{
public:

	virtual ~XAudioPlay();
	XAudioPlay *Get();
	//Ӱ��һЩ��Ϣ ����virtual ��ʹ���ڲ���Ƶ��ʵ�ֱ������� �����߲���Ҫ���κεĸı�
	virtual bool Start() = 0;
	virtual void  Stop() = 0;
	virtual void Play(bool isplay) = 0;
	virtual bool Write(const char *data, int datasize) = 0;
	virtual int GetFree() = 0;
	//int sampleRate = 48000;     // 1s�Ӳɼ���48000����Ƶ ������Խ��Խ��
	//int sampleSize = 16;        // 16λ��65535
	//int channelCount = 2;       // ����   ˫����
protected:
	XAudioPlay(); // 

};

