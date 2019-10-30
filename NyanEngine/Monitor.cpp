#include "stdafx.h"
#include "Monitor.h"

size_t getFPS(const sf::Time& time)
{
	return (1000000.0f / time.asMicroseconds());
}

void statsHandler(sf::RenderWindow& window, size_t fps)
{
	sf::Font font;
	if (!font.loadFromFile("content//fonts//arialbd.ttf"))
		return;

	sf::Text textStats;
	textStats.setFont(font);
	textStats.setCharacterSize(24);
	textStats.setPosition(0, 0);

	if (fps < 30)
		textStats.setFillColor(sf::Color::Red);
	else if (fps < 60)
		textStats.setFillColor(sf::Color::Yellow);
	else
		textStats.setFillColor(sf::Color::Green);

	textStats.setString("FPS " + std::to_string(fps));

	window.draw(textStats);
}