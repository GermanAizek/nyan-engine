#include "EngineFunctions_Lua.h"
//#include "EngineFunctions.h"
#include "Script.h"
#include "Allocator.h"
//#include "ScriptRender.h"
#include "RenderVulkan.h"
// TODO: Добавить больше методов функций для работы с движком

Script script;

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

	addAllocator(sprite);

	return 0;
}

int CreatePerson(lua_State*) {
	std::cout << script.GetArgument<char*>(1);
	//createPerson(script.GetArgument<char*>(1)); //, script.GetArgument<char*>(2), script.GetArgument<char*>(3), script.GetArgument<double>(4));
	// char* -> string, char* -> sf::Vector2f, char* -> sf::Vector2f

	std::cout << "Create Person\n";
	sf::Texture texture;
	if (!texture.loadFromFile(script.GetArgument<char*>(1))) {
		if (!texture.loadFromFile(ERROR_TEXTURE))
			return ERROR_LOAD;
	}

	sf::Sprite sprite(texture);
	sprite.setPosition(sf::Vector2f(200, 100));
	sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	//sprite.setPosition(pos);
	//sprite.setRotation(angle);
	//sprite.setScale(scale);
	texture.setSmooth(true); //antialiasing

	addAllocator(sprite);
	
	std::cout << "Call func lua CreatePerson\n";

	return 0;
}

int SetColorSpace(lua_State*) {
	std::array<VkClearValue, 2> clearValues = {};
	clearValues[0].color = { (float)script.GetArgument<double>(1), (float)script.GetArgument<double>(2),  (float)script.GetArgument<double>(3), (float)script.GetArgument<double>(4) }; // RGBA
	clearValues[1].depthStencil = { 1.0f, 0 };

	return 0;
}