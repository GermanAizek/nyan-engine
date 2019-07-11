#include "stdafx.h"
#include "SoundManager.h"
#include "ErrorLogger.h"

sf::Sound loadSound(const char* filename)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filename))
		addLogFile("sound not loaded!");

	return sf::Sound(buffer);
}