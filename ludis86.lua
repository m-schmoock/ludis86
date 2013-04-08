--- this module is a libudis86 C API binding 
--
-- https://code.google.com/p/ludis86/
-- http://udis86.sourceforge.net/
--
-- http://duschkumpane.org/index.php/ludis86
--
--EXAMPLEs
--    ud = ludis86.init_addr_intel32(0x401000)
--    ud:dis()
--    ud:asm()
--
-- @module utils.ludis86
module("ludis86", package.seeall);
require("ludis86_C");

--- initializes a dissasembler to an address using intel32 syntax
-- @param addr the address to disassemble. can be userdata cdata or number
-- @param len OPTIONAL the maximum number of bytes to read
function init_addr_intel32(addr, len)
	if not len then len = 2^31 end 
	local ud = ludis86_C.ud_init();
	ud:ud_set_input_buffer(touserdata(addr), len);
	ud:ud_set_pc(ptrtonumber(addr));
	ud:ud_set_mode(32);
	ud:ud_set_syntax(ud.UD_SYN_INTEL);
	
	return ud;
end
