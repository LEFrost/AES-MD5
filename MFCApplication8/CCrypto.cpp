#include"stdafx.h"
#include"CCrypto.h"
CCrypto::CCrypto()
{
	Key = "mbWIPa2nD389wEOU0M7PwoYYDm1NOjo7";
}

CCrypto::CCrypto(CString key)
{
	if (key.GetLength() < 32)
		throw "Key长度小于32";
	else
		Key = CT2A(key);
}

CCrypto::~CCrypto()
{
}

CString CCrypto::AESDecrypt(CString cipherText)
{
	string outstr;
	string temp = CT2A(cipherText);
	const char * tempText = temp.c_str();
	//填key  
	SecByteBlock key(AES::MAX_KEYLENGTH);
	memset(key, 0x30, key.size());
	Key.size() <= AES::MAX_KEYLENGTH ?
		memcpy(key, Key.c_str(), Key.size()) : memcpy(key, Key.c_str(), AES::MAX_KEYLENGTH);

	ECB_Mode<AES >::Decryption ecbDecryption((byte *)key, AES::MAX_KEYLENGTH);

	HexDecoder decryptor(new StreamTransformationFilter(ecbDecryption, new StringSink(outstr)));
	decryptor.Put((byte *)tempText, strlen(tempText));
	decryptor.MessageEnd();

	return CString(outstr.c_str());
}

CString CCrypto::AESEncrypt(CString plainText)
{
	string outstr;
	string temp = CT2A(plainText);
	const char * tempText = temp.c_str();
	//填key  
	SecByteBlock key(AES::MAX_KEYLENGTH);
	memset(key, 0x30, key.size());
	Key.size() <= AES::MAX_KEYLENGTH ?
		memcpy(key, Key.c_str(), Key.size()) : memcpy(key, Key.c_str(), AES::MAX_KEYLENGTH);


	AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);

	ECB_Mode_ExternalCipher::Encryption ecbEncryption(aesEncryption);
	StreamTransformationFilter ecbEncryptor(ecbEncryption, new HexEncoder(new StringSink(outstr)));
	ecbEncryptor.Put((byte *)tempText, strlen(tempText));
	ecbEncryptor.MessageEnd();

	return CString(outstr.c_str());
}

CString CCrypto::MD5Encrypt(CString cipherText)
{
	string message = CT2A(cipherText);
	string digest;
	MD5 md5;
	StringSource(message, true,
		new HashFilter(md5, new HexEncoder(new StringSink(digest))));
	return CString(digest.c_str());
	//string tempText = CT2A(cipherText);
	//int len = tempText.length();
	//byte* message = new byte[len + 1];
	//message[len] = 0;
	//memcpy(message, tempText.c_str(), len + 1);
	//byte digest[16];
	//MD5 md5;
	////md5.CalculateDigest(digest, message, len);
	//md5.Update(message, len);
	//md5.Final(digest);
	//CString* tempReturn = new CString((char*)digest, 16);
	//CString returnString = *tempReturn;
	//delete message;
	//delete tempReturn;
	//return returnString;
}
