#include "XFFmpeg.h"
//Ԥ����ָ����
#pragma comment(lib,"avformat.lib") // �ļ���ʽ   ������
#pragma comment(lib, "avutil.lib")  // �������     ��ȡ������Ϣ�Ŀ�
#pragma comment(lib, "avcodec.lib") // �����ʽ
#pragma comment(lib, "swscale.lib") // YUVתRGB


static double r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}

int XFFmpeg::Open(const char *path)
{
	Close();
	mutex.lock();
	int re = avformat_open_input(&ic, path, 0, 0); //���ļ���
	if (re != 0) //��ʧ��
	{
		mutex.unlock();
		av_strerror(re, errorbuf, sizeof(errorbuf)); // ����������Ϣ
		printf("open %s failed: %s\n", path, errorbuf);
		return 0;
	}
	// ��ȡ��Ƶ��ʱ�� ��λs
	int totalMs = (ic->duration / AV_TIME_BASE *1000);
	//printf("file totleSec is %d-%d\n", totalMs / 60, totalMs % 60);
	
	

	for (int i = 0; i < ic->nb_streams; i++)         // ������Ƶ��
	{
		AVCodecContext *enc = ic->streams[i]->codec; // ��������ֵ
		if (enc->codec_type == AVMEDIA_TYPE_VIDEO)   // �ж��ǲ���һ����Ƶ
		{
			videoStream = i;
			fps = r2d(ic->streams[i]->avg_frame_rate);
			AVCodec *codec = avcodec_find_decoder(enc->codec_id);// ���ҽ����� ���ص��ǽ�������id
			if (!codec)
			{
				mutex.unlock();
				printf("video code not find!\n");
				return 0;
			}
			int err = avcodec_open2(enc, codec, NULL);// �����������
			if (err != 0)
			{
				mutex.unlock();
				char buf[1024] = { 0 };
				av_strerror(err, buf, sizeof(buf));
				printf(buf);
				return 0;
			}
			printf("open codec success!\n");
		}
	}
	mutex.unlock();
	return totalMs;
}
void XFFmpeg::Close()
{
	mutex.lock();
	if(ic) avformat_close_input(&ic); //�ͷ�
	if (yuv) av_frame_free(&yuv);
	if (cCtx)
	{
		sws_freeContext(cCtx);
		cCtx = NULL;
	}
	mutex.unlock();
}
string XFFmpeg::GetError()
{
	mutex.lock();
	string re = this->errorbuf;
	mutex.unlock();
	return re;
}

AVPacket XFFmpeg::Read()// ��ȡ��Ƶ
{
	AVPacket pkt;
	memset(&pkt, 0, sizeof(AVPacket));
	mutex.lock();
	if (!ic)
	{	
		mutex.unlock();
		return pkt;
	}
	int err = av_read_frame(ic, &pkt);
	if (err != 0)
	{	
		av_strerror(err, errorbuf, sizeof(errorbuf));

	}
	mutex.unlock();
	return pkt;
}

AVFrame *XFFmpeg::Decode(const AVPacket *pkt)
{
	mutex.lock();
	if (!ic)
	{	
		mutex.unlock();
		return NULL;
	}
	if (yuv == NULL)
	{	
		yuv = av_frame_alloc();
	}
	int re = avcodec_send_packet(ic->streams[pkt->stream_index]->codec, pkt);
	if (re != 0)
	{
		mutex.unlock();
		return NULL;
	}
	re = avcodec_receive_frame(ic->streams[pkt->stream_index]->codec, yuv);
	if (re != 0)
	{
		mutex.unlock();
		return NULL;
	}
	mutex.unlock();
	pts = (yuv->pts *r2d(ic->streams[pkt->stream_index]->time_base))*1000;// ��ȡ��ǰ���ŵ�λ��
	return yuv;

}

bool XFFmpeg::Seek(float pos) // �϶�������
{
	mutex.lock();
	if (!ic)
	{
		mutex.unlock();
		return false;
	}
	int64_t stamp = 0;
	// streams ��ŵ���Ƶ��  videoStream ��ŵ���Ƶ�������� 
	stamp = pos * ic->streams[videoStream]->duration; 
	int re = av_seek_frame(ic, videoStream, stamp, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
	avcodec_flush_buffers(ic->streams[videoStream]->codec);

	pts = (stamp *r2d(ic->streams[videoStream]->time_base)) * 1000;// ��ȡ��ǰ���ŵ�λ��
	
	mutex.unlock();
	if (re >= 0)
		return true;
	return false;

}

bool XFFmpeg::ToRGB(char *out, int outwidth, int outheight)
{
	mutex.lock();
	if (!ic || !yuv)
	{
		mutex.unlock();
		return false;
	}
	// �򿪽�����
	AVCodecContext *videoCtx =ic->streams[this->videoStream]->codec;
	//���ø�ʽת����
	cCtx = sws_getCachedContext(NULL, //��һ�������Դ�NULL��Ĭ�ϻῪ��һ���µĿռ�
		videoCtx->width,
		videoCtx->height,            
		videoCtx->pix_fmt,            //ԭʼ���ݵĿ�ߺ�ԭʼ���ظ�ʽ
		outwidth, outheight,          // Ŀ���Ŀ���
		AV_PIX_FMT_BGRA,              //Ŀ������ظ�ʽ
		SWS_BICUBIC,
		NULL, NULL, NULL
	);
	if (cCtx)
	{
		printf("sws_getCachedContext success!\n");
	}
	else
	{
		mutex.unlock();
		printf("sws_getCachedContext faild!\n");
		return false;
	}

	// ת��
	uint8_t *data[AV_NUM_DATA_POINTERS] = {0}; // 8
	data[0] = (uint8_t *)out;
	int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	linesize[0] = outwidth * 4;

	// ת�뺯��   �������򿪵�ת������ԭ���ݵ�data��ÿһ����������0��ԭ���ݵĸ߶ȣ�Ŀ�����ݣ�ÿһ��������
	int h = sws_scale(cCtx, yuv->data, yuv->linesize, 0, videoCtx->height, //��֡��ԭʼ��ʽ��videoCtx->pix_fmt��ת����ΪRGB��ʽ
		data,
		linesize
	);
	if (h > 0)
	{
		printf("(%d)", h);

	}
	mutex.unlock();

}
XFFmpeg::XFFmpeg()
{
	errorbuf[0] = '\0';
	av_register_all();             //ע�����еĸ�ʽ
}


XFFmpeg::~XFFmpeg()
{
}
