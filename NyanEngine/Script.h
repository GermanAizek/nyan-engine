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
	lua_State* Create();
	void Close();
	int DoFile(const char* ScriptFileName);
	template<class T>
	void RegisterConstant(T value, char* constantname);

	void Array();

	template<class T>
	void RegisterConstantArray(T value, int index);
	void RegisterArray(char* arrayname);

	template<class T>
	void RegisterFieldGlobal(T value, const char* text);

	int GetArgumentCount();
	template<class T>
	T GetArgument(int index);
	template<class T>
	void Return(T value);
};

#endif