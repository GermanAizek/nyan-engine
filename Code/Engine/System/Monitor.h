#pragma once
#include "stdafx.h"

size_t getFPS(const sf::Time& time);
void statsHandler(sf::RenderWindow& window, size_t fps);

bool statsOpened = false;
