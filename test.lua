local ludis86 = require("ludis86")

-- some binary data
local buf = string.char(
		0x90, -- nop
		0x55, -- push ebp
		0x41, -- inc ecx
		0x5d, -- pop ebp
		0xc3	-- ret
)

--ud = ludis86.init_file_intel32("ludis86_C.so")
--while ud:dis() > 0 do
--	print(string.format("+%04X  %-16s  %-032s", ud:off(), ud:hex(), ud:asm()))
--end

local ud = ludis86.init_buf_intel32(buf)
while ud:dis() > 0 do
	print(string.format("+%04X  %-16s  %-032s", ud:off(), ud:hex(), ud:asm()))
end

ud = ludis86.init_buf_intel32(buf)
ud:dis(); assert(ud:asm():match("nop"))
ud:dis(); assert(ud:asm() == "push ebp")
ud:dis(); assert(ud:asm() == "inc ecx")
ud:dis(); assert(ud:asm() == "pop ebp")
ud:dis(); assert(ud:asm():match("ret"))


