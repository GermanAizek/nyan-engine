#pragma once

#include "Include.h"

namespace Core { // � ������������ ���� ����������� ����������� ����������
	extern bool criticalError = false;
	extern bool benchmode = false;
	extern bool debugmode = false;
	extern bool vulkanmode = false;
}// HACK: ����� �� ������, �� ������ ��������� ������ ���� ������ � ������ ������

size_t initEngine();
bool checkDir(const char* path);