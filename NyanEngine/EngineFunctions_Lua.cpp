#include "stdafx.h"
#include "EngineFunctions_Lua.h"
#include "Engine.h"
#include "Render.h"
#include "SoundManager.h"
#include "Script.h"
#include <any>
#include <Box2D/Box2D.h>

// TODO: Добавить больше методов функций для работы с движком

Script script;

lua_State* luaState = script.Create();

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
	exit(EXIT_SUCCESS);

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
			lua_pushboolean(luaState, false);
		else
		{
			sf::Sprite sprite(texture);
			sprite.setPosition(sf::Vector2f(script.GetArgument<double>(2), script.GetArgument<double>(3)));
			sprite.setScale(sf::Vector2f(script.GetArgument<double>(4), script.GetArgument<double>(5)));

			addAllocator(sprite, texture);
			lua_pushboolean(luaState, true);
		}
	}

	// physics
	/*
	b2PolygonShape shape;
	shape.SetAsBox(sprite.getScale().x, sprite.getScale().y);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(sprite.getPosition().x, sprite.getPosition().y);

	b2Body* bodySprite = physSpace.CreateBody(&bodyDef);
	bodySprite->CreateFixture(&shape, 1);
	bodySprite->SetUserData("sprite");
	*/

	return 1;
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

int createText(lua_State* luaState)
{
	sf::Font font;
	if (!font.loadFromFile(script.GetArgument<char*>(2)))
	{		
		if (!font.loadFromFile(ERROR_FONT))
			lua_pushboolean(luaState, false);
		else
		{
			// push pointer to text
			sf::Text text;
			text.setString(script.GetArgument<char*>(1));
			text.setCharacterSize(script.GetArgument<int>(3));
			text.setPosition(script.GetArgument<double>(4), script.GetArgument<double>(5));
			text.setFillColor(sf::Color::White);
			text.setOutlineColor(sf::Color::Black);
			text.setOutlineThickness(2.0f);
			text.setLineSpacing(1.1f);

			addAllocatorText(text, font);
			lua_pushboolean(luaState, true);
		}
	}

	return 1;
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

int changeCursor(lua_State* luaState)
{
	sf::Cursor cursor;
	sf::Cursor::Type cursorType;

	char* stateCursor = script.GetArgument<char*>(1);

	if (!strcmp(stateCursor, "arrow"))
		cursorType = sf::Cursor::Arrow;
	else if (!strcmp(stateCursor, "waitarrow"))
		cursorType = sf::Cursor::ArrowWait;
	else if (!strcmp(stateCursor, "wait"))
		cursorType = sf::Cursor::Wait;
	else if (!strcmp(stateCursor, "text"))
		cursorType = sf::Cursor::Text;
	else if (!strcmp(stateCursor, "hand"))
		cursorType = sf::Cursor::Hand;
	else if (strcmp(stateCursor, "sizehorizontal"))
		cursorType = sf::Cursor::SizeHorizontal;
	else if (strcmp(stateCursor, "sizevertical"))
		cursorType = sf::Cursor::SizeVertical;
	else if (strcmp(stateCursor, "sizetopleftbottomright"))
		cursorType = sf::Cursor::SizeTopLeftBottomRight;
	else if (strcmp(stateCursor, "sizebottomlefttopright"))
		cursorType = sf::Cursor::SizeBottomLeftTopRight;
	else if (strcmp(stateCursor, "sizeall"))
		cursorType = sf::Cursor::SizeAll;
	else if (strcmp(stateCursor, "cross"))
		cursorType = sf::Cursor::Cross;
	else if (strcmp(stateCursor, "help"))
		cursorType = sf::Cursor::Help;
	else if (strcmp(stateCursor, "notallowed"))
		cursorType = sf::Cursor::NotAllowed;
	else
	{
		// custom cursor
		sf::Image cursorImage;
		if (cursorImage.loadFromFile(stateCursor))
		{
			int hotspotx = script.GetArgument<int>(2);
			int hotspoty = script.GetArgument<int>(3);
			cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(hotspotx , hotspoty));
		}
		else
		{
			lua_pushboolean(luaState, false);
			return 1;
		}
	}

	if (cursor.loadFromSystem(cursorType))
	{
		// TODO: Дай видимость окна блядским функциям из скриптов
		//window.setMouseCursor(cursor);
		lua_pushboolean(luaState, true);
	}
	else
		lua_pushboolean(luaState, false);

	return 1;
}

// sound
int emitSound(lua_State* luaState, int index)
{
	try
	{
		sf::Sound sound = loadSound(script.GetArgument<char*>(1));

		sound.play();
	}
	catch (...)
	{
		lua_pushnil(luaState);
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

int createRecorder(lua_State* luaState)
{
	sf::SoundBufferRecorder recorder;
	recorder.start();

	sf::Clock clock;
	sf::Time elapsed = clock.getElapsedTime();

	// TODO: Checking functiom elapse needs moved in main cycle
	if (elapsed.asSeconds() == script.GetArgument<int>(1))
	{
		recorder.stop();
		clock.restart();
		sf::SoundBuffer buffer = recorder.getBuffer();
		buffer.saveToFile("record.ogg");
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

int isGamepadButtonPressed(lua_State* luaState)
{
	if (sf::Joystick::isConnected(0))
	{
		size_t buttons = sf::Joystick::getButtonCount(0);

		int keyCode = script.GetArgument<int>(1);

		//sf::Joystick::Axis enumKey;

		/*if (keyPressed == "JOYSTICK_POV_X")
			enumKey = sf::Joystick::PovX;
		else if (keyPressed == "JOYSTICK_POV_Y")
			enumKey = sf::Joystick::PovY;
		else if (keyPressed == "JOYSTICK_R")
			enumKey = sf::Joystick::R;
		else if (keyPressed == "JOYSTICK_U")
			enumKey = sf::Joystick::U;
		else if (keyPressed == "JOYSTICK_V")
			enumKey = sf::Joystick::V;
		else if (keyPressed == "JOYSTICK_X")
			enumKey = sf::Joystick::X;
		else if (keyPressed == "JOYSTICK_Y")
			enumKey = sf::Joystick::Y;
		else if (keyPressed == "JOYSTICK_Z")
			enumKey = sf::Joystick::Z;*/

		if (keyCode <= buttons)
		{
			if (sf::Joystick::isButtonPressed(0, keyCode))
			{
				std::cout << "press " << keyCode;
				lua_pushboolean(luaState, true);
			}
			else
				lua_pushboolean(luaState, false);
		}
	}

	return 1;
}
