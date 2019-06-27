#include "stdafx.h"
#include "Render.h"
#include "Parser.h"
#include "ErrorLogger.h"
//#include "Script.h"
#include "EngineFunctions_Lua.h"
#include "ScriptRender.h"
#include "Allocator.h"
#include "Engine.h"


extern Settings settings_token;
extern GameSettings game_token;
extern SceneSettings scene_token;

void drawer(sf::RenderWindow& window)
{
	window.clear();

	for (auto &s : mapSpriteTexture)
	{
		s.first.setTexture(s.second);

		window.draw(s.first);
	}

	window.display();
}

size_t renderDeviceSFML()
{
	/*
	if (NULL == settings_token.w || NULL == settings_token.h || NULL == settings_token.vsync || NULL == settings_token.frameratemax) {
		addLogFile("[ERROR] No configuration values found. Check the .cfg files!");
		return ERROR_FILE;
	}
	*/
	sf::RenderWindow window(sf::VideoMode(settings_token.w, settings_token.h), game_token.namewindow, sf::Style::Fullscreen);//sf::Style::Titlebar | sf::Style::Close);
	sf::RenderWindow* ptrw = &window;
    window.setVerticalSyncEnabled(settings_token.vsync);
	window.setFramerateLimit(settings_token.frameratemax);

	/*
	cout << settings_token.w;
	cout << settings_token.h;
	cout << game_token.namewindow;
	*/

	/* Test render */
	//sf::Texture texture;
	//if (!texture.loadFromFile("content/textures/1.gif")) {
	//	if (!texture.loadFromFile("content/textures/null.jpg"))
	//	return ERROR_LOAD;
	//}
	
	//sf::Sprite sprite(texture);
	//sprite.setScale(sf::Vector2f(1.3f, 1.5f));
	//texture.setSmooth(true); //antialiasing
	//addAllocator(sprite);

	//sf::Font font;
	//if (!font.loadFromFile("content/fonts/arial.ttf"))
	//	return ERROR_LOAD;

	//sf::Text text(L"Привет, давай понякаемся!", font, 50);
	//text.setString(L"Привет, давай понякаемся!");
	//text.setPosition(250, 700);
	//text.setFillColor(sf::Color::Cyan);
	//addAllocator(text);

	// Load a music to play
	//sf::Music music;
	//if (!music.openFromFile("content/sounds/musics/opening.ogg"))
	//	return ERROR_LOAD;
	// Play the music
	//music.play();
	
	

	//Script render
	script.Create();
	script.RegisterConstant<lua_CFunction>(Write, "Write");
	script.RegisterConstant<lua_CFunction>(CreatePerson, "CreatePerson");
	script.RegisterConstant<lua_CFunction>(SetBackground, "SetBackground");
	//script.RegisterConstant<lua_CFunction>(CreateBox, "CreateBox");
	script.RegisterConstant<lua_CFunction>(SetColorSpace, "SetColorSpace");
	script.DoFile("render.lua");
	script.Close();
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
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				return 1;
			}
				
		}

		drawer(window);

		//window.clear();
		// TODO: Возрат указателя на объект из renderScene для отрисовки в renderDeviceSFML или создать отдельную функцию для отрисовки
		//window.draw(sprite);
		//drawerScript(ptrw);
		//cout << pullerAllocator() << endl;
		//window.draw(sprite);
		//window.draw(spaceFunction(sprite));
		//window.draw(sprite);
		//window.draw(text);
		//window.draw(spr);

		//window.display();
	}
	
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
