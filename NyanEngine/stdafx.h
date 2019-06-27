#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <windows.h>
#include <ctime>
#include <chrono>
#include <algorithm>
//#include <io.h>

// Lua 5.3
#pragma comment(lib, "lua53.lib")

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
//

// Python
//#include <Python.h>
//#pragma comment (lib, "python38.lib")
//

// TODO: reference additional headers your program requires here
