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
	//strUrl 请传入 utf-8的编码格式
	int SetMedia(const std::string& strUrl);
#ifdef WIN32
	int SetHwnd(HWND hWnd);
#endif // WIN32
	int Play();
	int Pause();
	int Stop();
	float GetPostion();
	int SetPostion(float pos);
	int GetVolume();
	int SetVolume(int volume);
	float GetLength();
	VlcSize GetMediaInfomation();
	std::string Unicode2Utf8(const std::wstring& strIn);
protected:
	libvlc_instance_t* m_instance{};
	libvlc_media_t* m_media{};
	libvlc_media_player_t* m_player{};
	std::string m_Strurl;
#ifdef WIN32
	HWND m_hwnd;
#endif // WIN32

};