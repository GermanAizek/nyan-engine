#include "stdafx.h"
#include "Render.h"
#include "Parser.h"
#include "ErrorLogger.h"
//#include "Script.h"
#include "EngineFunctions_Lua.h"
#include "ScriptRender.h"
#include "Engine.h"
#include "Console.h"

extern Settings settings_token;
extern GameSettings game_token;
extern SceneSettings scene_token;

void addAllocator(sf::Sprite& sprite, sf::Texture& texture)
{
	mapAllocator.push_back(std::pair<sf::Sprite, sf::Texture>(sprite, texture));
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

	//sf::Text text(L"Привет, давай понякаемся!", font, 50);
	//text.setString(L"Привет, давай понякаемся!");
	//text.setPosition(250, 700);
	//text.setFillColor(sf::Color::Cyan);

	// Load a music to play
	//sf::Music music;
	//if (!music.openFromFile("content/sounds/musics/opening.ogg"))
	//	return ERROR_LOAD;
	// Play the music
	//music.play();
	
	

	// create thread main drawer
	std::thread threadDraw([]() {
		script.Create();
		// constants
		script.RegisterConstant<lua_CFunction>(getScreenWidth, "ScrW");
		script.RegisterConstant<lua_CFunction>(getScreenHeight, "ScrH");
		// console
		script.RegisterConstant<lua_CFunction>(PrintConsole, "Msg");
		// graphics
		script.RegisterConstant<lua_CFunction>(CreateSprite, "AddSprite");
		//script.RegisterConstant<lua_CFunction>(setupFont, "SetFont");
		script.RegisterConstant<lua_CFunction>(CreateText, "AddText");
		script.RegisterConstant<lua_CFunction>(SetBackground, "SetBackground");
		script.DoFile("content//scripts//render.lua");
		script.Close();
	});

	threadDraw.join();

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
		while (window.pollEvent(GameEvent))
		{
			ImGui::SFML::ProcessEvent(GameEvent);

			if (GameEvent.type == sf::Event::Closed) {
				// shutdown render window
				window.close();
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
