#include "stdafx.h"
#include "Texture.h"

bool Nyan::Texture::loadFromFile(std::string_view file)
{
	if (!texture.loadFromFile(file.data()))
	{
		if (!texture.loadFromFile(ERROR_TEXTURE))
			return false;
	}

	return true;
}