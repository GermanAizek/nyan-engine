#pragma once

#include "Include.h"
#include "Script.h"

extern Script script;

// Здесь декларации функций для работы с движком на луа
int Write(lua_State*);
int CreateBox(lua_State*);
int CreatePerson(lua_State*);
int SetColorSpace(lua_State*);
