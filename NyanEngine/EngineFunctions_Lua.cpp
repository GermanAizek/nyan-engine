#include "stdafx.h"
#include "EngineFunctions_Lua.h"
#include "Engine.h"
#include "Render.h"
#include "SoundManager.h"
#include "Script.h"
#include <any>

// TODO: Добавить больше методов функций для работы с движком

Script script;

// global functions

// system
int assertExpression(lua_State* luaState)
{
	//bool cond = script.GetArgument<bool>(1);
	//if (lua_assert(cond))
		lua_pushboolean(luaState, true);
	//else
		lua_pushboolean(luaState, false);

	return 1;
}

int exitApplication(lua_State* luaState)
{
	Core::criticalError = true;
	exit(0);

	return 0;
}

int color(lua_State* luaState)
{
	auto getColor = []() {
		sf::Color color;
		color.r = script.GetArgument<int>(1);
		color.g = script.GetArgument<int>(2);
		color.b = script.GetArgument<int>(3);
		color.a = script.GetArgument<int>(4);

		//return color;
	};

	// TODO: return array or data (class sf::Color)

	//lua_pushcclosure(luaState, getColor);

	return 1;
}

int colorRandom(lua_State* luaState)
{
	auto getColor = []() {
		sf::Color color;
		color.r = script.GetArgument<int>(1);
		color.g = script.GetArgument<int>(2);
		color.b = script.GetArgument<int>(3);
		color.a = script.GetArgument<int>(4);

		return color;
	};

	//lua_pushlightuserdata(luaState, getColor);
	

	return 1;
}

int getCurrentTime(lua_State* luaState)
{
	sf::Time sysTime = currentClock.getElapsedTime();
	lua_pushnumber(luaState, sysTime.asSeconds());

	return 1;
}

int getSystemTime(lua_State* luaState)
{
	// TODO: Re-edit getSystemTime, its should get seconds
	std::time_t end_time = std::chrono::system_clock::to_time_t(systemClock);
	lua_pushnumber(luaState, end_time);

	return 1;
}

int runScript(lua_State* luaState)
{
	if (!startScript(script.GetArgument<char*>(1)))
		lua_pushboolean(luaState, true);
	else
		lua_pushboolean(luaState, false);

	return 1;
}

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

// window
//int getScreenHeight(lua_State* luaState, void** p)
//{

//	return 1;
//}

// console
int printConsole(lua_State* luaState)
{
	for (size_t i = 1; i < script.GetArgumentCount() + 1; ++i)
		std::cout << script.GetArgument<char*>(i);

	return 0;
}

// graphics
int createSprite(lua_State* luaState)
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

sf::Text* createText(lua_State* luaState)//, sf::Text textObject)
{
	sf::Font font;
	if (!font.loadFromFile(script.GetArgument<char*>(2)))
	{		
		if (!font.loadFromFile(ERROR_FONT))
			return nullptr;
	}

	// push pointer to text
	sf::Text* text = (sf::Text*)lua_newuserdata(luaState, sizeof(sf::Text));
	text->setString(script.GetArgument<char*>(1));
	text->setCharacterSize(script.GetArgument<int>(3));
	text->setPosition(script.GetArgument<double>(4), script.GetArgument<double>(5));
	text->setFillColor(sf::Color::White);
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(2.0f);
	text->setLineSpacing(1.1f);
	//*text = textObject;
	luaL_getmetatable(luaState, "Text");
	lua_setmetatable(luaState, -2);

	return text;
}

int setBackground(lua_State* luaState)
{
	sf::Texture texture;
	texture.setSmooth(true); //antialiasing
	texture.setRepeated(true);
	if (!texture.loadFromFile(script.GetArgument<char*>(1)))
	{
		if (!texture.loadFromFile(ERROR_TEXTURE))
			return ERROR_LOAD;
	}

	sf::Sprite sprite;
	sf::Vector2u vec = texture.getSize();
	sprite.setScale(WIDTH / vec.x, HEIGHT / vec.y);
	addAllocator(sprite, texture);

	return 0;
}

int setVerticalSync(lua_State* luaState)
{
	try
	{
		//script.GetArgument<sf::RenderWindow>(1).setVerticalSyncEnabled(script.GetArgument<bool>(2));
		lua_pushboolean(luaState, true);
		return 1;
	}
	catch (...)
	{
		lua_pushboolean(luaState, false);
		return 1;
	}
}

// sound
int emitSound(lua_State* luaState)
{
	try
	{
		sf::Sound sound = loadSound(script.GetArgument<char*>(1));
		sound.play();
		sound.setVolume(100.f);

		//addAllocatorSound(sound);

		int* pos = script.GetArgument<int*>(2);
		if (pos)
			sound.setPosition(pos[0], pos[1], pos[2]);

		//lua_pushboolean(luaState, true);
		lua_pushinteger(luaState, pos[0]);
		lua_pushinteger(luaState, pos[1]);
		lua_pushinteger(luaState, pos[2]);
		return 3;
	}
	catch (...)
	{
		lua_pushboolean(luaState, false);
		return 1;
	}
}

