
// MFCApplication8Dlg.h : ͷ�ļ�
//

#pragma once
//using namespace std;

// CMFCApplication8Dlg �Ի���
class CMFCApplication8Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication8Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION8_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
