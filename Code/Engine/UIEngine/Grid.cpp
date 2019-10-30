#include "stdafx.h"
#include "Grid.h"

Nyan::Grid::Grid(int r, int c, sf::RenderWindow* window) : row(r), col(c), gridWindow(window)
{
	int w = gridWindow->getSize().x * 1.0 / row;
	int h = gridWindow->getSize().y * 1.0 / col;

	//std::vector<sf::RectangleShape> shapes;

	// need to create an actual cell
	int baseX = 100;
	int baseY = 100;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			sf::RectangleShape shape;
			shape.setPosition(baseX, baseY);
			shape.setFillColor(sf::Color::Yellow);
			shape.setOutlineColor(sf::Color::White);
			shape.setOutlineThickness(10);
			window->draw(shape);
			//shapes.push_back(shape);
			baseX += w;
		}

		baseX = 10;
		baseY += h;
	}
}
