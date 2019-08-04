#include "stdafx.h"
#include "SoundManager.h"
#include "ErrorLogger.h"

sf::Sound loadSound(std::string_view filename)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filename.data()))
		addLogFile("sound not loaded!");

	return sf::Sound(buffer);
}