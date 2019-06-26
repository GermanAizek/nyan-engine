#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Include.h"

#define ERROR_TEXTURE "content/textures/null.jpg"

size_t renderDeviceSFML();
void renderScene();
void loadSetTextureSprite(sf::Sprite sprite, std::string texture);

enum IDRender
{
	ERROR_FILE,
	ERROR_LOAD
};