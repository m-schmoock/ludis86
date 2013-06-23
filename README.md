<p align="center"><a href="http://lua.org"><img src="http://ludis86.schmoock.net/lua-logo-ludis86.png"></a></p>
===

## ludis86

libudis86 Lua bindings. Compatible with Lua 5.1, 5.2 and LuaJIT. It was developed as a part of the mmbbq project, the Lua code injection framework.

 * github page:    https://github.com/willsteel/ludis86
 * udis86 project: http://udis86.sourceforge.net
 * project page:   http://ludis86.schmoock.net
 * mmbbq page:     http://duschkumpane.org/index.php/mmbbq

We use same license as udis86: FreeBSD


===

### Makefile targets
    make all
        # Build lib and doc
    
    make doc
        # Just build the docs
    
    make test
        # run 'test.lua'

### Usage
    -- init udis to a specific address
    local ludis86 = require("ludis86")
    ud = ludis86.init_addr_intel32(0x401000) -- your address here :D	
    -- disassemble and print instructions
    while ud:dis() > 0 do
        print(string.format("+%04X %016s %016s", ud:off(), ud:hex(), ud:asm()))
    end
  
