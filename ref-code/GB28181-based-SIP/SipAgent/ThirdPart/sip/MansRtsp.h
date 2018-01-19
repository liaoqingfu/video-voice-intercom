#pragma once

/*
详见 安全防范视频监控联网系统 GB28181中关于MANSRTSP的描述

PLAY MANSRTSP/1.0
CSeq:5
Scale:1.0
Range:npt=196-

PAUSE MANSRTSP/1.0
CSeq:5
Range:npt=123(可选)

TEARDOWN MANSRTSP/1.0
CSeq:5



解析MansRtsp
*/
class MansRtsp
{
public:
	MansRtsp(void);
	~MansRtsp(void);

public:
	void ParseMansRtsp(const char* buf);

public:
	char method[16];
	int cseq;
	double scale;
	int nptStart;
	int nptEnd;
};
