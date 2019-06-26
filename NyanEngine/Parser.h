#pragma once

#include "Include.h"

#define u_int unsigned int

typedef struct Settings
{
	std::string renderer = "sfml";
	u_int w = 1366;
	u_int h = 768;
	u_int frameratemax = 60;
	bool vsync = false;
	bool windowed = true;
	bool devconfig = false;
} Settings;

typedef struct GameSettings
{
	std::string namewindow = "Nyan engine";
	size_t countscenes = 0;
} GameSettings;

#include "RenderVulkan.h"

typedef struct SceneSettings
{
	std::string namescene = "Test";
	size_t count_obj;
	glm::vec3 coordinatesObj[1000];
} SceneSettings;

bool parseSettings();
bool parseGame();
bool parseScene();
