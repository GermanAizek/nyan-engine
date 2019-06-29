#include "stdafx.h"
#include "EngineFunctions_Lua.h"
//#include "EngineFunctions.h"
#include "Render.h"
#include "Script.h"
//#include "ScriptRender.h"
// TODO: Добавить больше методов функций для работы с движком

Script script;

// constants
int getScreenWidth(lua_State* luaState)
{
	lua_pushinteger(luaState, WIDTH);

	return 1;
}

int getScreenHeight(lua_State* luaState)
{
	lua_pushinteger(luaState, HEIGHT);

	return 1;
}

// console
int PrintConsole(lua_State* luaState)
{
	for (size_t i = 1; i < script.GetArgumentCount() + 1; ++i)
		std::cout << script.GetArgument<char*>(i);

	return 0;
}

// graphics
int CreateSprite(lua_State* luaState)
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
	sprite.setScale(sf::Vector2f(script.GetArgument<double>(4), script.GetArgument<double>(5)));
	addAllocator(sprite, texture);

	return 0;
}

/*
int setupFont(lua_State* luaState)
{
	sf::Font font;
	if (!font.loadFromFile(script.GetArgument<char*>(1)))
	{
		if (!font.loadFromFile(ERROR_FONT))
			return ERROR_LOAD;
	}

	int b = lua_tointeger(luaState, &font);
	lua_pop(luaState, 1);
	return b;
}
*/

int CreateText(lua_State* luaState)
{
	sf::Font font;
	if (!font.loadFromFile(script.GetArgument<char*>(2)))
	{
		if (!font.loadFromFile(ERROR_FONT))
			return ERROR_LOAD;
	}

	sf::Text text;
	text.setString(script.GetArgument<char*>(1));
	text.setCharacterSize(script.GetArgument<int>(3));
	text.setPosition(script.GetArgument<double>(4), script.GetArgument<double>(5));
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2.0f);
	text.setLineSpacing(1.1f);
	addAllocatorText(text, font);

	return 0;
}

int SetBackground(lua_State* luaState)
{
	sf::Texture texture;
	texture.setSmooth(true); //antialiasing
	if (!texture.loadFromFile(script.GetArgument<char*>(1)))
	{
		if (!texture.loadFromFile(ERROR_TEXTURE))
			return ERROR_LOAD;
	}

	sf::Sprite sprite;
	sf::Vector2u vec = texture.getSize();
	sprite.setScale((double)WIDTH / (double)vec.x, (double)HEIGHT / (double)vec.y);
	addAllocator(sprite, texture);

	return 0;
}