//qt的头文件
#include "xplay.h"
#include <QtWidgets/QApplication>

#include "XFFmpeg.h"

//c++的头文件
#include <iostream>
using namespace std;


/***************************************************************
f9 可设置断点
注释：ctrl + k  c
取消注释：ctrl + k  u
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

	//	av_packet_unref(&pkt);// 释放
	//}





	//char *path = "video.mp4";      //设置路径   这个视频是放在我的bin目录下面的 
	//
	//



	//// 打开视频解码器
	//int videoStream = 0;
	//AVCodecContext *videoCtx = NULL; // 存放解码器的内容
	//for (int i = 0; i < ic->nb_streams; i++) // 遍历视频流
	//{
	//	AVCodecContext *enc = ic->streams[i]->codec; // 解码器的值
	//	if (enc->codec_type == AVMEDIA_TYPE_VIDEO)   // 判断是不是一个视频
	//	{
	//		videoStream = i;
	//		videoCtx = enc; // 作为解码器的内容
	//		AVCodec *codec = avcodec_find_decoder(enc->codec_id);// 查找解码器 返回的是解码器的id
	//		if (!codec)
	//		{
	//			printf("video code not find!\n");
	//			return -1;
	//		}
	//		int err = avcodec_open2(enc, codec, NULL);// 打开这个解码器
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
	//// 视频解码
	//AVFrame *yuv = av_frame_alloc(); // 定义一个帧来存放解码的内容  分配AVFrame这个对象的空间
	//// 定义解码器
	//SwsContext *cCtx = NULL;
	//int outwidth = 640;
	//int outheight = 480;
	//char *rgb = new char[outheight*outwidth * 4];

	//

	//// 读视频的信息
	//for (;;)        
	//{
	//	// 一帧数据
	//	AVPacket pkt;// 一个结构体存放视频信息
	//	re = av_read_frame(ic, &pkt);
	//	if (re != 0) break;
	//	printf("pts = %lld\n",pkt.pts);// pts  存放的时间戳  来控制进度
	//	//解码方法1
	//	//int got_picture = 0;// 是否获取了视频，获取了返回1
	//	// 解码视频  返回值：视频帧的大小。参数：打开的解码器，分配好的视频帧对象，是否获取了视频的标志位，对用的视频帧
	//	//int re = avcodec_decode_video2(videoCtx, yuv, &got_picture, &pkt);
	//	//if (got_picture)
	//	//{
	//	//	printf("[%d]", re);
	//	//}
	//	// 解码方法2
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

	//// 打开解码器
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
	//// 转码
	//uint8_t *data[AV_NUM_DATA_POINTERS] = {0}; // 8
	//data[0] = (uint8_t *)rgb;
	//int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	//linesize[0] = outwidth * 4;

	//// 转码函数   参数：打开的转码器，原数据的data，每一个的行数，0，原数据的高度，目标数据，每一个的行数
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








