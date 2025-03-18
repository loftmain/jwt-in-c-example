#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "l8w8jwt/encode.h"
#include "l8w8jwt/decode.h"

static const char KEY[] = "pe38eiXCuB0by1K5/l2rlG+ewxiUf2+gPhhc1d2Ki8A=";

// base64 디코딩을 위한 함수
size_t base64_decode(const char* input, unsigned char** output) {
    static const unsigned char table[256] = {
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
        64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
        64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
    };
    
    size_t len = strlen(input);
    if (len % 4 != 0) return 0;
    
    size_t padding = 0;
    if (len > 0) {
        if (input[len - 1] == '=') padding++;
        if (len > 1 && input[len - 2] == '=') padding++;
    }
    
    size_t output_len = (len / 4) * 3 - padding;
    *output = (unsigned char*)malloc(output_len + 1);
    if (!*output) return 0;
    
    size_t i, j = 0;
    uint32_t accumulator;
    for (i = 0; i < len; i += 4) {
        accumulator = (table[(unsigned char)input[i]] << 18) |
                     (table[(unsigned char)input[i + 1]] << 12) |
                     (table[(unsigned char)input[i + 2]] << 6) |
                     (table[(unsigned char)input[i + 3]]);
        
        (*output)[j++] = (accumulator >> 16) & 0xFF;
        if (j < output_len) (*output)[j++] = (accumulator >> 8) & 0xFF;
        if (j < output_len) (*output)[j++] = accumulator & 0xFF;
    }
    
    (*output)[output_len] = '\0';
    return output_len;
}

void decoding(const char* jwt) {
    
    // base64 디코딩
    unsigned char* decoded_key = NULL;
    size_t decoded_key_length = base64_decode(KEY, &decoded_key);
    
    struct l8w8jwt_decoding_params params;
    l8w8jwt_decoding_params_init(&params);

    params.alg = L8W8JWT_ALG_HS256;

    params.jwt = (char*)jwt;
    params.jwt_length = strlen(jwt);

    params.verification_key = decoded_key;
    params.verification_key_length = decoded_key_length;

    params.validate_sub = "itops01";

    /* Expiration validation set to false here only because the above example token is already expired! */
    params.validate_exp = 1; 
    params.exp_tolerance_seconds = 60;

    params.validate_iat = 1;
    params.iat_tolerance_seconds = 60;

    enum l8w8jwt_validation_result validation_result;

    int decode_result = l8w8jwt_decode(&params, &validation_result, NULL, NULL);

    if (decode_result == L8W8JWT_SUCCESS && validation_result == L8W8JWT_VALID) 
    {
        printf("\n Example HS256 token validation successful! \n");
    }
    else
    {
        printf("\n Example HS256 token validation failed! \n");
    }
    
    if (validation_result == L8W8JWT_EXP_FAILURE) {
        printf("Token expired!\n");
    }
    
    // 메모리 해제
    free(decoded_key);
}

void encoding(void) {
    char* jwt;
    size_t jwt_length;

    struct l8w8jwt_encoding_params params;
    l8w8jwt_encoding_params_init(&params);

    params.alg = L8W8JWT_ALG_HS256;

    params.sub = "itops01";
    //params.iss = "Black Mesa";
    //params.aud = "Administrator";

    params.iat = l8w8jwt_time(NULL);
    params.exp = l8w8jwt_time(NULL) + 120; /* Set to expire after 10 minutes (600 seconds). */


    // base64 디코딩
    unsigned char* secret_key = NULL;
    size_t secret_key_length = base64_decode(KEY, &secret_key);

    params.secret_key = secret_key;
    params.secret_key_length = secret_key_length;

    params.out = &jwt;
    params.out_length = &jwt_length;

    int r = l8w8jwt_encode(&params);

    printf("\n l8w8jwt example HS256 token: %s \n", r == L8W8JWT_SUCCESS ? jwt : " (encoding failure) ");

    /* Always free the output jwt string and the decoded key! */
    l8w8jwt_free(jwt);
    free(secret_key);
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        printf("Decoding JWT from command-line argument ...\n");
        decoding(argv[1]);
    } else {
        printf("No JWT provided as argument. Running default encoding and decoding...\n");
        encoding();
    }
    return 0;
}