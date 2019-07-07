#pragma once

#include "Script.h"

extern Script script;

int getScreenWidth(lua_State* luaState);
int getScreenHeight(lua_State* luaState);
int printConsole(lua_State* luaState);
int createSprite(lua_State* luaState);
int createSound(lua_State* luaState);
int createText(lua_State* luaState);
int setBackground(lua_State* luaState);
int isMouseButtonPressed(lua_State* luaState);
int isKeyboardButtonPressed(lua_State* luaState);
