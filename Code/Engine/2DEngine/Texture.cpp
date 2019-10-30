#include "stdafx.h"
#include "Texture.h"

bool Nyan::Texture::loadFromFile(std::string_view file)
{
	if (!texture.loadFromFile(file.data()))
	{
		if (texture.create(2, 2))
		{
			// 2007
			sf::Uint8* pixels = new sf::Uint8[2 * 2 * 4]; //RGBA	
			/*pixels[0] = (255, 0, 220, 255);
			pixels[1] = (0, 0, 0, 255);
			pixels[2] = (255, 0, 220, 255);
			pixels[3] = (0, 0, 0, 255);*/
			for (size_t i = 0; i < 2 * 2 * 4; i += 2)
			{
				pixels[i] = 255;
				pixels[i + 1] = 0;
				pixels[i + 2] = 220;
				pixels[i + 3] = 255;
			}
			texture.update(pixels);
			//texture.setSmooth(true);
			texture.setRepeated(true);
			//delete[] pixels;
		}
		else
			return false;
	}

	return true;
}