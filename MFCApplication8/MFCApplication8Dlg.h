
// MFCApplication8Dlg.h : 头文件
//

#pragma once
//using namespace std;

// CMFCApplication8Dlg 对话框
class CMFCApplication8Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication8Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION8_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	//std::string ECB_AESEncryptStr(std::string sKey, const char *plainText);
	//std::string ECB_AESDecryptStr(std::string sKey, const char *cipherText);
};
