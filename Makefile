make: all
default: all
.PHONY: luadoc

prepare:
	mkdir -p luadoc

clean:
	rm -f *.so
	rm -f *.o
	rm -f *.dll

all: prepare
	gcc -fPIC *.c 
	gcc -shared -Wl,-soname,libludis86.so.1 \
			    -o libludis86.so.1.0.1 *.o -lc

# DOC
doc: luadoc
ldoc: luadoc
luadoc: prepare
	ldoc.lua ${PWD}
	cp resources/lua-logo-ludis86.png luadoc

