#pragma once

namespace Core { // � ������������ ���� ����������� ����������� ����������
	extern bool criticalError = false;
	extern bool benchmode = false;
	extern bool debugmode = false;
	extern bool vulkanmode = false;
} // TODO: ����� �� ������, �� ������ ��������� ������ ���� ������ � ������ ������

int initEngine();
bool checkDir(const char* path);