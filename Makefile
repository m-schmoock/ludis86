make: all
default: all
.PHONY: luadoc


# DOC
doc: luadoc
ldoc: luadoc
luadoc:
	ldoc.lua ${PWD}

