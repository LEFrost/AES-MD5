
// MFCApplication8Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication8.h"
#include "MFCApplication8Dlg.h"
#include "afxdialogex.h"
#include "aes.h"
#include "hex.h"      // StreamTransformationFilter
#include "modes.h"
#include"CCrypto.h"
using namespace std;
using namespace CryptoPP;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCApplication8Dlg 对话框



CMFCApplication8Dlg::CMFCApplication8Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION8_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication8Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication8Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCApplication8Dlg 消息处理程序

BOOL CMFCApplication8Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication8Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication8Dlg::OnPaint()
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
HCURSOR CMFCApplication8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



std::string ECB_AESEncryptStr(std::string sKey, const char *plainText)
{
	std::string outstr;

	//填key  
	SecByteBlock key(AES::MAX_KEYLENGTH);
	memset(key, 0x30, key.size());
	sKey.size() <= AES::MAX_KEYLENGTH ? 
		memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);


	AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);

	ECB_Mode_ExternalCipher::Encryption ecbEncryption(aesEncryption);
	StreamTransformationFilter ecbEncryptor(ecbEncryption, new HexEncoder(new StringSink(outstr)));
	ecbEncryptor.Put((byte *)plainText, strlen(plainText));
	ecbEncryptor.MessageEnd();

	return outstr;
}


std::string ECB_AESDecryptStr(std::string sKey, const char *cipherText)
{
	std::string outstr;

	//填key  
	SecByteBlock key(AES::MAX_KEYLENGTH);
	memset(key, 0x30, key.size());
	sKey.size() <= AES::MAX_KEYLENGTH ? 
		memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);

	ECB_Mode<AES >::Decryption ecbDecryption((byte *)key, AES::MAX_KEYLENGTH);

	HexDecoder decryptor(new StreamTransformationFilter(ecbDecryption, new StringSink(outstr)));
	decryptor.Put((byte *)cipherText, strlen(cipherText));
	decryptor.MessageEnd();

	return outstr;
}



void CMFCApplication8Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString a( _T("This Program shows how to use ECB, CBC, CBC_CTS, CFB, OFB and CTR mode of AES in Crypto++."));
	CCrypto c;
	CString b(_T("abc"));
	CString re3 = c.MD5Encrypt(b);
	CString re1= c.AESEncrypt(a);
	CString re2 = c.AESDecrypt(re1);
}
