#pragma once

// init default
std::chrono::time_point<std::chrono::system_clock> systemClock;
sf::Clock currentClock;

namespace Core { // � ������������ ���� ����������� ����������� ����������
	extern bool criticalError = false;
	extern bool benchmode = false;
	extern bool debugmode = false;
} // TODO: ����� �� ������, �� ������ ��������� ������ ���� ������ � ������ ������

int initEngine();
bool checkDir(const char* path);