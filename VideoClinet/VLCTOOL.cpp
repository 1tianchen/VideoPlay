#include "pch.h"
#include "VLCTOOL.h"

VLCTOOL::VLCTOOL()
{
	m_instance = libvlc_new(0, NULL);
	m_media = NULL;
	m_player = NULL;
}

VLCTOOL::~VLCTOOL()
{
	if (m_player != NULL)
	{
		libvlc_media_player_t* temp = m_player;
		m_player = NULL;					//����ʽ��� ��ֹ��������ʱ��ʹ��
		libvlc_media_player_release(temp);
	}
	if (m_media != NULL)
	{
		libvlc_media_t* temp = m_media;
		m_media = NULL;					//����ʽ��� ��ֹ��������ʱ��ʹ��
		libvlc_media_release(temp);
	}
	if (m_instance != NULL)
	{
		libvlc_instance_t* temp = m_instance;
		m_instance = NULL;					//����ʽ��� ��ֹ��������ʱ��ʹ��
		libvlc_release(temp);
	}

}

int VLCTOOL::SetMedia(const std::string& strUrl)
{
	if (m_instance == NULL)
	{
		return -1;
	}
	m_media = libvlc_media_new_location(m_instance, strUrl.c_str());
	if (!m_media)
	{
		return -2;
	}
	m_player = libvlc_media_player_new_from_media(m_media);
	if (!m_player)
	{
		return -3;
	}
	return 0;
}

int VLCTOOL::SetHwnd(HWND hWnd)
{
	if (!m_player || !m_instance || !m_media || !hWnd)
	{
		return -1;
	}
	libvlc_media_player_set_hwnd(m_player, hWnd);
	return 0;
}

int VLCTOOL::Play()
{
	if (!m_player || !m_instance || !m_media)
	{
		return -1;
	}
	return libvlc_media_player_play(m_player);
}

int VLCTOOL::Pause()
{
	if (!m_player || !m_instance || !m_media)
	{
		return -1;
	}
	libvlc_media_player_pause(m_player);
	return 0;
}

int VLCTOOL::Stop()
{
	if (!m_player || !m_instance || !m_media)
	{
		return -1;
	}
	libvlc_media_player_stop(m_player);;
	return 0;
}

float VLCTOOL::GetPostion()
{
	if (!m_player || !m_instance || !m_media)
	{
		return -1.0f;
	}
	return libvlc_media_player_get_position(m_player);
}

int VLCTOOL::SetPostion(float pos)
{
	if (!m_player || !m_instance || !m_media)
	{
		return -1;
	}
	libvlc_media_player_set_position(m_player, pos);
	return 0;
}

int VLCTOOL::GetVolume()
{
	if (!m_player || !m_instance || !m_media)
	{
		return -1;
	}
	return libvlc_audio_get_volume(m_player);
}

int VLCTOOL::SetVolume(int volume)
{
	if (!m_player || !m_instance || !m_media)
	{
		return -1;
	}
	return libvlc_audio_set_volume(m_player,volume);
}

VlcSize VLCTOOL::GetMediaInfo()
{
	if (!m_player || !m_instance || !m_media)
	{
		return -1;
	}
	return VlcSize(
		libvlc_video_get_height(m_player),
		libvlc_video_get_width(m_player)
	);
}
