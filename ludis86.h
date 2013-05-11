#ifndef LUDIS86_H
#define LUDIS86_H

/*
 * libudis86 Lua bindings
 */

//extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
//}

#ifndef LUA_API
#ifdef WIN32
#define LUA_API __cdecl __declspec(dllexport)
#else
#define LUA_API
#endif
#endif

//extern "C" {
		int LUA_API ludis86(lua_State *L);
//}


#endif	/* LUDIS86_H */
