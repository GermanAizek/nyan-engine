#include "stdafx.h"
#include "Render.h"
#include "Parser.h"
#include "ErrorLogger.h"
//#include "Script.h"
#include "EngineFunctions_Lua.h"
#include "Engine.h"
#include "Console.h"
#include "Menubar.h"
#include "Grid.h"
#include "Monitor.h"
#include "Texture.h"
#include <mutex>
#include <sstream>

extern Settings settings_token;

std::vector<std::pair<sf::Sprite, Nyan::Texture>> mapAllocator;
std::vector<sf::Text/*std::pair<sf::Text, sf::Font>*/> mapAllocatorText;
std::vector<sf::Sound> mapAllocatorSound;

std::mutex threadMutex;
std::vector<std::exception_ptr> exceptions;

int startScript(std::string_view nameFile)
{
	std::stringstream currentPath;
	currentPath << nameFile;

	try
	{
		lua_State* luaState = script.Create();

		// global tables
		script.Array();
		script.RegisterArray("_G");
		script.Array();
		script.RegisterArray("_MODULES");

		/* create the proxy metatable */
		//luaL_newmetatable(luaState, "proxy");
		//lua_pushcfunction(luaState, proxy);
		//lua_setfield(luaState, -2, "__call");

		/* set the global function that returns the proxy */
		//lua_pushcfunction(luaState, getproxy);
		//lua_setglobal(luaState, "getproxy");

		// system
		script.RegisterConstant<lua_CFunction>(assertExpression, "assert");
		script.RegisterConstant<lua_CFunction>(exitApplication, "exit");
		script.RegisterConstant<lua_CFunction>(runScript, "RunScript");
		//script.RegisterConstant<lua_CFunction>(color, "Color");
		script.RegisterConstant<lua_CFunction>(getCurrentTime, "CurTime");
		script.RegisterConstant<lua_CFunction>(getSystemTime, "SysTime");
		// constants
		script.RegisterConstant<lua_CFunction>(getScreenWidth, "ScrW");
		script.RegisterConstant<lua_CFunction>(getScreenHeight, "ScrH");
		script.RegisterConstant<lua_CFunction>(getScaleTextureFullscreen, "GetScaleTextureFullscreen");
		// console
		script.RegisterConstant<lua_CFunction>(printConsole, "Msg");
		// sounds
		//script.RegisterConstant<lua_CFunction>(soundPlay, "play"); // non work
		script.RegisterConstant<lua_CFunction>(emitMusic, "EmitMusic"); // non work
		script.RegisterConstant<lua_CFunction>(createRecorder, "CreateRecorder"); // non work
		
		// graphics
		script.RegisterConstant<lua_CFunction>(createSprite, "createSprite");
		//script.RegisterFieldGlobal<lua_CFunction>(setVerticalSync, "SetVSync");
		script.RegisterConstant<lua_CFunction>(changeCursor, "changeCursor"); // non work

		script.RegisterConstant<lua_CFunction>(createText, "createText");
		//script.RegisterFieldGlobal<lua_CFunction>(setBackground, "DrawBackground");

		script.RegisterConstant<lua_CFunction>(isMouseButtonPressed, "mouseButtonPressed");
		script.RegisterConstant<lua_CFunction>(isKeyboardButtonPressed, "keyboardButtonPressed");
		script.RegisterConstant<lua_CFunction>(isGamepadButtonPressed, "gamepadButtonPressed"); // beta

		script.DoFile(currentPath.str().c_str());
	}
	catch (...)
	{
		std::lock_guard<std::mutex> lock(threadMutex);
		exceptions.push_back(std::current_exception());
	
		return 1;
	}

	return 0;
}

int connectToScript(std::string_view nameFile, Script& script)
{
	std::stringstream currentPath;
	currentPath << nameFile;

	try
	{
		script.DoFile(currentPath.str().c_str());
		//reportErrors(luaState, luaScript);
	}
	catch (...)
	{
		std::lock_guard<std::mutex> lock(threadMutex);
		exceptions.push_back(std::current_exception());

		return 1;
	}

	return 0;
}

void addAllocator(sf::Sprite& sprite, Nyan::Texture& texture)
{
	mapAllocator.push_back(std::pair<sf::Sprite, Nyan::Texture>(sprite, texture));
}

void addAllocatorSound(sf::Sound& sound)
{
	mapAllocatorSound.push_back(sound);
}

void addAllocatorText(sf::Text text, sf::Font font)
{
	mapAllocatorText.push_back(text/*std::pair<sf::Text, sf::Font>(text, font)*/);
}

