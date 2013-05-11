make: all
default: all
.PHONY: luadoc


# DOC
doc: luadoc
ldoc: luadoc
luadoc:
	ldoc.lua ${PWD}
	cp resources/lua-logo-ludis86.png luadoc

