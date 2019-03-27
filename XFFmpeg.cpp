#include "XFFmpeg.h"
//预处理指令导入库
#pragma comment(lib,"avformat.lib") // 文件格式   依赖库
#pragma comment(lib, "avutil.lib")  // 工具类库     获取错误信息的库
#pragma comment(lib, "avcodec.lib") // 编码格式
#pragma comment(lib, "swscale.lib") // YUV转RGB

#pragma comment(lib, "swresample.lib") // 音频重采样的库文件


static double r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}

int XFFmpeg::Open(const char *path)
{
	Close();
	mutex.lock();
	int re = avformat_open_input(&ic, path, 0, 0); //打开文件流
	if (re != 0) //打开失败
	{
		mutex.unlock();
		av_strerror(re, errorbuf, sizeof(errorbuf)); // 输出错误的信息
		printf("open %s failed: %s\n", path, errorbuf);
		return 0;
	}
	// 获取视频的时长 单位s
	int totalMs = (ic->duration / AV_TIME_BASE *1000);
	//printf("file totleSec is %d-%d\n", totalMs / 60, totalMs % 60);
	
	

	for (int i = 0; i < ic->nb_streams; i++)         // 遍历视频流
	{
		AVCodecContext *enc = ic->streams[i]->codec; // 解码器的值
		if (enc->codec_type == AVMEDIA_TYPE_VIDEO)   // 判断是不是一个视频
		{
			videoStream = i;
			fps = r2d(ic->streams[i]->avg_frame_rate);
			AVCodec *codec = avcodec_find_decoder(enc->codec_id);// 查找解码器 返回的是解码器的id
			if (!codec)
			{
				mutex.unlock();
				printf("video code not find!\n");
				return 0;
			}
			int err = avcodec_open2(enc, codec, NULL);// 打开这个解码器
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
		else if (enc->codec_type == AVMEDIA_TYPE_AUDIO) // 判断是不是一个音频流
		{
			audioStream = i;
			AVCodec *codec = avcodec_find_decoder(enc->codec_id);
			if (avcodec_open2(enc, codec, NULL) < 0)
			{
				mutex.unlock();
				return false;
			}
			this->sampleRate = enc->sample_rate;
			this->channelCount = enc->channels;
			switch ((enc->sample_fmt))
			{
			case AV_SAMPLE_FMT_S16:  // 16bit
				this->sampleSize = 16;
				break;
			case AV_SAMPLE_FMT_S32:  // 16bit
				this->sampleSize = 32;
				break;
			default:
				break;
			}
			printf("audio sample rate:%d sample size:%d chanle:%d\n", this->sampleRate, this->sampleSize, this->channelCount);

		}
	}
	mutex.unlock();
	return totalMs;
}
void XFFmpeg::Close()
{
	mutex.lock();
	if(ic) avformat_close_input(&ic); //释放
	if (yuv) av_frame_free(&yuv);
	if (cCtx)
	{
		sws_freeContext(cCtx);
		cCtx = NULL;
	}
	if (aCtx)
	{
		swr_free(&aCtx);
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

AVPacket XFFmpeg::Read()// 读取视频
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

int XFFmpeg::Decode(const AVPacket *pkt)
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

	if (pcm == NULL)
	{
		pcm = av_frame_alloc();
	}

	AVFrame *frame = yuv;
	if (pkt->stream_index == audioStream)// 判断要是音频 我们就将解码后的数据存放在pcm中  视频的就存放在yuv中
	{
		frame = pcm;
	}
	int re = avcodec_send_packet(ic->streams[pkt->stream_index]->codec, pkt);
	if (re != 0)
	{
		mutex.unlock();
		return NULL;
	}
	re = avcodec_receive_frame(ic->streams[pkt->stream_index]->codec, frame);
	if (re != 0)
	{
		mutex.unlock();
		return NULL;
	}
	mutex.unlock();
	int p = (frame->pts *r2d(ic->streams[pkt->stream_index]->time_base))*1000;// 获取当前播放的位置
	if (pkt->stream_index == audioStream)
	{
		this->pts = p;
	}

	return p;

}

bool XFFmpeg::Seek(float pos) // 拖动进度条
{
	mutex.lock();
	if (!ic)
	{
		mutex.unlock();
		return false;
	}
	int64_t stamp = 0;
	// streams 存放的视频流  videoStream 存放的视频流的索引 
	stamp = pos * ic->streams[videoStream]->duration; 
	int re = av_seek_frame(ic, videoStream, stamp, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
	avcodec_flush_buffers(ic->streams[videoStream]->codec);

	pts = (stamp *r2d(ic->streams[videoStream]->time_base)) * 1000;// 获取当前播放的位置
	
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
	// 打开解码器
	AVCodecContext *videoCtx =ic->streams[this->videoStream]->codec;
	//设置格式转换器
	cCtx = sws_getCachedContext(NULL, //第一参数可以传NULL，默认会开辟一块新的空间
		videoCtx->width,
		videoCtx->height,            
		videoCtx->pix_fmt,            //原始数据的宽高和原始像素格式
		outwidth, outheight,          // 目标宽，目标高
		AV_PIX_FMT_BGRA,              //目标的像素格式
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

	// 转码
	uint8_t *data[AV_NUM_DATA_POINTERS] = {0}; // 8
	data[0] = (uint8_t *)out;
	int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	linesize[0] = outwidth * 4;

	// 转码函数   参数：打开的转码器，原数据的data，每一个的行数，0，原数据的高度，目标数据，每一个的行数
	int h = sws_scale(cCtx, yuv->data, yuv->linesize, 0, videoCtx->height, //把帧从原始格式（videoCtx->pix_fmt）转换成为RGB格式
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
	av_register_all();             //注册所有的格式
}


XFFmpeg::~XFFmpeg()
{
}


int  XFFmpeg::ToPCM(char *out)
{
	mutex.lock();
	if (!ic || !pcm || !out)
	{
		mutex.unlock();
		return 0;
	}

	AVCodecContext *ctx = ic->streams[audioStream]->codec;
	if (aCtx == NULL)
	{
		aCtx = swr_alloc();
		swr_alloc_set_opts(aCtx, ctx->channel_layout,
			AV_SAMPLE_FMT_S16,
			ctx->sample_rate, ctx->channels, 
			ctx->sample_fmt,
			ctx->sample_rate,
			0, 0
		);
		swr_init(aCtx);
	}

	uint8_t *data[1];
	data[0] = (uint8_t *)out;
	int len = swr_convert(aCtx, data, 10000,
		(const uint8_t **)pcm->data,
		pcm->nb_samples
	);
	if (len <= 0)
	{
		mutex.unlock();
		return 0;
	}
	int outsize = av_samples_get_buffer_size(NULL, ctx->channels, 
		pcm->nb_samples, AV_SAMPLE_FMT_S16, 0
	);

	mutex.unlock();
	return outsize;
}
