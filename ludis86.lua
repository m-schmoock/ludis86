---[Udis86](http://udis86.sourceforge.net) C disassembler bindings for Lua.
--"Udis86 is an easy-to-use, minimalistic disassembler library (libudis86) for the x86 class of instruction set architectures."
--This bindings were former part of Lua code injection framework: 
--[mmBBQ](http://duschkumpane.org/index.php/mmbbq)
--
--## Overview
-- The project contains a standard Makefile that is used to build 
-- shared Lua libraries for Windows and Linux. The contained C code part
-- of the bindings can as well be integrated or hard-linked into a Lua projekt
--### Source
--The GitHub project site is: [here](https://github.com/willsteel/ludis86)
--	git clone https://github.com/willsteel/ludis86.git
--
--### Makefile targets
--	make all
--		# Build lib and doc
--
--	make doc
--		# Just build the docs
--
--	make test
--		# run 'test.lua'
--
--### Usage
--	-- initialize and get the first disassembled instruction as string
--	local ludis86 = require("ludis86")
--	ud = ludis86.init_addr_intel32(0x401000)
--	ud:dis()
--	ud:asm()
--	
--	-- disassemble and print instructions
--	while ud:dis() > 0 do
--		print(string.format("+%04X %016s %016s", ud:off(), ud:hex(), ud:asm()))
--	end
--
--### Notice
-- 2013 (c) by Michael Schmoock <michael@schmoock.net>
-- License: Free-BSD
--
--### C-Function API mapping
--	// Following code is taken from the file: ludis86.c
--	// API mapping
--	{ "ud_init", ud_init_C },
--	{ "ud_set_mode", ud_set_mode_C },
--	{ "ud_set_pc", ud_set_pc_C },
--	{ "ud_set_input_hook", ud_set_input_hook_C },
--	{ "ud_set_input_buffer", ud_set_input_buffer_C },
--	{ "ud_set_input_file", ud_set_input_file_C },
--	{ "ud_set_vendor", ud_set_vendor_C },
--	{ "ud_set_syntax", ud_set_syntax_C },
--	{ "ud_input_skip", ud_input_skip_C },
--	{ "ud_input_end", ud_input_end_C },
--	{ "ud_decode", ud_decode_C },
--	{ "ud_disassemble", ud_disassemble_C },
--	{ "ud_translate_intel", ud_translate_intel_C },
--	{ "ud_translate_att", ud_translate_att_C },
--	{ "ud_insn_asm", ud_insn_asm_C },
--	{ "ud_insn_ptr", ud_insn_ptr_C },
--	{ "ud_insn_off", ud_insn_off_C },
--	{ "ud_insn_hex", ud_insn_hex_C },
--	{ "ud_insn_len", ud_insn_len_C },
--	{ "ud_lookup_mnemonic", ud_lookup_mnemonic_C },
--
--	// shorthandles
--	{ "new",  ud_init },
--	{ "dis",  ud_disassemble_C },
--	{ "asm",  ud_insn_asm_C },
--	{ "off",  ud_insn_off_C },
--	{ "hex",  ud_insn_hex_C },
--	{ "skip", ud_input_skip_C },
--	{ "len",  ud_insn_len_C },
--	{ "ptr",  ud_insn_ptr_C },
--	{ "pc",   ud_set_pc_C },
--
--
-- @module ludis86
local ludis86 = require("ludis86_C");
--local ludis86 = package.loadlib("ludis86", "luaopen_ludis86_C")();

--- initialiszes the disassembler to a file using intel syntax and 32bit.
-- @param filename the path to an assembly file
-- @param offset OPTIONAL the offset where to start disassembly
-- @param len OPTIONAL the number if bytes to disassemlbe
-- @param pc OPTIONAL the programm counter to use
ludis86.init_file_intel32 = function(filename, offset, len, pc)
		local file = io.open(filename, "r")
		local buf = file:read("*a")
		file:close();
		if offset then buf=buf:sub(offset) end
		return ludis86.init_buf_intel32(buf, len, pc);
end
--- initialiszes the disassembler to a file using intel syntax and 64bit.
-- @param filename the path to an assembly file
-- @param offset OPTIONAL the offset where to start disassembly
-- @param len OPTIONAL the number if bytes to disassemlbe
-- @param pc OPTIONAL the programm counter to use
ludis86.init_file_intel64 = function(filename, offset, len, pc)
		local file = io.open(filename, "r")
		local buf = file:read("*a")
		file:close();
		if offset then buf=buf:sub(offset) end
		return ludis86.init_buf_intel64(buf, len, pc);
end

--- sets syntax to intel 32bit
-- @param ud initialized udis86 object
ludis86.intel32 = function(ud)
	ud:ud_set_mode(32);
	ud:ud_set_syntax(ud.UD_SYN_INTEL);
end

--- sets syntax to intel 64bit
-- @param ud initialized udis86 object
ludis86.intel64 = function(ud)
	ud:ud_set_mode(64);
	ud:ud_set_syntax(ud.UD_SYN_INTEL);
end

--- initializes the disassembler to a string buffer using intel syntax and 32bit.
-- @param buf the string buffer
-- @param len OPTIONAL the length to use. max and default: #buf
-- @param pc OPTIONAL the programm counter to use
ludis86.init_buf_intel32 = function(buf, len, pc)
	if not len then len = #buf end 
	local ud = ludis86.ud_init()
	ludis86.intel32(ud)
	ud:ud_set_input_buffer(buf, len)
	ud:ud_set_pc(pc or 0)
	return ud
end

--- initializes the disassembler to a string buffer using intel syntax and 64bit.
-- @param buf the string buffer
-- @param len OPTIONAL the length to use. max and default: #buf
-- @param pc OPTIONAL the programm counter to use
ludis86.init_buf_intel64 = function(buf, len, pc)
	if not len then len = #buf end 
	local ud = ludis86.ud_init()
	ludis86.intel64(ud)
	ud:ud_set_input_buffer(buf, len)
	ud:ud_set_pc(pc or 0)
	return ud
end

--- initializes the disassembler to an address using intel syntax and 32bit.
-- @param addr the address to disassemble. can be userdata cdata or number
-- @param len OPTIONAL the maximum number of bytes to read
ludis86.init_addr_intel32 = function(addr, len)
	if not len then len = 2^31 end 
	local ud = ludis86.ud_init()
	ludis86.intel32(ud)
	ud:ud_set_input_buffer(addr, len)
	ud:ud_set_pc(addr)
	return ud
end

--- initializes the disassembler to an address using intel syntax and 64bit.
-- @param addr the address to disassemble. can be userdata cdata or number
-- @param len OPTIONAL the maximum number of bytes to read
ludis86.init_addr_intel64 = function(addr, len)
	if not len then len = 2^31 end 
	local ud = ludis86.ud_init()
	ludis86.intel64(ud)
	ud:ud_set_input_buffer(addr, len)
	ud:ud_set_pc(addr)
	return ud;
end

return ludis86
