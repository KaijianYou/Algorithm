#ifndef ALGORITHM_BASE64_H
#define ALGORITHM_BASE64_H

#include <string>


namespace myalgorithm {
    char base64Alphabet[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // Base64 加密
    char* base64Encode(char *plainText)
    {
        size_t len = strlen(plainText);
        size_t part = (len + 2) / 3;
        char *cipherText = new char[part * 4 + 1];
        char in[3];
        for (int i = 0; i < part; i++) {
            in[0] = plainText[i * 3];
            in[1] = plainText[i * 3 + 1];
            in[2] = plainText[i * 3 + 2];
            size_t add = len - 3 * i;

            cipherText[i * 4] = base64Alphabet[in[0] >> 2];
            cipherText[i * 4 + 1] = base64Alphabet[((in[0] & 0x3) << 4) | ((in[1] & 0xf0) >> 4)];
            cipherText[i * 4 + 2] =  add > 1 ? base64Alphabet[(((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6))] : '=';
            cipherText[i * 4 + 3] = add > 2 ? base64Alphabet[(in[2] & 0x3f)] : '=';
        }
        cipherText[part * 4] = '\0';

        return cipherText;
    }

    // Base64 解密
    char* base64Decode(char *cipherText)
    {

    }
}

#endif  // ALGORITHM_BASE64_H