#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Include.h"

#define ERROR_TEXTURE "content/textures/null.jpg"

size_t renderDeviceSFML();
size_t renderDeviceVulkan();
size_t renderDeviceFalcor();
void renderScene();
void loadSetTextureSprite(sf::Sprite sprite, std::string texture);

enum ID_Render { // Нумерация ошибок в рендере
	ERROR_FILE,
	ERROR_LOAD
};

// Vulkan API class application


//