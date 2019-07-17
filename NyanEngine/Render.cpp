#include "stdafx.h"
#include "Render.h"
#include "Parser.h"
#include "ErrorLogger.h"
//#include "Script.h"
#include "EngineFunctions_Lua.h"
#include "Engine.h"
#include "Console.h"
#include <mutex>
#include <sstream>


extern Settings settings_token;
extern GameSettings game_token;
extern SceneSettings scene_token;

std::mutex threadMutex;
std::vector<std::exception_ptr> exceptions;

int startScript(std::string nameFile)
{
	std::stringstream currentPath;
	currentPath << "content//scripts//" << nameFile;

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
		// console
		script.RegisterConstant<lua_CFunction>(printConsole, "Msg");
		// sounds
		script.RegisterConstant<lua_CFunction>(emitSound, "EmitSound");
		script.RegisterConstant<lua_CFunction>(emitMusic, "EmitMusic");
		// graphics
		script.Array();
		script.RegisterFieldGlobal<lua_CFunction>(createSprite, "DrawSprite");
		script.RegisterArray("render");

		script.Array();
		//script.RegisterFieldGlobal<lua_EngineText>(createText, "DrawText");
		script.RegisterFieldGlobal<lua_CFunction>(setBackground, "DrawBackground");
		script.RegisterArray("draw");

		script.Array();
		script.RegisterFieldGlobal<lua_CFunction>(isMouseButtonPressed, "IsMouseDown");
		script.RegisterFieldGlobal<lua_CFunction>(isKeyboardButtonPressed, "IsKeyDown");
		script.RegisterArray("input");

		int luaScript = script.DoFile(currentPath.str().c_str());
		reportErrors(luaState, luaScript);
	}
	catch (...)
	{
		std::lock_guard<std::mutex> lock(threadMutex);
		exceptions.push_back(std::current_exception());
	
		return 1;
	}

	return 0;
}

int connectToScript(std::string nameFile, Script& script)
{
	std::stringstream currentPath;
	currentPath << "content//scripts//" << nameFile;

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

void addAllocator(sf::Sprite& sprite, sf::Texture& texture)
{
	mapAllocator.push_back(std::pair<sf::Sprite, sf::Texture>(sprite, texture));
}

void addAllocatorSound(sf::Sound& sound)
{
	mapAllocatorSound.push_back(sound);
}

void addAllocatorText(sf::Text& text, sf::Font& font)
{
	mapAllocatorText.push_back(std::pair<sf::Text, sf::Font>(text, font));
}

void drawer(sf::RenderWindow& window, sf::Clock dt)
{
	window.clear();

	for (auto& sprite : mapAllocator)
	{
		sprite.first.setTexture(sprite.second);
		window.draw(sprite.first);
	}

	for (auto& text : mapAllocatorText)
	{
		text.first.setFont(text.second);
		window.draw(text.first);
	}


	for (auto& sound : mapAllocatorSound)
	{
		sound.play();
	}

	ImGui::SFML::Update(window, dt.restart());
	consoleCreate("Console");
	ImGui::SFML::Render(window);

	window.display();
}

size_t renderDeviceSFML()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "build", sf::Style::Fullscreen);
	ImGui::SFML::Init(window);
    window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	// create thread init drawer
	
	exceptions.clear();

	std::thread threadInit(startScript, "init.lua");
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
			std::cout << error.what() << std::endl;
		}
	}
	
	/*
	sf::Texture texture2;
	if (!texture2.loadFromFile("content/textures/null.jpg", sf::IntRect(100, 100, 500, 500)))
	{
		cout << "1";
	}
	sf::Sprite spr(texture2);

	//loadSetTextureSprite(m_sprite,"content/textures/1.jpg");
	/*
	// Console
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde)){
		sf::Texture texture;
		if (!texture.loadFromFile("ontent/textures/ui/console.jpg", sf::IntRect(100, 30, 300, 50))) {
			cout << "[ERROR] Console not create!\n";
		}
	}
	//
	*/
	
	//sf::Sprite sprite(pullerAllocator());
	
	sf::Clock dt;
	while (window.isOpen())
	{
		sf::Event GameEvent;
		if (window.pollEvent(GameEvent))
		{
			// create thread think drawer
			exceptions.clear();

			std::thread threadThink(connectToScript, "think.lua", script);
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
					std::cout << error.what() << std::endl;
				}
			}
			//

			ImGui::SFML::ProcessEvent(GameEvent);

			if (GameEvent.type == sf::Event::Closed || Core::criticalError) {
				// shutdown render window
				window.close();
				// shutdown script exec
				script.Close();

				return 1;
			}
		}

		drawer(window, dt);
	}

	ImGui::SFML::Shutdown();
	
	return true;
}

void renderScene()
{
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);

	// Load a sprite to display
	sf::Texture texture;
	if (!texture.loadFromFile("content/textures/1.jpg"))
		return;

	sf::Sprite sprite(texture);
	// Create a graphical text to display
	//sf::Font font;
	//if (!font.loadFromFile("arial.ttf"))
	//	return;
	//sf::Text text("Nyan", font, 50);
}

void loadSetTextureSprite(sf::Sprite sprite, std::string texture)
{
	sf::Texture obj_texture;
	if(!obj_texture.loadFromFile(texture))
	{
		//cout << "[ERROR} Cannot load texture! " << texture << "\n";
		addLogFile("[ERROR} Cannot load texture! " + texture);
		return;
	}
	
    sprite.setTexture(obj_texture);

	/*
	if (!m_texture.loadFromFile("Textures/1.jpg")){
	cout << "[ERROR} Cannot load texture! " <<  << "\n"; 
	return false;
	}
    	m_sprite.setTexture(m_texture);
	*/
}
