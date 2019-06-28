#pragma once

namespace Core { // В пространстве имен обязательно статические переменные
	extern bool criticalError = false;
	extern bool benchmode = false;
	extern bool debugmode = false;
} // TODO: Косяк на косяке, но нельзя проверять режимы ядра движка в других файлах

int initEngine();
bool checkDir(const char* path);