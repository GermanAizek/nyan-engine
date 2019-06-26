#pragma once

// Lua 5.3
#pragma comment(lib, "lua53.lib")

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
//

#ifndef _SCRIPT_H_
#define _SCRIPT_H_

class Script
{
	lua_State *lua_state;

public:
	void Create();
	void Close();
	int DoFile(char* ScriptFileName);
	template<class T>
	void RegisterConstant(T value, char* constantname);

	void Array();
	template<class T>
	void RegisterConstantArray(T value, int index);
	void RegisterArray(char* arrayname);

	int GetArgumentCount();
	template<class T>
	T GetArgument(int index);
	template<class T>
	void Return(T value);
};

#endif