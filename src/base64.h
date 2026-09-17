#ifndef BASE_64_H_
#define BASE_64_H_

#include <stdint.h>
#include <stdbool.h>

uint32_t BASE64_Encode(uint8_t * input_buffer,
        uint32_t input_len,
        uint8_t * output_buffer);

uint32_t BASE64_Decode(uint8_t * input_buffer,
        uint32_t input_len,
        uint8_t * output_buffer);

#endif /* BASE_64_H_ */
