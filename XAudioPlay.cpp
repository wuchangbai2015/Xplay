#include "XAudioPlay.h"
// ��Ƶ
#include <QAudioOutput> // ����
#include <QMutex> // qt�Ļ������

class CXAudioPlay:public XAudioPlay //  �����̳нӿ��࣬�������ܵ�ʵ��
{
public:

	QAudioOutput *output = NULL;
	QIODevice *io = NULL; // ����
	QMutex mutex;

	bool Start()
	{
		Stop();
		mutex.lock();
		QAudioFormat fmt;  // ����ĸ�ʽ
		// ��48000������ ÿ��������16λ��  ��2������������
		fmt.setSampleRate(48000);     // 1s�Ӳɼ���48000����Ƶ ������Խ��Խ��
		fmt.setSampleSize(16);        // 16λ��65535
		fmt.setChannelCount(2);       // ����   ˫����
		fmt.setCodec("audio/pcm");    // ��ʽ   �̶�
		fmt.setByteOrder(QAudioFormat::LittleEndian);    // ���ݵ�С��β    ���ݵĴ���  Ĭ��
		fmt.setSampleType(QAudioFormat::UnSignedInt);    // ��ʲô���������   Ĭ��
		
		// ����һ������� ����Ƶ���
		output = new QAudioOutput(fmt);
	    io = output->start(); // ����
		mutex.unlock();
		return true;
	}

	void Stop()
	{
		mutex.lock();
		if (output)
		{
			output->stop();// ֹͣ
			delete output;
			output = NULL;
			io = NULL;
		}
		mutex.unlock();
	}

	void Play(bool isplay)
	{
		mutex.lock();
		if (!output)
		{
			mutex.unlock();
			return;
		}
		
		if (isplay)
		{
			output->resume(); // �ָ�����
		}
		else
		{
			output->suspend(); // ��ͣ
		}
		mutex.unlock();

	}
	// ���ļ����ȶ�ȡ��Ƶ������Ȼ���Ӹ� QAudioOutput ���в��� 
	// ���Ĳ����Ǵӻ������ж�ȡ�ģ����Ҫ��֤�������Ĵ�С ��Ȼ��д����ȥ��
	bool Write(const char *data, int datasize)
	{
		mutex.lock();
		if (io)
		{
			io->write(data, datasize);
		}
		mutex.unlock();
		return true;
	}

	virtual int GetFree()
	{
		mutex.lock();
		if (!output)
		{
			mutex.unlock();
			return 0;
		}
		 
		int free = output->bytesFree();
		mutex.unlock();
		return free;
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




