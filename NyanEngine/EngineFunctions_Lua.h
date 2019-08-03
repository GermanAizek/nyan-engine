#pragma once

#include "Script.h"

extern Script script;

int assertExpression(lua_State* luaState);
int exitApplication(lua_State* luaState);
int getCurrentTime(lua_State* luaState);
int getSystemTime(lua_State* luaState);
int runScript(lua_State* luaState);
int getScreenWidth(lua_State* luaState);
int getScreenHeight(lua_State* luaState);
int printConsole(lua_State* luaState);
int createSprite(lua_State* luaState);
int setVerticalSync(lua_State* luaState);
int changeCursor(lua_State* luaState);
int emitSound(lua_State* luaState);
int emitMusic(lua_State* luaState);
sf::Text* createText(lua_State* luaState);//, sf::Text textObject);
int setBackground(lua_State* luaState);
int isMouseButtonPressed(lua_State* luaState);
int isKeyboardButtonPressed(lua_State* luaState);
