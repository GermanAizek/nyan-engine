#pragma once

#include "stdafx.h"

#define ERROR_TEXTURE "content/textures/null.jpg"
#define ERROR_FONT "content/fonts/arial.ttf"

size_t WIDTH = sf::VideoMode::getDesktopMode().width;
size_t HEIGHT = sf::VideoMode::getDesktopMode().height;

int startScript(std::string nameFile);

size_t renderDeviceSFML();
void renderScene();
void loadSetTextureSprite(sf::Sprite sprite, std::string texture);
void addAllocator(sf::Sprite& sprite, sf::Texture& texture);
void addAllocatorSound(sf::Sound& sound);
void addAllocatorText(sf::Text& text, sf::Font& font);

std::vector<std::pair<sf::Sprite, sf::Texture>> mapAllocator;
std::vector<std::pair<sf::Text, sf::Font>> mapAllocatorText;
std::vector<sf::Sound> mapAllocatorSound;

enum IDRender
{
	ERROR_FILE,
	ERROR_LOAD
};