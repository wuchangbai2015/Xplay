#pragma once
#include <QThread>

class XVideoThread:public QThread
{
public:
	static XVideoThread *Get()
	{
		static XVideoThread vt;
		return &vt;
	}
	void run();
	XVideoThread();
	virtual ~XVideoThread();
};

