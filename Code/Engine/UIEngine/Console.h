#pragma once

#include "Render.h"

void consoleCreate(std::string_view name);
size_t consoleHandler();
void printConsole(std::string_view text);

bool consoleOpened = false;

std::string consoleLine("");
std::string commandLine("");