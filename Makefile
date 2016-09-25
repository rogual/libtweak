prefix=/usr/local

build/test: test.cc build/libtweak.a
	mkdir -p build
	c++ -std=c++11 -o $@ $^

build/%.o: src/%.cc
	mkdir -p build
	c++ -std=c++11 -c -o $@ $^

build/libtweak.a: build/sys_posix.o build/tweak.o build/util.o build/types.o
	libtool -static -o $@ $^

clean:
	rm -rf build

install:
	install bin/* ${prefix}/bin
	install include/* ${prefix}/include
	install build/libtweak.a ${prefix}/lib

.PHONY: clean install