void drawer(sf::RenderWindow& window, sf::FloatRect& view, sf::Clock dt)
{
	window.clear();

	for (auto& sprite : mapAllocator)
	{
		if (sprite.first.getGlobalBounds().intersects(view))
		{
			sprite.first.setTexture(sprite.second.get());

			// physics
			/*
			for (b2Body* it = physSpace.GetBodyList(); it != 0; it = it->GetNext())
			{
				if (it->GetUserData() == "sprite")
				{
					b2Vec2 pos = it->GetPosition();
					float angle = it->GetAngle();
					sprite.first.setPosition(pos.x, pos.y);
					sprite.first.setRotation(angle);
				}
			}
			*/

			window.draw(sprite.first);
		}
	}

	

	for (auto& text : mapAllocatorText)
	{
		sf::Text queueText = text;//.first;
		queueText.setFillColor(sf::Color::White);
		queueText.setOutlineColor(sf::Color::Black);
		queueText.setOutlineThickness(2.0f);
		queueText.setLineSpacing(1.1f);
		// test font
		sf::Font font;
		if (!font.loadFromFile("content/fonts/arial.ttf"))
		{
			// error
		}
		//
		queueText.setFont(font); // text.second
		window.draw(queueText);
	}

	for (auto& sound : mapAllocatorSound)
	{
		sound.play();
	}

	ImGui::SFML::Update(window, dt.restart());

	// GUI elements
	if (EngineEvent::showEditor)
	{
		Nyan::Grid grid(10, 10, &window);
		menubarCreate();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde))
		consoleOpened ? consoleOpened = false : consoleOpened = true;

	if (consoleOpened)
		consoleCreate("Console");

	ImGui::SFML::Render(window);

	// GUI system elements
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
		statsOpened ? statsOpened = false : statsOpened = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
		EngineEvent::showEditor ? EngineEvent::showEditor = false : EngineEvent::showEditor = true;

	if (statsOpened)
		statsHandler(window, getFPS(dt.restart()));

	window.display();
}

size_t renderDeviceSFML()
{
	/*
	for (auto& mode : sf::VideoMode::getFullscreenModes())
	{
		std::cout << mode.bitsPerPixel << mode.width << mode.width << '\n';
	}
	*/

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "nyan engine", sf::Style::Fullscreen);
	window.setSize(sf::Vector2u(WIDTH, HEIGHT));
	window.setActive(true);
	window.setFramerateLimit(120);
	window.setVerticalSyncEnabled(true);
	//window.setIcon(64, 64, icon);
	ImGui::SFML::Init(window);

	sf::Vector2f viewCenter(window.getView().getCenter());
	sf::Vector2f viewSize(window.getView().getSize());

	sf::FloatRect currentViewRect(viewCenter - viewSize / 2.f, viewSize);
	
	if (!EngineEvent::showEditor)
	{
		// create thread init drawer
		exceptions.clear();

		std::thread threadInit(startScript, "content//scripts//init.lua");
		threadInit.join();

		for (auto& error : exceptions)
		{
			try
			{
				if (error != nullptr)
					std::rethrow_exception(error);
			}
			catch (const std::exception& error)
			{
				addLogFile(error.what());
			}
		}
	}
	else
	{
		Nyan::Texture back("content/textures/system/editor_background.jpg");
		sf::Texture texture(back.get());
		texture.setSmooth(true);
		texture.setRepeated(true);

		sf::Sprite backgroundEditor;
		backgroundEditor.setTexture(texture);
		backgroundEditor.setTextureRect({ 0, 0, (int)WIDTH, (int)HEIGHT });
		addAllocator(backgroundEditor, back);
	}
	
	sf::Clock dt;
	while (window.isOpen())
	{
		sf::Event GameEvent;
		if (window.pollEvent(GameEvent))
		{
			if (!EngineEvent::showEditor)
			{
				// create thread think drawer
				exceptions.clear();

				std::thread threadThink(connectToScript, "content//scripts//think.lua", script);
				threadThink.join();

				for (auto& error : exceptions)
				{
					try
					{
						if (error != nullptr)
							std::rethrow_exception(error);
					}
					catch (const std::exception& error)
					{
						addLogFile(error.what());
					}
				}
				//
			}

			ImGui::SFML::ProcessEvent(GameEvent);

			if (GameEvent.type == sf::Event::Closed || Core::criticalError) {
				// shutdown render window
				window.close();
				// shutdown script exec
				script.Close();

				return 1;
			}
		}

		drawer(window, currentViewRect, dt);
	}

	ImGui::SFML::Shutdown();
	
	return true;
}
