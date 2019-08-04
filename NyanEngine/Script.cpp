#include "stdafx.h"
#include "Script.h"
#include "ErrorLogger.h"

#include <iostream>

void reportErrors(lua_State* L, int status)
{
	
}

lua_State* Script::Create()
{
	lua_state = luaL_newstate();

	static const luaL_Reg lualibs[] = {
		{ "base", luaopen_base },
		{ "bit32", luaopen_bit32 },
		{ "coroutine", luaopen_coroutine },
		{ "debug", luaopen_debug },
		{ "io", luaopen_io },
		{ "math", luaopen_math },
		{ "os", luaopen_os },
		{ "package", luaopen_package },
		{ "string", luaopen_string },
		{ "table", luaopen_table },
		{ "utf8", luaopen_utf8 },
		{ NULL, NULL }
	};

	for (const luaL_Reg *lib = lualibs; lib->func != NULL; lib++)
	{
		luaL_requiref(lua_state, lib->name, lib->func, 1);
		lua_settop(lua_state, 0);
	}

	return lua_state;
}

void Script::Close()
{
	lua_close(lua_state);
}

int Script::DoFile(std::string_view fileName)
{
	auto status = luaL_dofile(lua_state, fileName.data());

	if (status != 0)
	{
		std::string error = lua_tostring(lua_state, -1);
		addLogFile("[ERROR] " + error);
		lua_pop(lua_state, 1); // remove error message
	}

	return lua_tointeger(lua_state, lua_gettop(lua_state));
}

template<>
void Script::RegisterConstant<int>(int value, char* constantname)
{
	lua_pushinteger(lua_state, value);
	lua_setglobal(lua_state, constantname);
}

template<>
void Script::RegisterConstant<double>(double value, char* constantname)
{
	lua_pushnumber(lua_state, value);
	lua_setglobal(lua_state, constantname);
}

template<>
void Script::RegisterConstant<char*>(char* value, char* constantname)
{
	lua_pushstring(lua_state, value);
	lua_setglobal(lua_state, constantname);
}

template<>
void Script::RegisterConstant<bool>(bool value, char* constantname)
{
	lua_pushboolean(lua_state, value);
	lua_setglobal(lua_state, constantname);
}

template<>
void Script::RegisterConstant<lua_CFunction>(int(*value)(lua_State*), char* constantname)
{
	lua_pushcfunction(lua_state, value);
	lua_setglobal(lua_state, constantname);
}


void Script::Array()
{
	lua_createtable(lua_state, 2, 0);
}


template<>
void Script::RegisterConstantArray<int>(int value, int index)
{
	lua_pushnumber(lua_state, index);
	lua_pushinteger(lua_state, value);
	lua_settable(lua_state, -3);
}

template<>
void Script::RegisterConstantArray<double>(double value, int index)
{
	lua_pushnumber(lua_state, index);
	lua_pushnumber(lua_state, value);
	lua_settable(lua_state, -3);
}

template<>
void Script::RegisterConstantArray<char*>(char* value, int index)
{
	lua_pushnumber(lua_state, index);
	lua_pushstring(lua_state, value);
	lua_settable(lua_state, -3);
}

template<>
void Script::RegisterConstantArray<bool>(bool value, int index)
{
	lua_pushnumber(lua_state, index);
	lua_pushboolean(lua_state, value);
	lua_settable(lua_state, -3);
}

template<>
void Script::RegisterConstantArray<lua_CFunction>(lua_CFunction value, int index)
{
	lua_pushnumber(lua_state, index);
	lua_pushcfunction(lua_state, value);
	lua_settable(lua_state, -3);
}

void Script::RegisterArray(char* arrayname)
{
	lua_setglobal(lua_state, arrayname);
}

template<>
void Script::RegisterFieldGlobal<int>(int value, std::string_view text)
{
	lua_pushinteger(lua_state, value);
	lua_setfield(lua_state, -2, text.data());
}

template<>
void Script::RegisterFieldGlobal<double>(double value, std::string_view text)
{
	lua_pushnumber(lua_state, value);
	lua_setfield(lua_state, -2, text.data());
}

template<>
void Script::RegisterFieldGlobal<char*>(char* value, std::string_view text)
{
	lua_pushstring(lua_state, value);
	lua_setfield(lua_state, -2, text.data());
}

template<>
void Script::RegisterFieldGlobal<bool>(bool value, std::string_view text)
{
	lua_pushboolean(lua_state, value);
	lua_setfield(lua_state, -2, text.data());
}

template<>
void Script::RegisterFieldGlobal<lua_CFunction>(lua_CFunction value, std::string_view text)
{
	lua_pushcfunction(lua_state, value);
	lua_setfield(lua_state, -2, text.data());
}

int Script::GetArgumentCount()
{
	return lua_gettop(lua_state);
}

template<>
int Script::GetArgument<int>(int index)
{
	return lua_tointeger(lua_state, index);
}

template<>
double Script::GetArgument<double>(int index)
{
	return lua_tonumber(lua_state, index);
}

template<>
int* Script::GetArgument<int*>(int index)
{
	return (int*)lua_topointer(lua_state, index);
	//return (double*)lua_tonumber(lua_state, index);
	//return (double*)lua_touserdata(lua_state, index);
}

template<>
char* Script::GetArgument<char*>(int index)
{
	return (char*)lua_tostring(lua_state, index);
}

template<>
bool Script::GetArgument<bool>(int index)
{
	return lua_toboolean(lua_state, index);
}


template<>
void Script::Return<int>(int value)
{
	lua_pushinteger(lua_state, value);
}

template<>
void Script::Return<double>(double value)
{
	lua_pushnumber(lua_state, value);
}

template<>
void Script::Return<char*>(char* value)
{
	lua_pushstring(lua_state, value);
}

template<>
void Script::Return<bool>(bool value)
{
	lua_pushboolean(lua_state, value);
}