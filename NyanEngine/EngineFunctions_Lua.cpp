#include "stdafx.h"
#include "EngineFunctions_Lua.h"
//#include "EngineFunctions.h"
#include "Render.h"
#include "Script.h"
//#include "ScriptRender.h"
// TODO: Добавить больше методов функций для работы с движком

Script script;

int Write(lua_State*)
{
	for (size_t i = 1; i < script.GetArgumentCount() + 1; ++i)
		std::cout << script.GetArgument<char*>(i);

	return 0;
}

int CreateBox(lua_State*)
{
	sf::Texture tex;
	tex.setSmooth(true); //antialiasing
	if (!tex.loadFromFile(script.GetArgument<char*>(1), sf::IntRect(script.GetArgument<int>(2), script.GetArgument<int>(3),
		script.GetArgument<int>(4), script.GetArgument<int>(5))))
	{
		std::cout << "NOT Creating Box!\n";
		return 1;
	}

	sf::Sprite sprite(tex);
	addAllocator(sprite, tex);

	return 0;
}

int CreatePerson(lua_State*)
{
	sf::Texture texture;
	texture.setSmooth(true); //antialiasing
	if (!texture.loadFromFile(script.GetArgument<char*>(1)))
	{
		if (!texture.loadFromFile(ERROR_TEXTURE))
			return ERROR_LOAD;
	}

	sf::Sprite sprite(texture);
	sprite.setPosition(sf::Vector2f(script.GetArgument<double>(2), script.GetArgument<double>(3)));
	sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	//sprite.setPosition(pos);
	//sprite.setRotation(angle);
	//sprite.setScale(scale);
	addAllocator(sprite, texture);

	return 0;
}

int SetBackground(lua_State*)
{
	sf::Texture texture;
	texture.setSmooth(true); //antialiasing
	if (!texture.loadFromFile(script.GetArgument<char*>(1)))
	{
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