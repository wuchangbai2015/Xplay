//qt��ͷ�ļ�
#include "xplay.h"
#include <QtWidgets/QApplication>

#include "XFFmpeg.h"

//c++��ͷ�ļ�
#include <iostream>
using namespace std;


/***************************************************************
f9 �����öϵ�
ע�ͣ�ctrl + k  c
ȡ��ע�ͣ�ctrl + k  u
***************************************************************/
int main(int argc, char *argv[])
{
	//if (XFFmpeg::Get()->Open("video.mp4"))
	//{
	//	printf("open success!\n");
	//}
	//else
	//{
	//	printf("open faild!%s",XFFmpeg::Get()->GetError().c_str());
	//}

	//char *rgb = new char[800*600*4];
	//for (;;)
	//{
	//	AVPacket pkt = XFFmpeg::Get()->Read();
	//	if (pkt.size == 0)
	//	{	
	//		break;
	//	}
	//	printf("pts = %lld\n",pkt.dts);

	//	if (pkt.stream_index != XFFmpeg::Get()->videoStream)
	//	{
	//		av_packet_unref(&pkt);
	//		continue;
	//	}

	//	AVFrame *yuv = XFFmpeg::Get()->Decode(&pkt);
	//	if (yuv)
	//	{
	//		printf("[D]");
	//		XFFmpeg::Get()->ToRGB(yuv, rgb, 800, 600);
	//	}

	//	

	//	av_packet_unref(&pkt);// �ͷ�
	//}





	//char *path = "video.mp4";      //����·��   �����Ƶ�Ƿ����ҵ�binĿ¼����� 
	//
	//



	//// ����Ƶ������
	//int videoStream = 0;
	//AVCodecContext *videoCtx = NULL; // ��Ž�����������
	//for (int i = 0; i < ic->nb_streams; i++) // ������Ƶ��
	//{
	//	AVCodecContext *enc = ic->streams[i]->codec; // ��������ֵ
	//	if (enc->codec_type == AVMEDIA_TYPE_VIDEO)   // �ж��ǲ���һ����Ƶ
	//	{
	//		videoStream = i;
	//		videoCtx = enc; // ��Ϊ������������
	//		AVCodec *codec = avcodec_find_decoder(enc->codec_id);// ���ҽ����� ���ص��ǽ�������id
	//		if (!codec)
	//		{
	//			printf("video code not find!\n");
	//			return -1;
	//		}
	//		int err = avcodec_open2(enc, codec, NULL);// �����������
	//		if (err != 0)
	//		{
	//			char buf[1024] = {0};
	//			av_strerror(err, buf, sizeof(buf));
	//			printf(buf);
	//			return -2;
	//		}
	//		printf("open codec success!\n");

	//	}

	//}
	//// ��Ƶ����
	//AVFrame *yuv = av_frame_alloc(); // ����һ��֡����Ž��������  ����AVFrame�������Ŀռ�
	//// ���������
	//SwsContext *cCtx = NULL;
	//int outwidth = 640;
	//int outheight = 480;
	//char *rgb = new char[outheight*outwidth * 4];

	//

	//// ����Ƶ����Ϣ
	//for (;;)        
	//{
	//	// һ֡����
	//	AVPacket pkt;// һ���ṹ������Ƶ��Ϣ
	//	re = av_read_frame(ic, &pkt);
	//	if (re != 0) break;
	//	printf("pts = %lld\n",pkt.pts);// pts  ��ŵ�ʱ���  �����ƽ���
	//	//���뷽��1
	//	//int got_picture = 0;// �Ƿ��ȡ����Ƶ����ȡ�˷���1
	//	// ������Ƶ  ����ֵ����Ƶ֡�Ĵ�С���������򿪵Ľ�����������õ���Ƶ֡�����Ƿ��ȡ����Ƶ�ı�־λ�����õ���Ƶ֡
	//	//int re = avcodec_decode_video2(videoCtx, yuv, &got_picture, &pkt);
	//	//if (got_picture)
	//	//{
	//	//	printf("[%d]", re);
	//	//}
	//	// ���뷽��2
	//	int re = avcodec_send_packet(videoCtx, &pkt);
	//	if (re != 0)
	//	{
	//		av_packet_unref(&pkt);
	//		continue;
	//	}
	//	re = avcodec_receive_frame(videoCtx, yuv);
	//	if (re != 0)
	//	{
	//		av_packet_unref(&pkt);
	//		continue;
	//	}
	//	printf("[D]");


	//	
	//}

	//// �򿪽�����
	//cCtx = sws_getCachedContext(NULL, videoCtx->width,
	//	videoCtx->height,
	//	videoCtx->pix_fmt,
	//	outwidth, outheight,
	//	AV_PIX_FMT_BGRA,
	//	SWS_BICUBIC,
	//	NULL, NULL, NULL
	//);
	//if (cCtx)
	//{
	//	printf("sws_getCachedContext success!\n");
	//}
	//else
	//{
	//	printf("sws_getCachedContext faild!\n");
	//	return -1;
	//}

	//if (cCtx)
	//{
	//	sws_freeContext(cCtx);
	//	cCtx = NULL;
	//}
	//// ת��
	//uint8_t *data[AV_NUM_DATA_POINTERS] = {0}; // 8
	//data[0] = (uint8_t *)rgb;
	//int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	//linesize[0] = outwidth * 4;

	//// ת�뺯��   �������򿪵�ת������ԭ���ݵ�data��ÿһ����������0��ԭ���ݵĸ߶ȣ�Ŀ�����ݣ�ÿһ��������
	//int h = sws_scale(cCtx, yuv->data, yuv->linesize, 0, videoCtx->height,
	//	data,
	//	linesize
	//);
	//if (h > 0)
	//{
	//	printf("(%d)", h);

	//}

	//
	//ic = NULL;
	
	
	QApplication a(argc, argv);
	Xplay w;
	w.show();
	return a.exec();
}