int emitMusic(lua_State* luaState)
{
	try
	{
		sf::Music music;
		if (!music.openFromFile(script.GetArgument<char*>(1)))
		{
			lua_pushboolean(luaState, false);
			throw "Music not loaded";
		}

		music.play();

		lua_pushboolean(luaState, true);
		return 1;
	}
	catch (...)
	{
		lua_pushboolean(luaState, false);
		return 1;
	}
}

// input/output handler
int isMouseButtonPressed(lua_State* luaState)
{
	char* keyPressed = script.GetArgument<char*>(1);
	sf::Mouse::Button enumKey;

	if (keyPressed == "MOUSE_LEFT")
		enumKey = sf::Mouse::Left;
	else if(keyPressed == "MOUSE_RIGHT")
		enumKey = sf::Mouse::Right;
	else if (keyPressed == "MOUSE_MIDDLE")
		enumKey = sf::Mouse::Middle;
	else if (keyPressed == "MOUSE_4")
		enumKey = sf::Mouse::XButton1;
	else if (keyPressed == "MOUSE_5")
		enumKey = sf::Mouse::XButton2;

	if (sf::Mouse::isButtonPressed(enumKey))
		lua_pushboolean(luaState, true);
	else
		lua_pushboolean(luaState, false);

	return 1;
}

