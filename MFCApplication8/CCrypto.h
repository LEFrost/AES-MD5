#pragma once
#include "aes.h"
#include "hex.h"      // StreamTransformationFilter
#include "modes.h"
#include "md5.h"
using namespace std;
using namespace CryptoPP;
class CCrypto
{
private:
	string Key;
public:
	CCrypto();
	CCrypto(CString key);
	~CCrypto();
	CString AESDecrypt(CString cipherText);
	CString AESEncrypt(CString plainText);
	CString MD5Encrypt(CString cipherText);
private:

};

