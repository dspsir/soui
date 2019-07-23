// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"	
	
CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;
}

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;
	SWindow *pWnd = FindChildByName(L"wnd_test");
	if (pWnd)
	{
		pWnd->SetMatrix(SMatrix().rotate(10));
	}
	return 0;
}
void CMainDlg::onBtnTest()
{
	SWindow *pTst = FindChildByName(L"txt_test");
	if (pTst)
	{
		IAnimation *pAni = SApplication::getSingletonPtr()->LoadAnimation(L"anim",L"test");
		if(pAni)
		{
			pTst->SetAnimation(pAni);
			pAni->Release();
		}
	}
}
//TODO:消息映射
void CMainDlg::OnClose()
{
	SNativeWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;
	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}

void CMainDlg::onBtnShow()
{
	SWindow *pWnd = FindChildByName(L"pane_left");
	if(pWnd && !pWnd->IsVisible(FALSE))
	{
		IAnimation *pAni = SApplication::getSingletonPtr()->LoadAnimation(L"anim",L"slide_show");
		if(pAni)
		{
			pWnd->SetVisible(TRUE);
			pWnd->SetAnimation(pAni);
			pAni->Release();
		}
	}
}

void CMainDlg::onBtnHide()
{
	SWindow *pWnd = FindChildByName(L"pane_left");
	if(pWnd && pWnd->IsVisible(FALSE))
	{
		IAnimation *pAni = SApplication::getSingletonPtr()->LoadAnimation(L"anim",L"slide_hide");
		if(pAni)
		{
			pAni->setAnimationListener(this);
			pWnd->SetAnimation(pAni);
			pAni->Release();
		}
	}
}

void CMainDlg::onAnimationStart(IAnimation * animation)
{
}

void CMainDlg::onAnimationEnd(IAnimation * animation)
{
	SWindow *pWnd = FindChildByName(L"pane_left");
	if(pWnd && pWnd->IsVisible(FALSE))
	{
		pWnd->SetVisible(FALSE,TRUE);
	}
}

void CMainDlg::onAnimationRepeat(IAnimation * animation)
{
}