int isKeyboardButtonPressed(lua_State* luaState)
{
	char* keyPressed = script.GetArgument<char*>(1);
	sf::Keyboard::Key enumKey;

	if (keyPressed == "KEY_0")
		enumKey = sf::Keyboard::Num0;
	else if (keyPressed == "KEY_1")
		enumKey = sf::Keyboard::Num1;
	else if (keyPressed == "KEY_2")
		enumKey = sf::Keyboard::Num2;
	else if (keyPressed == "KEY_3")
		enumKey = sf::Keyboard::Num3;
	else if (keyPressed == "KEY_4")
		enumKey = sf::Keyboard::Num4;
	else if (keyPressed == "KEY_5")
		enumKey = sf::Keyboard::Num5;
	else if (keyPressed == "KEY_6")
		enumKey = sf::Keyboard::Num6;
	else if (keyPressed == "KEY_7")
		enumKey = sf::Keyboard::Num7;
	else if (keyPressed == "KEY_8")
		enumKey = sf::Keyboard::Num8;
	else if (keyPressed == "KEY_9")
		enumKey = sf::Keyboard::Num9;
	else if (keyPressed == "KEY_A")
		enumKey = sf::Keyboard::A;
	else if (keyPressed == "KEY_B")
		enumKey = sf::Keyboard::B;
	else if (keyPressed == "KEY_C")
		enumKey = sf::Keyboard::C;
	else if (keyPressed == "KEY_D")
		enumKey = sf::Keyboard::D;
	else if (keyPressed == "KEY_E")
		enumKey = sf::Keyboard::E;
	else if (keyPressed == "KEY_F")
		enumKey = sf::Keyboard::F;
	else if (keyPressed == "KEY_G")
		enumKey = sf::Keyboard::G;
	else if (keyPressed == "KEY_H")
		enumKey = sf::Keyboard::H;
	else if (keyPressed == "KEY_I")
		enumKey = sf::Keyboard::I;
	else if (keyPressed == "KEY_J")
		enumKey = sf::Keyboard::J;
	else if (keyPressed == "KEY_K")
		enumKey = sf::Keyboard::K;
	else if (keyPressed == "KEY_L")
		enumKey = sf::Keyboard::L;
	else if (keyPressed == "KEY_M")
		enumKey = sf::Keyboard::M;
	else if (keyPressed == "KEY_N")
		enumKey = sf::Keyboard::N;
	else if (keyPressed == "KEY_O")
		enumKey = sf::Keyboard::O;
	else if (keyPressed == "KEY_P")
		enumKey = sf::Keyboard::P;
	else if (keyPressed == "KEY_Q")
		enumKey = sf::Keyboard::Q;
	else if (keyPressed == "KEY_R")
		enumKey = sf::Keyboard::R;
	else if (keyPressed == "KEY_S")
		enumKey = sf::Keyboard::S;
	else if (keyPressed == "KEY_T")
		enumKey = sf::Keyboard::T;
	else if (keyPressed == "KEY_U")
		enumKey = sf::Keyboard::U;
	else if (keyPressed == "KEY_V")
		enumKey = sf::Keyboard::V;
	else if (keyPressed == "KEY_W")
		enumKey = sf::Keyboard::W;
	else if (keyPressed == "KEY_X")
		enumKey = sf::Keyboard::X;
	else if (keyPressed == "KEY_Y")
		enumKey = sf::Keyboard::Y;
	else if (keyPressed == "KEY_Z")
		enumKey = sf::Keyboard::Z;
	else if (keyPressed == "KEY_PAD_0")
		enumKey = sf::Keyboard::Numpad0;
	else if (keyPressed == "KEY_PAD_1")
		enumKey = sf::Keyboard::Numpad1;
	else if (keyPressed == "KEY_PAD_2")
		enumKey = sf::Keyboard::Numpad2;
	else if (keyPressed == "KEY_PAD_3")
		enumKey = sf::Keyboard::Numpad3;
	else if (keyPressed == "KEY_PAD_4")
		enumKey = sf::Keyboard::Numpad4;
	else if (keyPressed == "KEY_PAD_5")
		enumKey = sf::Keyboard::Numpad5;
	else if (keyPressed == "KEY_PAD_6")
		enumKey = sf::Keyboard::Numpad6;
	else if (keyPressed == "KEY_PAD_7")
		enumKey = sf::Keyboard::Numpad7;
	else if (keyPressed == "KEY_PAD_8")
		enumKey = sf::Keyboard::Numpad8;
	else if (keyPressed == "KEY_PAD_9")
		enumKey = sf::Keyboard::Numpad9;
	else if (keyPressed == "KEY_PAD_DIVIDE")
		enumKey = sf::Keyboard::Divide;
	else if (keyPressed == "KEY_PAD_MULTIPLY")
		enumKey = sf::Keyboard::Multiply;
	//else if (keyPressed == "KEY_PAD_MINUS")
		//enumKey = sf::Keyboard::Subtract; // !
	//else if (keyPressed == "KEY_PAD_PLUS")
		//enumKey = sf::Keyboard::Add; // !
	//else if (keyPressed == "KEY_PAD_ENTER")
		//enumKey = sf::Keyboard::Enter; // !
	//else if (keyPressed == "KEY_PAD_DECIMAL")
		//enumKey = sf::Keyboard::Dash; // !
	else if (keyPressed == "KEY_LBRACKET")
		enumKey = sf::Keyboard::LBracket;
	else if (keyPressed == "KEY_RBRACKET")
		enumKey = sf::Keyboard::RBracket;
	else if (keyPressed == "KEY_SEMICOLON")
		enumKey = sf::Keyboard::Semicolon;
	//else if (keyPressed == "KEY_APOSTROPHE")
		//enumKey = sf::Keyboard::apost;
	//else if (keyPressed == "KEY_BACKQUOTE")
		//enumKey = sf::Keyboard::backquote;
	else if (keyPressed == "KEY_COMMA")
		enumKey = sf::Keyboard::Comma;
	else if (keyPressed == "KEY_PERIOD")
		enumKey = sf::Keyboard::Period;
	else if (keyPressed == "KEY_SLASH")
		enumKey = sf::Keyboard::Slash;
	else if (keyPressed == "KEY_BACKSLASH")
	enumKey = sf::Keyboard::Backslash;
	//else if (keyPressed == "KEY_MINUS")
	//enumKey = sf::Keyboard::Subtract;
	else if (keyPressed == "KEY_EQUAL")
		enumKey = sf::Keyboard::Equal;
	else if (keyPressed == "KEY_ENTER")
		enumKey = sf::Keyboard::Enter;
	else if (keyPressed == "KEY_SPACE")
		enumKey = sf::Keyboard::Space;
	else if (keyPressed == "KEY_BACKSPACE")
		enumKey = sf::Keyboard::Backspace;
	else if (keyPressed == "KEY_TAB")
		enumKey = sf::Keyboard::Tab;
	else if (keyPressed == "KEY_ESCAPE")
		enumKey = sf::Keyboard::Escape;
	//else if (keyPressed == "")
	//	enumKey = sf::Keyboard::;
	else if (keyPressed == "KEY_F1")
		enumKey = sf::Keyboard::F1;
	else if (keyPressed == "KEY_F2")
		enumKey = sf::Keyboard::F2;
	else if (keyPressed == "KEY_F3")
		enumKey = sf::Keyboard::F3;
	else if (keyPressed == "KEY_F4")
		enumKey = sf::Keyboard::F4;
	else if (keyPressed == "KEY_F5")
		enumKey = sf::Keyboard::F5;
	else if (keyPressed == "KEY_F6")
		enumKey = sf::Keyboard::F6;
	else if (keyPressed == "KEY_F7")
		enumKey = sf::Keyboard::F7;
	else if (keyPressed == "KEY_F8")
		enumKey = sf::Keyboard::F8;
	else if (keyPressed == "KEY_F9")
		enumKey = sf::Keyboard::F9;
	else if (keyPressed == "KEY_F10")
		enumKey = sf::Keyboard::F10;
	else if (keyPressed == "KEY_F11")
		enumKey = sf::Keyboard::F11;
	else if (keyPressed == "KEY_F12")
		enumKey = sf::Keyboard::F12;
	
	// TODO: added more keys

	if (sf::Keyboard::isKeyPressed(enumKey))
		lua_pushboolean(luaState, true);
	else
		lua_pushboolean(luaState, false);

	return 1;
}
