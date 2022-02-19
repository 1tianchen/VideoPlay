﻿
// VideoClinetDlg.h: 头文件
//

#pragma once

class VideoClientController;

// CVideoClinetDlg 对话框
class CVideoClinetDlg : public CDialogEx
{
// 构造
public:
	CVideoClinetDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEOCLINET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedBtnPlay();

public:
	 afx_msg void OnBnClickedBtnStop();
	 afx_msg void OnTRBNThumbPosChangingSliderPos(NMHDR* pNMHDR, LRESULT* pResult);
	 afx_msg void OnTRBNThumbPosChangingSliderVolume(NMHDR* pNMHDR, LRESULT* pResult);
	 afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	 afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
protected:
	//播放状态
	bool status = false;
	CButton m_btnPlay;
	CEdit m_video;
	CSliderCtrl m_pos;
	CSliderCtrl m_volume;
	CEdit m_url;
	float m_video_length{};
public:
	VideoClientController* m_controller;
	afx_msg void OnBnClickedBtnOpemfile();
};
