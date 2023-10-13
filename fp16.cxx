#include <bitset>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <iostream>

// Takes and returns the *bits* of the floating point number
std::uint16_t fp32_to_fp16(std::uint32_t fp32bits) {
  std::uint32_t sign32 = fp32bits >> 0x0000001f;
  std::uint32_t exponent32 = (fp32bits << 0x00000001) >> 0x00000018;
  std::uint32_t mantissa32 = (fp32bits << 0x00000009) >> 0x00000009;

  std::uint16_t sign16 = sign32;
  std::uint16_t exponent16 = exponent32 >> 0x00000003;
  std::uint16_t mantissa16 = mantissa32 >> 0x0000000d;

  // exp >= 31 ==> infinity
  if (exponent16 & 0x0000001f) {
    mantissa16 = 0x0;
  } else {
    // round the mantissa to the nearest even
    std::uint16_t rest_mantissa = mantissa32 & 0x1fff;
    if (rest_mantissa & 0x1000) {
      if (rest_mantissa & 0X0fff || mantissa16 & 0x1) {
        mantissa16 |= 0x1;
      }
    }
  }

  std::uint16_t fp16bits = (sign16 << 15) | (exponent16 << 10) | (mantissa16);
  return fp16bits;
}

void print_fp32(std::uint32_t fp32bits) {
  std::bitset<1> sign32bitset = fp32bits >> 0x0000001f;
  std::bitset<8> exponent32bitset = fp32bits >> 0x00000017;
  std::bitset<23> mantissa32bitset = fp32bits;

  std::cout << "32-bit: " << sign32bitset << " " << exponent32bitset << " "
            << mantissa32bitset << std::endl;
}

void print_fp16(std::uint16_t fp16bits) {
  std::bitset<1> sign16bitset = fp16bits >> 0x0000000f;
  std::bitset<5> exponent16bitset = fp16bits >> 0x0000000a;
  std::bitset<10> mantissa16bitset = fp16bits;

  std::cout << "16-bit: " << sign16bitset << " " << exponent16bitset << "    "
            << mantissa16bitset << std::endl;
}

void convert_and_print_result(float fp32) {
  std::cout << "Input: " << fp32 << std::endl;

  std::uint32_t fp32bits = *reinterpret_cast<std::uint32_t *>(&fp32);
  std::uint16_t fp16bits = fp32_to_fp16(fp32bits);

  print_fp32(fp32bits);
  print_fp16(fp16bits);
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cout << "======= MAX ========" << std::endl;
    convert_and_print_result(std::numeric_limits<float>::max());
    std::cout << "======= MIN ========" << std::endl;
    convert_and_print_result(std::numeric_limits<float>::min());
    std::cout << "======= -MAX =======" << std::endl;
    convert_and_print_result(std::numeric_limits<float>::lowest());
    std::cout << "====== DENORM ======" << std::endl;
    convert_and_print_result(std::numeric_limits<float>::denorm_min());
    std::cout << "======= INF ========" << std::endl;
    convert_and_print_result(std::numeric_limits<float>::infinity());
  } else {
    convert_and_print_result(std::atof(argv[1]));
  }

  return 0;
}
