#pragma once

// init default
std::chrono::high_resolution_clock::time_point startSysClock;

namespace Core { // � ������������ ���� ����������� ����������� ����������
	extern bool criticalError = false;
	extern bool benchmode = false;
	extern bool debugmode = false;
} // TODO: ����� �� ������, �� ������ ��������� ������ ���� ������ � ������ ������

int initEngine();
bool checkDir(const char* path);