#include "pch.h"
#include "VideoClientController.h"

VideoClientController::VideoClientController()
{
	m_dlg.m_controller=this;
}

VideoClientController::~VideoClientController()
{

}

int VideoClientController::Init(CWnd*& pWnd)
{
	pWnd = &m_dlg;

	return 0;
}

int VideoClientController::Invoke()
{
	INT_PTR nResponse = m_dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}
	return nResponse;
}

int VideoClientController::SetMedia(std::string& strUrl)
{
	return m_vlc.SetMedia(strUrl);
}

float VideoClientController::VideoCtrl(VLCCommand cmd)
{
	switch (cmd)
	{
	case VLCTOOL_PLAY:
		return  float(m_vlc.Play());
		break;
	case VLCTOOL_PAUSE:
		return float(m_vlc.Pause());
		break;
	case VLCTOOL_STOP:
		return float(m_vlc.Stop());
		break;
	case VLCTOOL_GET_VOLUME:
		return float(m_vlc.GetVolume());
		break;
	case VLCTOOL_GET_POSTION:
		return float(m_vlc.GetPostion());
		break;
	case VLCTOOL_GET_LENGTH:
		return float(m_vlc.GetLength());
		break;;
	default:
		break;
	}
	return -1.0f;
}

int VideoClientController::SetPosition(float pos)
{
	return m_vlc.SetPostion(pos);
}

int VideoClientController::SetWnd(HWND hWnd)
{
	return m_vlc.SetHwnd(hWnd);
}

int VideoClientController::SetVolume(int volume)
{
	return m_vlc.SetVolume(volume);
}

VlcSize VideoClientController::GetMediaInfomation()
{
	return m_vlc.GetMediaInfomation();
}

std::string VideoClientController::Unicode2Utf8(const std::wstring& strIn)
{
	return m_vlc.Unicode2Utf8(strIn);
}
