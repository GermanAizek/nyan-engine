#pragma once

namespace Nyan
{
	class Grid
	{
	private:
		sf::RenderWindow* gridWindow;
		int row;
		int col;
	public:
		Grid(int r, int c, sf::RenderWindow* window);
	};
}

