#pragma once

#include "Script.h"

extern Script script;

int getScreenWidth(lua_State* luaState);
int getScreenHeight(lua_State* luaState);
int PrintConsole(lua_State* luaState);
int CreateSprite(lua_State* luaState);
int CreateText(lua_State* luaState);
int SetBackground(lua_State* luaState);
