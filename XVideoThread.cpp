#include "XVideoThread.h"
#include "XFFmpeg.h"

#include "XAudioPlay.h"

bool isexit = false;


XVideoThread::XVideoThread()
{

}
void XVideoThread::run()
{
	char out[10000] = {0};
	while (!isexit)
	{
	   // 拖动进度条的，要是暂停状态 就sleep
		if (!XFFmpeg::Get()->isPlay)
		{
			msleep(10);
			continue;
		}

		int free = XAudioPlay::Get()->GetFree();// 音频的缓冲区还有多少内存可以写
		if (free < 10000)
		{
			msleep(1);
			continue;
		}

		AVPacket pkt = XFFmpeg::Get()->Read();
		if (pkt.size <= 0)
		{
			msleep(10);
			continue;
		}


		if (pkt.stream_index == XFFmpeg::Get()->audioStream)
		{
			XFFmpeg::Get()->Decode(&pkt);
			av_packet_unref(&pkt);
			int len = XFFmpeg::Get()->ToPCM(out); // 重采样
			XAudioPlay::Get()->Write(out, len);
			
			continue;
		}

		if (pkt.stream_index != XFFmpeg::Get()->videoStream)
		{
			av_packet_unref(&pkt);
			continue;
		}
		

		XFFmpeg::Get()->Decode(&pkt);
		av_packet_unref(&pkt);
		//if (XFFmpeg::Get()->fps > 0)
		//{
		//	msleep(1000 / XFFmpeg::Get()->fps);
		//}
		

	}

}

XVideoThread::~XVideoThread()
{
}
