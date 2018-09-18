#pragma once

#include "Include.h"
#include "Render.h"

std::vector<sf::Sprite> vectorSprites;

size_t initAllocator();
size_t addAllocator(sf::Sprite &sprite);
//sf::Texture/* sf::Sprite* */ pullerAllocator();
//sf::Sprite spaceFunction(sf::Sprite ptr);