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
	int SetMedia(std::string& strUrl);//请使用utf-8 的格式
	float VideoCtrl(VLCCommand cmd);//-1.0错误
	int SetPosition(float pos);
	int SetWnd(HWND hWnd);
	int SetVolume(int volume);
	VlcSize GetMediaInfomation();
	std::string Unicode2Utf8(const std::wstring& strIn);
protected:
	VLCTOOL m_vlc{};
	CVideoClinetDlg m_dlg;
};

