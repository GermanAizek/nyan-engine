#pragma once

#include "stdafx.h"

typedef struct Settings
{
	std::string renderer = "sfml";
	size_t w = 1366;
	size_t h = 768;
	size_t frameratemax = 60;
	bool vsync = false;
	bool windowed = true;
	bool devconfig = false;
} Settings;

typedef struct GameSettings
{
	std::string namewindow = "Nyan engine";
	size_t countscenes = 0;
} GameSettings;

typedef struct SceneSettings
{
	std::string namescene = "Test";
	size_t count_obj;
} SceneSettings;

bool parseSettings();
bool parseGame();
bool parseScene();
