#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <thread>
#include <windows.h>
#include <ctime>
#include <chrono>
#include <algorithm>
//#include <io.h>

// sfml render
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "imgui.h"
#include "imgui-sfml.h"

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
