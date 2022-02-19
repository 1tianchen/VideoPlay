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
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
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
