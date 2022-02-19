
// VideoClinetDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "VideoClinet.h"
#include "VideoClinetDlg.h"
#include "afxdialogex.h"
#include "VideoClientController.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <string>


// CVideoClinetDlg 对话框

CVideoClinetDlg::CVideoClinetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIDEOCLINET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVideoClinetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PLAY, m_video);
	DDX_Control(pDX, IDC_SLIDER_POS, m_pos);
	DDX_Control(pDX, IDC_SLIDER_VOLUME, m_volume);
	DDX_Control(pDX, IDC_EDIT_URL, m_url);
	DDX_Control(pDX, IDC_BTN_PLAY, m_btnPlay);
}

BEGIN_MESSAGE_MAP(CVideoClinetDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BTN_PLAY, &CVideoClinetDlg::OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_STOP, &CVideoClinetDlg::OnBnClickedBtnStop)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER_POS, &CVideoClinetDlg::OnTRBNThumbPosChangingSliderPos)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER_VOLUME, &CVideoClinetDlg::OnTRBNThumbPosChangingSliderVolume)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BTN_OPEMFILE, &CVideoClinetDlg::OnBnClickedBtnOpemfile)
END_MESSAGE_MAP()


// CVideoClinetDlg 消息处理程序

BOOL CVideoClinetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_pos.SetRange(0, 1);
	m_volume.SetRange(0, 100);
	m_volume.SetTicFreq(20);
	m_volume.SetPos(100);
	SetTimer(0, 500, NULL);//因为是我们接管了 这个初始化  VLC在前面


	m_controller->SetWnd(m_video.GetSafeHwnd()); //设置窗口 在构造的时候没有
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVideoClinetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CVideoClinetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVideoClinetDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0)
	{
		//获取播放状态,进度信息
		float pos = m_controller->VideoCtrl(VLCTOOL_GET_POSTION);
		if (pos != -1.0f)
		{//IDC_STATIC_TIME 更新播放时间
			static float length = 0.0f;
			length=m_controller->VideoCtrl(VLCTOOL_GET_LENGTH);
			if (m_video_length !=length)
			{
				m_video_length = length;
				m_pos.SetRange(0, int(length));
			}
			CString strPos;
			strPos.Format(L"%f/%f", pos*length,length);
			SetDlgItemText(IDC_STATIC_TIME, strPos);
			m_pos.SetPos(int(length*pos));
		}
		//更新音量 IDC_STATIC_VOLUME

	}
	CDialogEx::OnTimer(nIDEvent);
}


void CVideoClinetDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	KillTimer(0);
	// TODO: 在此处添加消息处理程序代码
}


void CVideoClinetDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnDropFiles(hDropInfo);
	WIN32_FIND_DATAW wfd;
	CString Path;
	wchar_t  Buffer[MAX_PATH];
	int nCounts = DragQueryFileW(hDropInfo, 0xFFFFFFFF, NULL, 0);
	if (nCounts == 1)
	{
		//TODO 记得转码
		DragQueryFileW(hDropInfo, 0, Buffer, MAX_PATH);
		FindClose(FindFirstFileW(Buffer, &wfd));
		Path.Format(L"file:///%s", Buffer);
		m_url.SetWindowTextW(Path);
	}
	else if (nCounts > 1)
	{
		AfxMessageBox(L"暂时处理不了这么多文件");
	}
}


void CVideoClinetDlg::OnBnClickedBtnPlay()
{
	if (status == false)
	{
		CString url;
		m_url.GetWindowText(url);
		//unicode to utf-8
		m_controller->SetMedia(m_controller->Unicode2Utf8((LPCTSTR)url));
		m_btnPlay.SetWindowTextW(L"暂停");
		status = true;
		m_controller->VideoCtrl(VLCTOOL_PLAY);
	}
	else
	{
		m_btnPlay.SetWindowTextW(L"播放");
		status = false;
		m_controller->VideoCtrl(VLCTOOL_PAUSE);
	}
}


void CVideoClinetDlg::OnBnClickedBtnStop()
{
	m_btnPlay.SetWindowTextW(L"播放");
	status = false;
	m_controller->VideoCtrl(VLCTOOL_STOP);
}


void CVideoClinetDlg::OnTRBNThumbPosChangingSliderPos(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING* pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	TRACE("pos %d reason %d\r\n", pNMTPC->dwPos, pNMTPC->nReason);
	AfxMessageBox(L"cc");
}


void CVideoClinetDlg::OnTRBNThumbPosChangingSliderVolume(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING* pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	TRACE("pos %d reason %d\r\n", pNMTPC->dwPos, pNMTPC->nReason);
	AfxMessageBox(L"cc");
}


void CVideoClinetDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (nSBCode == 5)
	{
		CString strPosition{};
		TRACE("pos %p volume %p cur %p pos %d nSBcod %d \r\n", &m_pos, &m_volume, pScrollBar, nPos, nSBCode);
		if ((unsigned)&m_pos == (unsigned)pScrollBar)//播放时间
		{
			strPosition.Format(_T("%d%%"), nPos);
			SetDlgItemText(IDC_STATIC_TIME, strPosition);
			m_controller->SetPosition(float(nPos/m_video_length));
		}
		else//声音
		{
			strPosition.Format(_T("%d%%"), nPos);
			SetDlgItemText(IDC_STATIC_VOLUME, strPosition);
			m_controller->SetVolume(nPos);
		}
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CVideoClinetDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CVideoClinetDlg::OnBnClickedBtnOpemfile()
{
	TCHAR szFilters[] = _T("音频文件 (*.mp4)|*.mp4| 音频文件 (*.mp3)|*.mp3|  All Files (*.*)|*.*||");
	CFileDialog dialog
	(
		TRUE,
		NULL,//后缀 
		NULL,//文件名
		6,
		szFilters//文件过滤器
	);
	CString tmp{};
	if (dialog.DoModal() == IDOK)
	{
		tmp = dialog.GetPathName();
		tmp.Format(L"file:///%s", tmp.GetBuffer());
		m_url.SetWindowTextW(tmp);
	}
}
