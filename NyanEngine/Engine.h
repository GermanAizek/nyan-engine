#pragma once

// init default
std::chrono::time_point<std::chrono::system_clock> systemClock;
sf::Clock currentClock;

namespace Core
{ // В пространстве имен обязательно статические переменные
	extern bool criticalError = false;
	extern bool benchmode = false;
	extern bool debugmode = false;
} // TODO: Косяк на косяке, но нельзя проверять режимы ядра движка в других файлах

namespace EngineEvent
{
	extern bool showStats = false;
	extern bool showEditor = true;
}

int initEngine();
bool checkDir(std::string_view path);