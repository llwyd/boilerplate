#include "base64.h"
#include "assert_bp.h"

#define BASE64_ENC_MASK ( ( 1<<6 ) - 1)
#define BASE64_DEC_MASK (0xFF)

uint8_t encode_lut[65] =
{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','-','_','='};

uint8_t decode_lut[256] =
{
    ['A'] = 0,
    ['B'] = 1,
    ['C'] = 2,
    ['D'] = 3,
    ['E'] = 4,
    ['F'] = 5,
    ['G'] = 6,
    ['H'] = 7,
    ['I'] = 8,
    ['J'] = 9,
    ['K'] = 10,
    ['L'] = 11,
    ['M'] = 12,
    ['N'] = 13,
    ['O'] = 14,
    ['P'] = 15,
    ['Q'] = 16,
    ['R'] = 17,
    ['S'] = 18,
    ['T'] = 19,
    ['U'] = 20,
    ['V'] = 21,
    ['W'] = 22,
    ['X'] = 23,
    ['Y'] = 24,
    ['Z'] = 25,
    ['a'] = 26,
    ['b'] = 27,
    ['c'] = 28,
    ['d'] = 29,
    ['e'] = 30,
    ['f'] = 31,
    ['g'] = 32,
    ['h'] = 33,
    ['i'] = 34,
    ['j'] = 35,
    ['k'] = 36,
    ['l'] = 37,
    ['m'] = 38,
    ['n'] = 39,
    ['o'] = 40,
    ['p'] = 41,
    ['q'] = 42,
    ['r'] = 43,
    ['s'] = 44,
    ['t'] = 45,
    ['u'] = 46,
    ['v'] = 47,
    ['w'] = 48,
    ['x'] = 49,
    ['y'] = 50,
    ['z'] = 51,
    ['0'] = 52,
    ['1'] = 53,
    ['2'] = 54,
    ['3'] = 55,
    ['4'] = 56,
    ['5'] = 57,
    ['6'] = 58,
    ['7'] = 59,
    ['8'] = 60,
    ['9'] = 61,
    ['-'] = 62,
    ['_'] = 63,
    ['='] = 64,
};


uint32_t BASE64_Encode(uint8_t * input_buffer,
        uint32_t input_len,
        uint8_t * output_buffer)
{
    ASSERT(input_buffer);
    ASSERT(output_buffer);
    uint32_t out_len = 0;
    
    uint32_t jdx = 0;
    for(uint32_t idx = 0u; idx < input_len; idx+=3)
    {
        uint32_t word = 0u;
        uint32_t kdx = 0;
        for(; (kdx < 3u) && (jdx < input_len);kdx++,jdx++)
        {
            uint32_t shift = 16u - (kdx * 8u);
            word |= (input_buffer[jdx] << shift);
        }
        
        uint8_t out[4];
        out[0] = (word >> 18) & BASE64_ENC_MASK;
        out[1] = (word >> 12) & BASE64_ENC_MASK;

        /* Add padding if necessary */
        out[2] = (kdx > 1) ? (word >> 6) & BASE64_ENC_MASK : 64;
        out[3] = (kdx > 2) ? word & BASE64_ENC_MASK: 64;

        for(uint32_t ndx = 0; ndx < 4; ndx++)
        {
            output_buffer[out_len++] = encode_lut[out[ndx]];
        }
    }
    ASSERT((out_len%4) == 0);
    return out_len;
}

uint32_t BASE64_Decode(uint8_t * input_buffer,
        uint32_t input_len,
        uint8_t * output_buffer)
{
    ASSERT(input_buffer);
    ASSERT(output_buffer);
    ASSERT((input_len%4) == 0);
    uint32_t out_len = 0;
    uint32_t jdx = 0;
    for(uint32_t idx = 0u; idx < input_len; idx+=4)
    {
        uint32_t word = 0u;
        uint32_t kdx = 0;
        for(; (kdx < 4u) && (jdx < input_len);jdx++)
        {
            uint32_t shift = 18u - (kdx * 6u);
            uint8_t bits = decode_lut[input_buffer[jdx]];
            word |= bits << shift;
            if(bits < decode_lut['='])
            {
                kdx++;
            }
        }
        uint8_t out[3];
        out[0] = (word >> 16) & BASE64_DEC_MASK;
        out[1] = (word >>  8) & BASE64_DEC_MASK;
        out[2] = (word >>  0) & BASE64_DEC_MASK;

        for(uint32_t ndx = 0; ndx < (kdx - 1); ndx++)
        {
            output_buffer[out_len++] = out[ndx];
        }
    }
    return out_len;
}
