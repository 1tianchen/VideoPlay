#pragma once
#include "VLCTOOL.h"
#include "VideoClinetDlg.h"
enum VLCCommand
{
	VLCTOOL_PLAY,
	VLCTOOL_PAUSE,
	VLCTOOL_STOP,
	VLCTOOL_GET_VOLUME,
	VLCTOOL_GET_POSTION,
	VLCTOOL_GET_LENGTH
};
class VideoClientController
{
public:
	VideoClientController();
	~VideoClientController();
	int Init(CWnd*& pWnd);
	int Invoke();
	int SetMedia(std::string& strUrl);//��ʹ��utf-8 �ĸ�ʽ
	float VideoCtrl(VLCCommand cmd);//-1.0����
	int SetPosition(float pos);
	int SetWnd(HWND hWnd);
	int SetVolume(int volume);
	VlcSize GetMediaInfomation();
	std::string Unicode2Utf8(const std::wstring& strIn);
protected:
	VLCTOOL m_vlc{};
	CVideoClinetDlg m_dlg;
};

