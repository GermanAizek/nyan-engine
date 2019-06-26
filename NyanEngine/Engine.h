#pragma once

#include "Include.h"

namespace Core { // В пространстве имен обязательно статические переменные
	extern bool criticalError = false;
	extern bool benchmode = false;
	extern bool debugmode = false;
	extern bool vulkanmode = false;
} // TODO: Косяк на косяке, но нельзя проверять режимы ядра движка в других файлах

size_t initEngine();
bool checkDir(const char* path);