/*
 * libudis86 Lua bindings
 */
#include <udis86.h>
#include "ludis86.h"

#define LUBUDIS_REG "ludis86_C"

static const luaL_reg ludis86_C[];
static const luaL_reg ludis86_M[];

/*
 * utils
 */
inline void* lua_toptr(lua_State* L, int idx)
{
	int type = lua_type(L, idx);
	switch (type){
		case LUA_TNUMBER:        return (void*)lua_tointeger (L, idx);        break;
		case LUA_TLIGHTUSERDATA: return (void*)lua_touserdata(L, idx);        break;
		case LUA_TUSERDATA:      return (void*)lua_touserdata(L, idx);        break;
		case LUA_TSTRING:        return (void*)lua_tostring  (L, idx);        break;
		case 10:                 return (void*)lua_topointer (L, idx);        break;
		default:                 return (void*)lua_topointer (L, idx);        break;
	}
}

/*
 * definitions from libudis86 extern.h
 */

// extern void ud_init(struct ud*);
int LUA_API ud_init_C(lua_State *L)
{
	ud_t* ud = lua_newuserdata(L, sizeof(ud_t));
	ud_init(ud);

	// add metatable
	luaL_getmetatable(L, LUBUDIS_REG);
	lua_setmetatable(L, -2);

	return 1;
}

//extern void ud_set_mode(struct ud*, uint8_t);
int LUA_API ud_set_mode_C(lua_State *L)
{
	ud_set_mode(lua_touserdata(L, 1), lua_tointeger(L, 2));
	return 0;
}

//extern void ud_set_pc(struct ud*, uint64_t);
int LUA_API ud_set_pc_C(lua_State *L)
{
	ud_set_pc(lua_touserdata(L, 1), (uint64_t)lua_tonumber(L, 2));
	return 0;
}

//extern void ud_set_input_hook(struct ud*, int (*)(struct ud*));
int LUA_API ud_set_input_hook_C(lua_State *L)
{
	ud_set_input_hook(lua_touserdata(L, 1), lua_toptr(L, 2));
	return 0;
}

//extern void ud_set_input_buffer(struct ud*, uint8_t*, size_t);
int LUA_API ud_set_input_buffer_C(lua_State *L)
{
	ud_set_input_buffer(lua_touserdata(L, 1), lua_toptr(L, 2), lua_tointeger(L, 3));
	return 0;
}

//extern void ud_set_input_file(struct ud*, FILE*);
int LUA_API ud_set_input_file_C(lua_State *L)
{
	ud_set_input_file(lua_touserdata(L, 1), lua_toptr(L, 2));
	return 0;
}

//extern void ud_set_vendor(struct ud*, unsigned);
int LUA_API ud_set_vendor_C(lua_State *L)
{
	ud_set_vendor(lua_touserdata(L, 1), lua_tointeger(L, 2));
	return 0;
}

//extern void ud_set_syntax(struct ud*, void (*)(struct ud*));
int LUA_API ud_set_syntax_C(lua_State *L)
{
	ud_set_syntax(lua_touserdata(L, 1), lua_toptr(L, 2));
	return 0;
}

//extern void ud_input_skip(struct ud*, size_t);
int LUA_API ud_input_skip_C(lua_State *L)
{
	ud_input_skip(lua_touserdata(L, 1), lua_tointeger(L, 2));
	return 0;
}

//extern int ud_input_end(struct ud*);
int LUA_API ud_input_end_C(lua_State *L)
{
	lua_pushinteger(L, ud_input_end(lua_touserdata(L, 1)));
	return 1;
}

//extern unsigned int ud_decode(struct ud*);
int LUA_API ud_decode_C(lua_State *L)
{
	lua_pushinteger(L, ud_decode(lua_touserdata(L, 1)));
	return 1;
}

