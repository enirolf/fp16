#include "fp16.hxx"

#include <cstdlib>
#include <iostream>
#include <limits>

static void convert_and_print_result(std::uint32_t fp16bits) {
  std::uint64_t fp32bits = fp16_to_fp32(fp16bits);
  float fp32 = *reinterpret_cast<float *>(&fp32bits);

  print_fp32(fp32bits);
  print_fp16(fp16bits);


  std::cout << "Result: " << fp32 << std::endl;
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    convert_and_print_result(49736); // -3.14
  } else {
    convert_and_print_result(static_cast<std::uint16_t>(std::atoi(argv[1])));
  }

  return 0;
}
