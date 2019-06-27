#include "stdafx.h"
#include "Console.h"

void initConsole(sf::RenderWindow window)
{
	ImGui::SFML::Init(window);
}

void createConsole(const char* name)
{
	ImGui::Begin(name);
	ImGui::InputText("Window title", "1", 255);
	ImGui::End();
}