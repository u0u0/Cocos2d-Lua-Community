--[[
  encrypt, decrypt, hash
]]--

local crypto = {}


--[[
  use AES256 to encrypt buffer
  @function encryptAES256
  @param string plaintext
  @param string key
  @return string ret
]]--
function crypto.encryptAES256(plaintext, key)
    plaintext = tostring(plaintext)
    key = tostring(key)
    return cc.Crypto:encryptAES256(plaintext, string.len(plaintext), key, string.len(key))
end

--[[
  use AES256 to decrypt buffer
  @function decryptAES256
  @param string ciphertext
  @param string key
  @return string ret
]]--
function crypto.decryptAES256(ciphertext, key)
    ciphertext = tostring(ciphertext)
    key = tostring(key)
    return cc.Crypto:decryptAES256(ciphertext, string.len(ciphertext), key, string.len(key))
end

--[[
  use XXTEA to encrypt buffer
  @function encryptXXTEA
  @param string plaintext
  @param string key
  @return string ret
]]--
function crypto.encryptXXTEA(plaintext, key)
    plaintext = tostring(plaintext)
    key = tostring(key)
    return cc.Crypto:encryptXXTEA(plaintext, string.len(plaintext), key, string.len(key))
end

--[[
  use XXTEA to decrypt buffer
  @function decryptXXTEA
  @param string ciphertext
  @param string key
  @return string ret
]]--
function crypto.decryptXXTEA(ciphertext, key)
    ciphertext = tostring(ciphertext)
    key = tostring(key)
    return cc.Crypto:decryptXXTEA(ciphertext, string.len(ciphertext), key, string.len(key))
end

--[[
  use Base64 to encode buffer
  @function encodeBase64
  @param string plaintext
  @return string ret
]]--
function crypto.encodeBase64(plaintext)
    plaintext = tostring(plaintext)
    return cc.Crypto:encodeBase64(plaintext, string.len(plaintext))
end

--[[
  use Base64 to decode buffer
  @function decodeBase64
  @param string ciphertext
  @return string ret
]]--
function crypto.decodeBase64(ciphertext)
    ciphertext = tostring(ciphertext)
    return cc.Crypto:decodeBase64(ciphertext)
end

--[[
  use md5 to hash buffer
  @function md5
  @param string input
  @param boolean isRawOutput, true retuen binary buffer, false return HEX string
  @return string ret
]]--
function crypto.md5(input, isRawOutput)
    input = tostring(input)
    if type(isRawOutput) ~= "boolean" then isRawOutput = false end
    return cc.Crypto:MD5(input, isRawOutput)
end

--[[
  use md5 to hash file
  @function md5file
  @param string path
  @return string ret
]]--
function crypto.md5file(path)
    if not path then
        printError("crypto.md5file() - invalid filename")
        return nil
    end
    path = tostring(path)
    if DEBUG > 1 then
        printInfo("crypto.md5file() - filename: %s", path)
    end
    return cc.Crypto:MD5File(path)
end

return crypto
