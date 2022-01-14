
// MultiPipeServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MultiPipeServer.h"
#include "MultiPipeServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMultiPipeServerDlg 대화 상자



CMultiPipeServerDlg::CMultiPipeServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MULTIPIPESERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMultiPipeServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMultiPipeServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMultiPipeServerDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMultiPipeServerDlg 메시지 처리기

BOOL CMultiPipeServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMultiPipeServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMultiPipeServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMultiPipeServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



DWORD WINAPI TranslateThread(LPVOID p)
{
	HANDLE hPipe = (HANDLE)p;
	TCHAR szInput[255], szOutput[255];
	DWORD dwRead, dwWritten;
	BOOL bSuccess;

	for (;;)
	{
		// 1) 파이프로 부터 읽기
		bSuccess = ReadFile(hPipe, szInput, 255, &dwRead, NULL);
		if ((bSuccess == FALSE) || (dwRead == 0)) break;
		
		// 2) 번역
		if (lstrcmp(szInput, _T("one")) == 0)
			lstrcpy(szOutput, _T("하나"));
		else if (lstrcmp(szInput, _T("two")) == 0)
			lstrcpy(szOutput, _T("둘"));
		else if (lstrcmp(szInput, _T("three")) == 0)
			lstrcpy(szOutput, _T("셋"));
		else if (lstrcmp(szInput, _T("four")) == 0)
			lstrcpy(szOutput, _T("넷"));
		else if (lstrcmp(szInput, _T("five")) == 0)
			lstrcpy(szOutput, _T("다섯"));
		else
			lstrcpy(szOutput, _T("해석불가"));

		// 3) 파이프에 결과 쓰기 
		bSuccess = WriteFile(hPipe, szOutput, (lstrlen(szOutput) + 1) * sizeof(TCHAR), &dwWritten, NULL);
		if ((bSuccess == FALSE) || (dwWritten == 0)) break;
	}

	// 4. 뒷정리 
	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	return 0;
}

DWORD WINAPI ListenThread(LPVOID p)
{
	HANDLE hPipe;

	for (;;)	// for : 다수의 클라이언트 처리용 
	{
		// 1. 파이프 생성
		hPipe =
			CreateNamedPipe(_T("\\\\.\\pipe\\loveletter"),
				PIPE_ACCESS_DUPLEX,
				PIPE_TYPE_BYTE,
				3,	// 동시접속 
				0, 0, 0, NULL);	// OS에게 맡김

		// 2. 파이프 접속 대기
		BOOL bConnect;
		bConnect = ConnectNamedPipe(hPipe, NULL);
		if ((bConnect == FALSE) && (GetLastError() == ERROR_PIPE_CONNECTED))
		{
			bConnect = TRUE;
		}

		// 3. 서비스 진행(통신)
		if (bConnect == TRUE)
		{
			// for : 1명의 고객을 위한 무한 서비스용 
			CloseHandle(CreateThread(NULL, 0, TranslateThread, hPipe, 0, NULL));
		}		
	}
	return 0;
}


void CMultiPipeServerDlg::OnBnClickedButton1()
{
	DWORD ThreadID;
	CloseHandle(CreateThread(NULL, 0, ListenThread, this, 0, &ThreadID));
}
