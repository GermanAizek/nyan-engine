#pragma once

#include "stdafx.h"

#define ERROR_TEXTURE "content/textures/null.jpg"

size_t WIDTH = sf::VideoMode::getDesktopMode().width;
size_t HEIGHT = sf::VideoMode::getDesktopMode().height;

size_t renderDeviceSFML();
void renderScene();
void loadSetTextureSprite(sf::Sprite sprite, std::string texture);
void addAllocator(sf::Sprite& sprite, sf::Texture& texture);

std::vector<std::pair<sf::Sprite, sf::Texture>> mapSpriteTexture;

enum IDRender
{
	ERROR_FILE,
	ERROR_LOAD
};