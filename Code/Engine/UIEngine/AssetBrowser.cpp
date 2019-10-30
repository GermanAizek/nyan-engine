#include "stdafx.h"
#include "AssetBrowser.h"

void assetBrowserCreate(std::string_view name)
{
	ImGui::Begin(name.data(), NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

	ImGui::SetWindowPos(name.data(), { 0, (float)HEIGHT / 1.5f });
	ImGui::SetWindowSize(name.data(), { (float)WIDTH, (float)HEIGHT / 3.0f });

	sf::Texture textu;
	textu.loadFromFile("content/textures/system/editor_background.jpg");
	sf::Sprite sprite(textu);
	ImGui::ImageButton(sprite, { 128.0f, 128.0f });

	Nyan::Texture texture("content/textures/actor.png");
	if (ImGui::ImageButton(texture.get(), { 128.0f, 128.0f }))
	{
		Nyan::Texture texture("content/textures/mouse.png");
		sf::Sprite sprite(texture.get());
		sprite.setPosition(200, 200);
		sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
		addAllocator(sprite, texture);
	}

	ImGui::End();
}