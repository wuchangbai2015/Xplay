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
	   // �϶��������ģ�Ҫ����ͣ״̬ ��sleep
		if (!XFFmpeg::Get()->isPlay)
		{
			msleep(10);
			continue;
		}

		int free = XAudioPlay::Get()->GetFree();// ��Ƶ�Ļ��������ж����ڴ����д
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
			int len = XFFmpeg::Get()->ToPCM(out); // �ز���
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
