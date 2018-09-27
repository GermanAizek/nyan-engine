#pragma once

#include "Include.h"
#include "Render.h"

std::vector<std::pair<sf::Sprite, sf::Texture>> mapSpriteTexture;

size_t initAllocator();
size_t addAllocator(sf::Sprite &sprite, sf::Texture &texture);
//sf::Texture/* sf::Sprite* */ pullerAllocator();
//sf::Sprite spaceFunction(sf::Sprite ptr);