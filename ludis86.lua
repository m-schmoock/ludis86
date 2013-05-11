---[Udis86](http://udis86.sourceforge.net) C disassembler bindings for Lua.
-- "Udis86 is an easy-to-use, minimalistic disassembler library (libudis86) 
--  for the x86 class of instruction set architectures."
--
-- This bindings were former part of Lua code injection framework: 
-- [mmBBQ](http://duschkumpane.org/index.php/mmbbq)
--
-- The GitHub project site is: [https://github.com/willsteel/ludis86](https://github.com/willsteel/ludis86)
--
--### Overview
-- The project contains a standard Makefile that is used to build 
-- shared Lua libraries for Windows and Linux. The contained C code part
-- of the bindings can as well be integrated or hard-linked into a Lua projekt.
--
--### QuickUsage
--	-- initialize and get the first disassembled instruction as string
--	local ludis86 = require("ludis86")
--	ud = ludis86.init_addr_intel32(0x401000)
--	ud:dis()
--	ud:asm()
--	
--	-- disassemble and print 10 instructions
--	for i = 1, 10 do
--		print(string.format("+%04X %016s %016s", ud:off(), ud:hex(), ud:asm()))
--	end
--    
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
--	{ "ud_set_user_opaque_data", ud_set_user_opaque_data_C },
--	{ "ud_get_user_opaque_data", ud_get_user_opaque_data_C },
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
-- @module ludis86
module("ludis86", package.seeall);

local ludis86_C = require("ludis86_C");
local ludis86 = {}

--- initializes the dissasembler to an address using intel syntax and 32bit.
-- @param addr the address to disassemble. can be userdata cdata or number
-- @param len OPTIONAL the maximum number of bytes to read
ludis86.init_addr_intel32 = function(addr, len)
	if not len then len = 2^31 end 
	local ud = ludis86_C.ud_init();
	ud:ud_set_input_buffer(touserdata(addr), len);
	ud:ud_set_pc(ptrtonumber(addr));
	ud:ud_set_mode(32);
	ud:ud_set_syntax(ud.UD_SYN_INTEL);
	return ud;
end

--- initializes the dissasembler to an address using intel syntax and 64bit.
-- @param addr the address to disassemble. can be userdata cdata or number
-- @param len OPTIONAL the maximum number of bytes to read
ludis86.init_addr_intel64 = function(addr, len)
	if not len then len = 2^31 end 
	local ud = ludis86_C.ud_init();
	ud:ud_set_input_buffer(touserdata(addr), len);
	ud:ud_set_pc(ptrtonumber(addr));
	ud:ud_set_mode(64);
	ud:ud_set_syntax(ud.UD_SYN_INTEL);
	return ud;
end

return ludis86
