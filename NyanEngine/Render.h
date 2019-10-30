#pragma once

#include "stdafx.h"
#include "Script.h"

int startScript(std::string_view nameFile);
int connectToScript(std::string_view nameFile, Script& script);

size_t renderDeviceSFML();
void addAllocator(sf::Sprite& sprite, sf::Texture& texture);
void addAllocatorSound(sf::Sound& sound);
void addAllocatorText(sf::Text text, sf::Font font);

extern std::vector<std::pair<sf::Sprite, sf::Texture>> mapAllocator;
extern std::vector<sf::Text/*std::pair<sf::Text, sf::Font>*/> mapAllocatorText;
extern std::vector<sf::Sound> mapAllocatorSound;

enum IDRender
{
	ERROR_FILE,
	ERROR_LOAD
};

size_t WIDTH = sf::VideoMode::getDesktopMode().width;
size_t HEIGHT = sf::VideoMode::getDesktopMode().height;

/*
b2Vec2 physGravity(0.f, 9.8f);
b2World physSpace(physGravity);
*/