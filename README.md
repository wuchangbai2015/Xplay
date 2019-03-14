************************************************************************************************************
源码src文件夹中的Xplay为一个播放器项目，现说明如下：

开发工具：VS2015 

开发环境：FFmpeg3.4.2 、qt5.9、C++ 

部分教程：

一.编解码过程

	1. 注册所有容器格式和CODEC:av_register_all()   http://mp.toutiao.com/preview_article/?pgc_id=6667895765584577028

	2. 打开文件:avformat_open_input()

	3. 从文件中提取流信息:av_find_stream_info()
	
	4. 穷举所有的流，查找其中种类为CODEC_TYPE_VIDEO
	
	5. 查找对应的解码器:avcodec_find_decoder()

	6. 打开编解码器:avcodec_open()

	7. 为解码帧分配内存:avcodec_alloc_frame()

	8. 不停地从码流中提取出帧数据:av_read_frame()

	9. 判断帧的类型，对于视频帧调用:avcodec_decode_video()

	10. 解码完后，释放解码器:avcodec_close()

	11. 关闭输入文件:av_close_input_file()

