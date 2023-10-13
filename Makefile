CXX:=g++
CXXFLAGS:=-std=c++17 -Wall -Wshift-count-overflow -O0 -g -fno-omit-frame-pointer

objects := fp16.o
executables := float2half half2float

all: $(executables)

float2half: float2half.cxx $(objects)
	$(CXX) $(CXXFLAGS) $^ -o $@

half2float: half2float.cxx $(objects)
	$(CXX) $(CXXFLAGS) $^ -o $@

fp16.o: fp16.cxx fp16.hxx
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf $(objects) $(executables)
