#include "XAudioPlay.h"
// 音频
#include <QAudioOutput> // 播放
#include <QMutex> // qt的互斥变量

class CXAudioPlay:public XAudioPlay //  这个类继承接口类，来做功能的实现
{
public:

	QAudioOutput *output = NULL;
	QIODevice *io = NULL; // 播放
	QMutex mutex;

	bool Start()
	{
		Stop();
		mutex.lock();
		QAudioFormat fmt;  // 输出的格式
		// 有48000个样本 每个样本是16位的  有2个这样的样本
		fmt.setSampleRate(48000);     // 1s钟采集了48000个音频 理论上越高越好
		fmt.setSampleSize(16);        // 16位即65535
		fmt.setChannelCount(2);       // 声道   双声道
		fmt.setCodec("audio/pcm");    // 格式   固定
		fmt.setByteOrder(QAudioFormat::LittleEndian);    // 数据的小结尾    数据的次序  默认
		fmt.setSampleType(QAudioFormat::UnSignedInt);    // 用什么数据来存的   默认
		
		// 创建一个输出流 打开音频输出
		output = new QAudioOutput(fmt);
	    io = output->start(); // 播放
		mutex.unlock();
		return true;
	}

	void Stop()
	{
		mutex.lock();
		if (output)
		{
			output->stop();// 停止
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
			output->resume(); // 恢复播放
		}
		else
		{
			output->suspend(); // 暂停
		}
		mutex.unlock();

	}
	// 由文件中先读取音频出来，然后扔给 QAudioOutput 进行播放 
	// 他的播放是从缓冲区中读取的，这就要保证缓冲区的大小 不然就写不进去了
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


XAudioPlay * XAudioPlay::Get() //还是定义成单键模式  定义一个对象 自己内部调用
{
	static CXAudioPlay ap;
	return &ap;
}




