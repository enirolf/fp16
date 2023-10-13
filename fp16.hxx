#ifndef FP16_HXX
#define FP16_HXX

#include <cstdint>

std::uint16_t fp32_to_fp16(std::uint32_t fp32bits);
std::uint32_t fp16_to_fp32(std::uint16_t fp16bits);

void print_fp32(std::uint32_t fp32bits);
void print_fp16(std::uint16_t fp16bits);

#endif // FP16_HXX
