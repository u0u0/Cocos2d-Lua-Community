#include <stdlib.h>

#include "scripting/lua-bindings/manual/extra/lua_crypto_manual.h"
#include "external/xxtea/xxtea.h"
#include "base/base64.h"
#include "md5/md5.h"
#include "openssl/aes.h"
#include "platform/CCFileUtils.h"

#define MD5_DIGEST_LENGTH (16)
#define AES256_CHUNK_SIZE (16)
#define AES256_KEY_SIZE (32)

using namespace cocos2d;

static int tolua_extra_Crypto_encryptAES256(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
			!tolua_isstring(tolua_S,4,0,&tolua_err) ||
			!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,6,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		const unsigned char *plaintext = (const unsigned char *)tolua_tostring(tolua_S,2,0);
		size_t plainLength = tolua_tonumber(tolua_S,3,0);
		const char *key = (const char *)tolua_tostring(tolua_S,4,0);
		int keyLength = tolua_tonumber(tolua_S,5,0);

		// make key
		unsigned char aesKeyBuf[AES256_KEY_SIZE] = {0};
		strncpy((char *)aesKeyBuf, key, MIN(AES256_KEY_SIZE, keyLength));
		AES_KEY aesKey;
		AES_set_encrypt_key(aesKeyBuf, 256, &aesKey);

		// AES_ENCRYPT
		unsigned int outLength = (plainLength % AES256_CHUNK_SIZE ? plainLength / AES256_CHUNK_SIZE + 1 : plainLength / AES256_CHUNK_SIZE) * AES256_CHUNK_SIZE;
		unsigned char *ciphertext = (unsigned char *)malloc(outLength);
		memset(ciphertext, 0, outLength);
		unsigned char ivec[AES256_CHUNK_SIZE] = {0};
		AES_cbc_encrypt(plaintext, ciphertext, plainLength, &aesKey, ivec, AES_ENCRYPT);

		lua_pushlstring(tolua_S, (const char*)ciphertext, outLength);
		free(ciphertext);
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'encryptAES256'.",&tolua_err);
	return 0;
#endif
}

static int tolua_extra_Crypto_decryptAES256(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
			!tolua_isstring(tolua_S,4,0,&tolua_err) ||
			!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,6,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		unsigned char *ciphertext = (unsigned char *)tolua_tostring(tolua_S,2,0);
		int cipherLength = tolua_tonumber(tolua_S,3,0);
		const char *key = (const char *)tolua_tostring(tolua_S,4,0);
		int keyLength = tolua_tonumber(tolua_S,5,0);

		// make key
		unsigned char aesKeyBuf[AES256_KEY_SIZE] = {0};
		strncpy((char *)aesKeyBuf, key, MIN(AES256_KEY_SIZE, keyLength));
		AES_KEY aesKey;
		AES_set_decrypt_key(aesKeyBuf, 256, &aesKey);

		// AES_DECRYPT
		unsigned int outLength = (cipherLength % AES256_CHUNK_SIZE ? cipherLength / AES256_CHUNK_SIZE + 1 : cipherLength / AES256_CHUNK_SIZE) * AES256_CHUNK_SIZE;
		unsigned char *plaintext = (unsigned char *)malloc(outLength);
		memset(plaintext, 0, outLength);
		unsigned char ivec[AES256_CHUNK_SIZE] = {0};
		AES_cbc_encrypt(ciphertext, plaintext, cipherLength, &aesKey, ivec, AES_DECRYPT);

		lua_pushlstring(tolua_S, (const char*)plaintext, outLength);
		free(plaintext);
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'decryptAES256'.",&tolua_err);
	return 0;
#endif
}

