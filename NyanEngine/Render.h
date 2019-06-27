#pragma once

#include "stdafx.h"

#define ERROR_TEXTURE "content/textures/null.jpg"

size_t renderDeviceSFML();
void renderScene();
void loadSetTextureSprite(sf::Sprite sprite, std::string texture);

enum IDRender
{
	ERROR_FILE,
	ERROR_LOAD
};