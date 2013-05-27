make: all
default: all
.PHONY: luadoc

all: lib doc

prepare:
	mkdir -p luadoc

clean:
	rm -rf *.so
	rm -rf *.o
	rm -rf *.dll
	rm -rf luadoc

lib: prepare
	gcc -l udis86 -shared -fPIC ludis86.c -o ludis86_C.so

test: lib
	lua -e 'ludis86 = require("ludis86"); ludis86.test();'

run: lib
	lua -e 'ludis86 = require("ludis86"); print("### entered ludis86 interactive mode ###")' -i

# DOC
doc: luadoc
ldoc: luadoc
luadoc: prepare
	ldoc.lua ${PWD}
	cp resources/lua-logo-ludis86.png luadoc

