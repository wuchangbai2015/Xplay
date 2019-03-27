#include "XAudioPlay.h"
// ��Ƶ
#include <QAudioOutput> // ����

class CXAudioPlay:public XAudioPlay //  �����̳нӿ��࣬�������ܵ�ʵ��
{
public:

	QAudioOutput *output = NULL;
	QIODevice *io; // ����

	bool Start()
	{
		Stop();
		QAudioFormat fmt;  // ����ĸ�ʽ
		// ��48000������ ÿ��������16λ��  ��2������������
		fmt.setSampleRate(48000);     // 1s�Ӳɼ���48000����Ƶ ������Խ��Խ��
		fmt.setSampleRate(16);        // 16λ��65535
		fmt.setChannelCount(2);       // ����   ˫����
		fmt.setCodec("audio/pcm");    // ��ʽ   �̶�
		fmt.setByteOrder(QAudioFormat::LittleEndian);    // ���ݵ�С��β    ���ݵĴ���  Ĭ��
		fmt.setSampleType(QAudioFormat::UnSignedInt);    // ��ʲô���������   Ĭ��
		
		// ����һ������� ����Ƶ���
		output = new QAudioOutput(fmt);
	    io = output->start(); // ����
		return true;
	}

	void Stop()
	{
		if (output)
		{
			output->stop();// ֹͣ
			delete output;
			output = NULL;
			io = NULL;
		}
	}

	void Play(bool isplay)
	{
		if (!output) return;
		if (isplay)
		{
			output->resume(); // �ָ�����
		}
		else
		{
			output->suspend(); // ��ͣ
		}

	}
	// ���ļ����ȶ�ȡ��Ƶ������Ȼ���Ӹ� QAudioOutput ���в��� 
	// ���Ĳ����Ǵӻ������ж�ȡ�ģ����Ҫ��֤�������Ĵ�С ��Ȼ��д����ȥ��
	bool Write(const char *data, int datasize)
	{
		if (io)
		{
			io->write(data, datasize);
		}
		return true;
	}

	virtual int GetFree()
	{
		if (!output) return 0;
		return output->bytesFree();
	}

private:

};


XAudioPlay::XAudioPlay()
{
}


XAudioPlay::~XAudioPlay()
{
}


XAudioPlay * XAudioPlay::Get() //���Ƕ���ɵ���ģʽ  ����һ������ �Լ��ڲ�����
{
	static CXAudioPlay ap;
	return &ap;
}




