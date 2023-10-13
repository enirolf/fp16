#include <bitset>
#include <iostream>

#include "fp16.hxx"

// Takes and returns the *bits* of the floating point number
std::uint16_t fp32_to_fp16(std::uint32_t fp32bits) {
  std::uint32_t sign32 = fp32bits >> 0x001f;
  std::uint32_t exponent32 = (fp32bits << 0x0001) >> 0x0018;
  std::uint32_t mantissa32 = (fp32bits << 0x0009) >> 0x0009;

  std::uint16_t sign16 = sign32;
  std::uint16_t exponent16 = exponent32 >> 0x0003;
  std::uint16_t mantissa16 = mantissa32 >> 0x000d;
  std::uint16_t rest_mantissa = mantissa32 & 0x1fff;

  if ((exponent32 == 0x00ff) && mantissa32) {
    // exp32 == 255 & mantissa32 > 1 ==> NaN
    mantissa16 = 0x0200;
  } else if (exponent16 == 0x001f) {
    // exp16 >= 31 ==> infinity
    mantissa16 = 0x0000;
  } else {
    // round mantissa16 to the nearest even
    if (rest_mantissa & 0x1000) {
      if (rest_mantissa & 0x0fff || mantissa16 & 0x0001) {
        mantissa16 |= 0x0001;
      }
    }
  }

  return (sign16 << 0x000f) | (exponent16 << 0x000a) | (mantissa16);
}

// Takes and returns the *bits* of the floating point number
std::uint32_t fp16_to_fp32(std::uint16_t fp16bits) {
  std::uint16_t sign16 = fp16bits >> 0x000f;
  std::uint16_t exponent16 = static_cast<uint16_t>(fp16bits << 0x0001) >> 0x000b;
  std::uint16_t mantissa16 = static_cast<uint16_t>(fp16bits << 0x0006) >> 0x0006;

  return (sign16 << 0x001f) | (exponent16 << 0x001a) | (mantissa16 << 0x0d);
}

void print_fp32(std::uint32_t fp32bits) {
  std::bitset<1> sign32bitset = fp32bits >> 0x001f;
  std::bitset<8> exponent32bitset = fp32bits >> 0x0017;
  std::bitset<23> mantissa32bitset = fp32bits;

  std::cout << "32-bit: " << sign32bitset << " " << exponent32bitset << " "
            << mantissa32bitset << std::endl;
}

void print_fp16(std::uint16_t fp16bits) {
  std::bitset<1> sign16bitset = fp16bits >> 0x000f;
  std::bitset<5> exponent16bitset = fp16bits >> 0x000a;
  std::bitset<10> mantissa16bitset = fp16bits;

  std::cout << "16-bit: " << sign16bitset << " " << exponent16bitset << "    "
            << mantissa16bitset << std::endl;
}
