make: all
default: all
.PHONY: luadoc

prepare:
	mkdir -p luadoc

clean:
	rm -rf *.so
	rm -rf *.o
	rm -rf *.dll
	rm -rf luadoc

lib:
	gcc -l udis86 -shared -fPIC ludis86.c -o ludis86_C.so

test: lib
	lua test.lua

all: prepare lib doc

# DOC
doc: luadoc
ldoc: luadoc
luadoc: prepare
	ldoc.lua ${PWD}
	cp resources/lua-logo-ludis86.png luadoc