//extern unsigned int ud_disassemble(struct ud*);
int LUA_API ud_disassemble_C(lua_State *L)
{
	lua_pushinteger(L, ud_disassemble(lua_touserdata(L, 1)));
	return 1;
}

//extern void ud_translate_intel(struct ud*);
int LUA_API ud_translate_intel_C(lua_State *L)
{
	ud_translate_intel(lua_touserdata(L, 1));
	return 0;
}

//extern void ud_translate_att(struct ud*);
int LUA_API ud_translate_att_C(lua_State *L)
{
	ud_translate_att(lua_touserdata(L, 1));
	return 0;
}

//extern char* ud_insn_asm(struct ud* u);
int LUA_API ud_insn_asm_C(lua_State *L)
{
	lua_pushstring(L, ud_insn_asm(lua_touserdata(L, 1)));
	return 1;
}

//extern uint8_t* ud_insn_ptr(struct ud* u);
int LUA_API ud_insn_ptr_C(lua_State *L)
{
	lua_pushlightuserdata(L, ud_insn_ptr(lua_touserdata(L, 1)));
	return 1;
}

//extern uint64_t ud_insn_off(struct ud*);
int LUA_API ud_insn_off_C(lua_State *L)
{
	lua_pushnumber(L, ud_insn_off(lua_touserdata(L, 1)));
	return 1;
}

//extern char* ud_insn_hex(struct ud*);
int LUA_API ud_insn_hex_C(lua_State *L)
{
	lua_pushstring(L, ud_insn_hex(lua_touserdata(L, 1)));
	return 1;
}

//extern unsigned int ud_insn_len(struct ud* u);
int LUA_API ud_insn_len_C(lua_State *L)
{
	lua_pushinteger(L, ud_insn_len(lua_touserdata(L, 1)));
	return 1;
}

//extern const char* ud_lookup_mnemonic(enum ud_mnemonic_code c);
int LUA_API ud_lookup_mnemonic_C(lua_State *L)
{
	lua_pushstring(L, ud_lookup_mnemonic(lua_tointeger(L, 1)));
	return 1;
}

/* MSC: not in any udis version. can cause compile errors
//extern void ud_set_user_opaque_data(struct ud*, void*);
int LUA_API ud_set_user_opaque_data_C(lua_State *L)
{
	ud_set_user_opaque_data(lua_touserdata(L, 1), lua_toptr(L, 2));
	return 0;
}

//extern void *ud_get_user_opaque_data(struct ud*);
int LUA_API ud_get_user_opaque_data_C(lua_State *L)
{
	lua_pushlightuserdata(L, ud_get_user_opaque_data(lua_touserdata(L, 1)));
	return 1;
}
*/

/*
 * register stuff to lua machine
 */
static const luaL_reg ludis86_C[] =
{
	// API mapping
	{ "ud_init", ud_init_C },
	{ "ud_set_mode", ud_set_mode_C },
	{ "ud_set_pc", ud_set_pc_C },
	{ "ud_set_input_hook", ud_set_input_hook_C },
	{ "ud_set_input_buffer", ud_set_input_buffer_C },
	{ "ud_set_input_file", ud_set_input_file_C },
	{ "ud_set_vendor", ud_set_vendor_C },
	{ "ud_set_syntax", ud_set_syntax_C },
	{ "ud_input_skip", ud_input_skip_C },
	{ "ud_input_end", ud_input_end_C },
	{ "ud_decode", ud_decode_C },
	{ "ud_disassemble", ud_disassemble_C },
	{ "ud_translate_intel", ud_translate_intel_C },
	{ "ud_translate_att", ud_translate_att_C },
	{ "ud_insn_asm", ud_insn_asm_C },
	{ "ud_insn_ptr", ud_insn_ptr_C },
	{ "ud_insn_off", ud_insn_off_C },
	{ "ud_insn_hex", ud_insn_hex_C },
	{ "ud_insn_len", ud_insn_len_C },
	{ "ud_lookup_mnemonic", ud_lookup_mnemonic_C },
	//{ "ud_set_user_opaque_data", ud_set_user_opaque_data_C },
	//{ "ud_get_user_opaque_data", ud_get_user_opaque_data_C },

	// shorthandles
	{ "new",  ud_init_C },
	{ "dis",  ud_disassemble_C },
	{ "asm",  ud_insn_asm_C },
	{ "off",  ud_insn_off_C },
	{ "hex",  ud_insn_hex_C },
	{ "skip", ud_input_skip_C },
	{ "len",  ud_insn_len_C },
	{ "ptr",  ud_insn_ptr_C },
	{ "pc",   ud_set_pc_C },

	{0, 0}	/* terminator */
};

