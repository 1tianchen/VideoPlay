#pragma once
#include <string>
#include <vlc.h>
class VlcSize
{
public:
	int nWidth;
	int nHeight;
	VlcSize(int width = 0,int height = 0)
	{
		nWidth = width;
		nHeight = height;
	}
	VlcSize(const VlcSize& size)
	{
		nWidth = size.nWidth;
		nHeight = size.nHeight;
	}
	VlcSize& operator=(const VlcSize& size)
	{
		if (this != &size)
		{
			nWidth = size.nWidth;
			nHeight = size.nHeight;
		}
		return *this;
	}
};

class VLCTOOL
{
public:
	VLCTOOL();
	~VLCTOOL();
	//strUrl �봫�� utf-8�ı����ʽ
	int SetMedia(const std::string& strUrl);
	int SetHwnd(HWND hWnd);
	int Play();
	int Pause();
	int Stop();
	float GetPostion();
	int SetPostion(float pos);
	int GetVolume();
	int SetVolume(int volume);
	VlcSize GetMediaInfo();
protected:
	libvlc_instance_t* m_instance;
	libvlc_media_t* m_media;
	libvlc_media_player_t* m_player;
};