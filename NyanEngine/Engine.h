#pragma once

namespace Core { // � ������������ ���� ����������� ����������� ����������
	extern bool criticalError = false;
	extern bool benchmode = false;
	extern bool debugmode = false;
} // TODO: ����� �� ������, �� ������ ��������� ������ ���� ������ � ������ ������

int initEngine();
bool checkDir(const char* path);