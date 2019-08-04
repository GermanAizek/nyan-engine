#pragma once

#include "stdafx.h"

typedef struct Settings
{
	size_t w = 1366;
	size_t h = 768;
	size_t frameratemax = 60;
	bool vsync = false;
	bool windowed = true;
	bool devconfig = false;
} Settings;

bool parseSettings();
