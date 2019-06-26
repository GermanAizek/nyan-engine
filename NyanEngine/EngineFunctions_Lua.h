#pragma once

#include "Include.h"
#include "Script.h"

extern Script script;

int Write(lua_State*);
int CreateBox(lua_State*);
int CreatePerson(lua_State*);
int SetBackground(lua_State*);
