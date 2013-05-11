make: all
default: all
.PHONY: luadoc

clean:
	rm -f *.so
	rm -f *.o
	rm -f *.dll

all:
	gcc -fPIC *.c 
	gcc -shared -Wl,-soname,libludis86.so.1 \
			    -o libludis86.so.1.0.1 *.o -lc

# DOC
doc: luadoc
ldoc: luadoc
luadoc:
	ldoc.lua ${PWD}
	cp resources/lua-logo-ludis86.png luadoc

