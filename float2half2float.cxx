#include "fp16.hxx"

#include <cstdlib>
#include <iostream>
#include <limits>

static void convert_and_print_result(float fp32) {
  std::cout << "Input: " << fp32 << std::endl;

  std::uint32_t fp32bits = *reinterpret_cast<std::uint32_t *>(&fp32);
  std::uint16_t fp16bits = fp32_to_fp16(fp32bits);

  print_fp32(fp32bits);
  print_fp16(fp16bits);

  std::uint64_t fp32bits_converted = fp16_to_fp32(fp16bits);
  float fp32_converted = *reinterpret_cast<float *>(&fp32bits_converted);

  std::cout << "Result: " << fp32_converted << std::endl;

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
    std::cout << "======= NaN ========" << std::endl;
    convert_and_print_result(std::numeric_limits<float>::signaling_NaN());
    std::cout << "--------------------" << std::endl;
    convert_and_print_result(std::numeric_limits<float>::quiet_NaN());
  } else {
    convert_and_print_result(std::atof(argv[1]));
  }

  return 0;
}