static int tolua_extra_Crypto_encryptXXTEA(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
			!tolua_isstring(tolua_S,4,0,&tolua_err) ||
			!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,6,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		unsigned char* plaintext = (unsigned char *)tolua_tostring(tolua_S,2,0);
		int plaintextLength = tolua_tonumber(tolua_S,3,0);
		unsigned char* key = (unsigned char *)tolua_tostring(tolua_S,4,0);
		int keyLength = tolua_tonumber(tolua_S,5,0);

		xxtea_long resultLength;
		unsigned char *result = xxtea_encrypt(plaintext, (xxtea_long)plaintextLength, key, (xxtea_long)keyLength, &resultLength);
		if (resultLength <= 0) {
			lua_pushnil(tolua_S);
		} else {
			lua_pushlstring(tolua_S, (const char*)result, resultLength);
			free(result);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'encryptXXTEA'.",&tolua_err);
	return 0;
#endif
}

static int tolua_extra_Crypto_decryptXXTEA(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
			!tolua_isstring(tolua_S,4,0,&tolua_err) ||
			!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,6,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		unsigned char* ciphertext = (unsigned char *)tolua_tostring(tolua_S,2,0);
		int ciphertextLength = tolua_tonumber(tolua_S,3,0);
		unsigned char* key = (unsigned char *)tolua_tostring(tolua_S,4,0);
		int keyLength = tolua_tonumber(tolua_S,5,0);

		xxtea_long resultLength;
		unsigned char *result = xxtea_decrypt(ciphertext, (xxtea_long)ciphertextLength, key, (xxtea_long)keyLength, &resultLength);
		if (resultLength <= 0) {
			lua_pushnil(tolua_S);
		} else {
			lua_pushlstring(tolua_S, (const char*)result, resultLength);
			free(result);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'decryptXXTEA'.",&tolua_err);
	return 0;
#endif
}

static int tolua_extra_Crypto_encodeBase64(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,4,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		const unsigned char *input = (const unsigned char *)tolua_tostring(tolua_S,2,0);
		unsigned int inputLength = tolua_tonumber(tolua_S,3,0);

		char *encodedData = nullptr;
		int outLength = base64Encode(input, inputLength, &encodedData);
		if (encodedData) {
			lua_pushlstring(tolua_S, (const char*)encodedData, outLength);
			free(encodedData);
		} else {
			lua_pushnil(tolua_S);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'encodeBase64'.",&tolua_err);
	return 0;
#endif
}

static int tolua_extra_Crypto_decodeBase64(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,3,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		const unsigned char *input = (const unsigned char *)tolua_tostring(tolua_S,2,0);
		unsigned int inLen = lua_objlen(tolua_S,2);
		unsigned char *decodedData = nullptr;
		int decodeLen = base64Decode(input, (unsigned int)inLen, &decodedData);
		if (decodedData) {
			lua_pushlstring(tolua_S, (const char*)decodedData, decodeLen);
			free(decodedData);
		} else {
			lua_pushnil(tolua_S);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'decodeBase64'.",&tolua_err);
	return 0;
#endif
}

static int tolua_extra_Crypto_md5(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isboolean(tolua_S,3,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,4,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		const md5_byte_t *input = (const md5_byte_t *)tolua_tostring(tolua_S,2,0);
		int inLen = lua_objlen(tolua_S,2);
		bool isRawOutput = tolua_toboolean(tolua_S,3,0);

		md5_state_t state;
		md5_byte_t digest[MD5_DIGEST_LENGTH];
		md5_init(&state);
		md5_append(&state, input, inLen);
		md5_finish(&state, digest);

		if (isRawOutput) {
			lua_pushlstring(tolua_S, (const char*)digest, MD5_DIGEST_LENGTH);
		} else {
			char hexOutput[(MD5_DIGEST_LENGTH << 1) + 1] = { 0 };
			for (int di = 0; di < MD5_DIGEST_LENGTH; ++di) {
				sprintf(hexOutput + di * 2, "%02x", digest[di]);
			}
			lua_pushstring(tolua_S, (const char *)hexOutput);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'MD5'.",&tolua_err);
	return 0;
#endif
}

static int tolua_extra_Crypto_md5File(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,3,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		const char *path = (const char*)tolua_tostring(tolua_S,2,0);

		Data data = FileUtils::getInstance()->getDataFromFile(path);
		md5_state_t state;
		md5_byte_t digest[MD5_DIGEST_LENGTH];
		char hexOutput[(MD5_DIGEST_LENGTH << 1) + 1] = { 0 };
		md5_init(&state);
		md5_append(&state, data.getBytes(), data.getSize());
		md5_finish(&state, digest);

		for (int di = 0; di < MD5_DIGEST_LENGTH; ++di) {
			sprintf(hexOutput + di * 2, "%02x", digest[di]);
		}
		lua_pushstring(tolua_S, (const char *)hexOutput);
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'MD5File'.",&tolua_err);
	return 0;
#endif
}

/* Open function */
TOLUA_API int register_crypto_module(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	tolua_usertype(tolua_S, "Crypto");
	tolua_module(tolua_S, "cc", 0);
	tolua_beginmodule(tolua_S, "cc");
	tolua_cclass(tolua_S, "Crypto", "Crypto", "", NULL);
	tolua_beginmodule(tolua_S, "Crypto");
	tolua_function(tolua_S, "encryptAES256", tolua_extra_Crypto_encryptAES256);
	tolua_function(tolua_S, "decryptAES256", tolua_extra_Crypto_decryptAES256);
	tolua_function(tolua_S, "encryptXXTEA", tolua_extra_Crypto_encryptXXTEA);
	tolua_function(tolua_S, "decryptXXTEA", tolua_extra_Crypto_decryptXXTEA);
	tolua_function(tolua_S, "encodeBase64", tolua_extra_Crypto_encodeBase64);
	tolua_function(tolua_S, "decodeBase64", tolua_extra_Crypto_decodeBase64);
	tolua_function(tolua_S, "MD5", tolua_extra_Crypto_md5);
	tolua_function(tolua_S, "MD5File", tolua_extra_Crypto_md5File);
	tolua_endmodule(tolua_S);
	tolua_endmodule(tolua_S);
	return 1;
}
