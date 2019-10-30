#pragma once

#define ERROR_TEXTURE "content/textures/system/null.jpg"
#define ERROR_FONT "content/fonts/arial.ttf"

namespace Nyan
{
	class Texture
	{
	private:
		sf::Texture texture;
	public:
		Texture() { }
		Texture(std::string_view file) { loadFromFile(file); }
		sf::Texture get() { return this->texture; }

		bool loadFromFile(std::string_view file);
	};
}