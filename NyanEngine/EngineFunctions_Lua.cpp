#include "EngineFunctions_Lua.h"
//#include "EngineFunctions.h"
#include "Script.h"
#include "Allocator.h"
//#include "ScriptRender.h"
#include "RenderVulkan.h"
// TODO: Добавить больше методов функций для работы с движком

Script script;

unsigned int WIDTH = sf::VideoMode::getDesktopMode().width;
unsigned int HEIGHT = sf::VideoMode::getDesktopMode().height;

int Write(lua_State*) {
	// Тут мы считываем количество аргументов и каждый аргумент выводим
	for (size_t i = 1; i < script.GetArgumentCount() + 1; ++i) std::cout << script.GetArgument<char*>(i);

	return 0;
}

int CreateBox(lua_State*) {
	sf::Texture tex;
	if (!tex.loadFromFile(script.GetArgument<char*>(1), sf::IntRect(script.GetArgument<int>(2), script.GetArgument<int>(3), script.GetArgument<int>(4), script.GetArgument<int>(5)))) {
		std::cout << "NOT Creating Box!\n";
		return 1;
	}
	sf::Sprite sprite(tex);

	addAllocator(sprite, tex);

	return 0;
}

int CreatePerson(lua_State*) {
	sf::Texture texture;
	if (!texture.loadFromFile(script.GetArgument<char*>(1))) {
		if (!texture.loadFromFile(ERROR_TEXTURE))
			return ERROR_LOAD;
	}

	sf::Sprite sprite(texture);
	sprite.setPosition(sf::Vector2f(script.GetArgument<double>(2), script.GetArgument<double>(3)));
	sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	//sprite.setPosition(pos);
	//sprite.setRotation(angle);
	//sprite.setScale(scale);
	texture.setSmooth(true); //antialiasing

	addAllocator(sprite, texture);

	return 0;
}

int SetBackground(lua_State*) {
	sf::Texture texture;
	texture.setSmooth(true); //antialiasing
	if (!texture.loadFromFile(script.GetArgument<char*>(1))) {
		if (!texture.loadFromFile(ERROR_TEXTURE))
			return ERROR_LOAD;
	}

	sf::Sprite sprite;
	//sprite.setPosition(sf::Vector2f(200, 100));
	sf::Vector2u vec = texture.getSize();
	sprite.setScale((double)WIDTH / (double)vec.x, (double)HEIGHT / (double)vec.y);
	//sprite.setPosition(pos);
	//sprite.setRotation(angle);
	//sprite.setScale(scale);

	addAllocator(sprite, texture);

	return 0;
}

int SetColorSpace(lua_State*) {
	std::array<VkClearValue, 2> clearValues = {};
	clearValues[0].color = { (float)script.GetArgument<double>(1), (float)script.GetArgument<double>(2),  (float)script.GetArgument<double>(3), (float)script.GetArgument<double>(4) }; // RGBA
	clearValues[1].depthStencil = { 1.0f, 0 };

	return 0;
}