CXX:=g++
CXXFLAGS:=-std=c++17 -Wall -O0 -g -fno-omit-frame-pointer

objects := fp16
all: $(objects)

%: %.cxx
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(objects)