static const luaL_reg ludis86_M[] = {
	//{"__gc",       ud_close},
	//{"__tostring", ud_tostring},
	//{"__add",      ud_add},
	{0, 0}	/* terminator */
};

#define LUA_KVE(L, val) \
  lua_pushlstring(L, #val, sizeof(#val)-1); \
  lua_pushnumber(L, val); \
  lua_settable(L, -3);

#define LUA_KVU(L, val) \
  lua_pushlstring(L, #val, sizeof(#val)-1); \
  lua_pushlightuserdata(L, val); \
  lua_settable(L, -3);

int LUA_API luaopen_ludis86_C(lua_State *L)
{
	// from Lua wiki - C bindings with metatable
	luaL_register(L, LUBUDIS_REG, (luaL_Reg*)&ludis86_C);   /* create methods table, add it to the globals */

	luaL_newmetatable(L, LUBUDIS_REG);                      /* create metatable and add it to the Lua registry */
	luaL_register(L, 0, (luaL_Reg*)&ludis86_M);             /* fill metatable */
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);                        /* dup methods table*/
	lua_rawset(L, -3);                           /* metatable.__index = methods */
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);                        /* dup methods table*/
	lua_rawset(L, -3);                           /* hide metatable: metatable.__metatable = methods */
	lua_pop(L, 1);                               /* drop metatable */

	// defines
	LUA_KVE(L, UD_EOI);
	LUA_KVE(L, UD_INP_CACHE_SZ);
	LUA_KVE(L, UD_VENDOR_AMD);
	LUA_KVE(L, UD_VENDOR_INTEL);
	//LUA_KVE(L, UD_VENDOR_ANY);	// MSC: not in any udis version

	// pointers
	LUA_KVU(L, UD_SYN_INTEL);
	LUA_KVU(L, UD_SYN_ATT);

	// enum ud_type
	/* 8 bit GPRs */
	LUA_KVE(L, UD_NONE);
	LUA_KVE(L, UD_R_AL);
	LUA_KVE(L, UD_R_AL);
	LUA_KVE(L, UD_R_CL);
	LUA_KVE(L, UD_R_DL);
	LUA_KVE(L, UD_R_BL);
	LUA_KVE(L, UD_R_AH);
	LUA_KVE(L, UD_R_CH);
	LUA_KVE(L, UD_R_DH);
	LUA_KVE(L, UD_R_BH);
	LUA_KVE(L, UD_R_SPL);
	LUA_KVE(L, UD_R_BPL);
	LUA_KVE(L, UD_R_SIL);
	LUA_KVE(L, UD_R_DIL);
	LUA_KVE(L, UD_R_R8B);
	LUA_KVE(L, UD_R_R9B);
	LUA_KVE(L, UD_R_R10B);
	LUA_KVE(L, UD_R_R11B);
	LUA_KVE(L, UD_R_R12B);
	LUA_KVE(L, UD_R_R13B);
	LUA_KVE(L, UD_R_R14B);
	LUA_KVE(L, UD_R_R15B);
	/* 16 bit GPRs */
	LUA_KVE(L, UD_R_AX);
	LUA_KVE(L, UD_R_CX);
	LUA_KVE(L, UD_R_DX);
	LUA_KVE(L, UD_R_BX);
	LUA_KVE(L, UD_R_SP);
	LUA_KVE(L, UD_R_BP);
	LUA_KVE(L, UD_R_SI);
	LUA_KVE(L, UD_R_DI);
	LUA_KVE(L, UD_R_R8W);
	LUA_KVE(L, UD_R_R9W);
	LUA_KVE(L, UD_R_R10W);
	LUA_KVE(L, UD_R_R11W);
	LUA_KVE(L, UD_R_R12W);
	LUA_KVE(L, UD_R_R13W);
	LUA_KVE(L, UD_R_R14W);
	LUA_KVE(L, UD_R_R15W);
	/* 32 bit GPRs */
	LUA_KVE(L, UD_R_EAX);
	LUA_KVE(L, UD_R_ECX);
	LUA_KVE(L, UD_R_EDX);
	LUA_KVE(L, UD_R_EBX);
	LUA_KVE(L, UD_R_ESP);
	LUA_KVE(L, UD_R_EBP);
	LUA_KVE(L, UD_R_ESI);
	LUA_KVE(L, UD_R_EDI);
	LUA_KVE(L, UD_R_R8D);
	LUA_KVE(L, UD_R_R9D);
	LUA_KVE(L, UD_R_R10D);
	LUA_KVE(L, UD_R_R11D);
	LUA_KVE(L, UD_R_R12D);
	LUA_KVE(L, UD_R_R13D);
	LUA_KVE(L, UD_R_R14D);
	LUA_KVE(L, UD_R_R15D);
	/* 64 bit GPRs */
	LUA_KVE(L, UD_R_RAX);
	LUA_KVE(L, UD_R_RCX);
	LUA_KVE(L, UD_R_RDX);
	LUA_KVE(L, UD_R_RBX);
	LUA_KVE(L, UD_R_RSP);
	LUA_KVE(L, UD_R_RBP);
	LUA_KVE(L, UD_R_RSI);
	LUA_KVE(L, UD_R_RDI);
	LUA_KVE(L, UD_R_R8);
	LUA_KVE(L, UD_R_R9);
	LUA_KVE(L, UD_R_R10);
	LUA_KVE(L, UD_R_R11);
	LUA_KVE(L, UD_R_R12);
	LUA_KVE(L, UD_R_R13);
	LUA_KVE(L, UD_R_R14);
	LUA_KVE(L, UD_R_R15);
	/* segment registers */
	LUA_KVE(L, UD_R_ES);
	LUA_KVE(L, UD_R_CS);
	LUA_KVE(L, UD_R_SS);
	LUA_KVE(L, UD_R_DS);
	LUA_KVE(L, UD_R_FS);
	LUA_KVE(L, UD_R_GS);
	/* control registers*/
	LUA_KVE(L, UD_R_CR0);
	LUA_KVE(L, UD_R_CR1);
	LUA_KVE(L, UD_R_CR2);
	LUA_KVE(L, UD_R_CR3);
	LUA_KVE(L, UD_R_CR4);
	LUA_KVE(L, UD_R_CR5);
	LUA_KVE(L, UD_R_CR6);
	LUA_KVE(L, UD_R_CR7);
	LUA_KVE(L, UD_R_CR8);
	LUA_KVE(L, UD_R_CR9);
	LUA_KVE(L, UD_R_CR10);
	LUA_KVE(L, UD_R_CR11);
	LUA_KVE(L, UD_R_CR12);
	LUA_KVE(L, UD_R_CR13);
	LUA_KVE(L, UD_R_CR14);
	LUA_KVE(L, UD_R_CR15);
	/* debug registers */
	LUA_KVE(L, UD_R_DR0);
	LUA_KVE(L, UD_R_DR1);
	LUA_KVE(L, UD_R_DR2);
	LUA_KVE(L, UD_R_DR3);
	LUA_KVE(L, UD_R_DR4);
	LUA_KVE(L, UD_R_DR5);
	LUA_KVE(L, UD_R_DR6);
	LUA_KVE(L, UD_R_DR7);
	LUA_KVE(L, UD_R_DR8);
	LUA_KVE(L, UD_R_DR9);
	LUA_KVE(L, UD_R_DR10);
	LUA_KVE(L, UD_R_DR11);
	LUA_KVE(L, UD_R_DR12);
	LUA_KVE(L, UD_R_DR13);
	LUA_KVE(L, UD_R_DR14);
	LUA_KVE(L, UD_R_DR15);
	/* mmx registers */
	LUA_KVE(L, UD_R_MM0);
	LUA_KVE(L, UD_R_MM1);
	LUA_KVE(L, UD_R_MM2);
	LUA_KVE(L, UD_R_MM3);
	LUA_KVE(L, UD_R_MM4);
	LUA_KVE(L, UD_R_MM5);
	LUA_KVE(L, UD_R_MM6);
	LUA_KVE(L, UD_R_MM7);
	/* x87 registers */
	LUA_KVE(L, UD_R_ST0);
	LUA_KVE(L, UD_R_ST1);
	LUA_KVE(L, UD_R_ST2);
	LUA_KVE(L, UD_R_ST3);
	LUA_KVE(L, UD_R_ST4);
	LUA_KVE(L, UD_R_ST5);
	LUA_KVE(L, UD_R_ST6);
	LUA_KVE(L, UD_R_ST7);
	/* extended multimedia registers */
	LUA_KVE(L, UD_R_XMM0);
	LUA_KVE(L, UD_R_XMM1);
	LUA_KVE(L, UD_R_XMM2);
	LUA_KVE(L, UD_R_XMM3);
	LUA_KVE(L, UD_R_XMM4);
	LUA_KVE(L, UD_R_XMM5);
	LUA_KVE(L, UD_R_XMM6);
	LUA_KVE(L, UD_R_XMM7);
	LUA_KVE(L, UD_R_XMM8);
	LUA_KVE(L, UD_R_XMM9);
	LUA_KVE(L, UD_R_XMM10);
	LUA_KVE(L, UD_R_XMM11);
	LUA_KVE(L, UD_R_XMM12);
	LUA_KVE(L, UD_R_XMM13);
	LUA_KVE(L, UD_R_XMM14);
	LUA_KVE(L, UD_R_XMM15);
	LUA_KVE(L, UD_R_RIP);
	/* Operand Types */
	LUA_KVE(L, UD_OP_REG);
	LUA_KVE(L, UD_OP_MEM);
	LUA_KVE(L, UD_OP_PTR);
	LUA_KVE(L, UD_OP_IMM);
	LUA_KVE(L, UD_OP_JIMM);
	LUA_KVE(L, UD_OP_CONST);

/* MSC: not in any udis version
 * can cause comiler errors
	// enum from itab.h
	LUA_KVE(L, UD_TAB__OPC_TABLE);
	LUA_KVE(L, UD_TAB__OPC_X87);
	LUA_KVE(L, UD_TAB__OPC_MOD);
	LUA_KVE(L, UD_TAB__OPC_RM);
	LUA_KVE(L, UD_TAB__OPC_VENDOR);
	LUA_KVE(L, UD_TAB__OPC_OSIZE);
	LUA_KVE(L, UD_TAB__OPC_MODE);
	LUA_KVE(L, UD_TAB__OPC_3BYTE);
	LUA_KVE(L, UD_TAB__OPC_3DNOW);
	LUA_KVE(L, UD_TAB__OPC_REG);
	LUA_KVE(L, UD_TAB__OPC_ASIZE);
	LUA_KVE(L, UD_TAB__OPC_2BYTE);
*/

	lua_pop(L, 1);                               /* drop maintable */
}

