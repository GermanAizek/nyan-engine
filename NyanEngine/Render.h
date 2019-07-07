#pragma once

#include "stdafx.h"

#define ERROR_TEXTURE "content/textures/null.jpg"
#define ERROR_FONT "content/fonts/arial.ttf"

int WIDTH = sf::VideoMode::getDesktopMode().width;
int HEIGHT = sf::VideoMode::getDesktopMode().height;

void startScript(std::string nameFile);

size_t renderDeviceSFML();
void renderScene();
void loadSetTextureSprite(sf::Sprite sprite, std::string texture);
void addAllocator(sf::Sprite& sprite, sf::Texture& texture);
void addAllocatorText(sf::Text& text, sf::Font& font);

std::vector<std::pair<sf::Sprite, sf::Texture>> mapAllocator;
std::vector<std::pair<sf::Text, sf::Font>> mapAllocatorText;

enum IDRender
{
	ERROR_FILE,
	ERROR_LOAD
};