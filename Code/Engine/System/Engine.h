#pragma once

// init default
std::chrono::time_point<std::chrono::system_clock> systemClock;
sf::Clock currentClock;

namespace Core
{
	extern bool criticalError = false;
	extern bool benchmode = false;
	extern bool debugmode = false;
}

namespace EngineEvent
{
	extern bool showStats = false;
	extern bool showEditor = false;
}

int initEngine();
bool checkDir(std::string_view path);