#include "stdafx.h"
#include "Allocator.h"
#include "Engine.h"
//#include "Render.h"

// TODO: Аллокатор выделяет память под используемые для отрисовки объектов, сделай с начала для спрайтов

//bool debugmode = false;
//extern std::vector<sf::Sprite> vectorSprites(10);

size_t initAllocator() {
	std::cout << "Initialize allocator...\n";
	//std::vector<sf::Texture/* sf::Sprite* */> vectorSprites(10);

}

size_t addAllocator(sf::Sprite &sprite, sf::Texture &texture) {

	mapSpriteTexture.push_back(std::pair<sf::Sprite, sf::Texture>(sprite, texture));

	//vectorSprites.push_back(sprite);

	//std::cout << "Vector size:" << vectorSprites.size() << "\n";

	//vectorTextures.push_back(texture);

	//std::cout << "Vector size:" << vectorTextures.size() << "\n";
	
	return 0;
}

//sf::Sprite pullerAllocator() {
//	for ( auto &p : vectorSprites ) {
//		std::cout << "Pull element " << &p <<  "...\n";
//		return p;
//	}
//}

//sf::Sprite spaceFunction(const sf::Sprite &ptr)
//{
//	std::cout << "Pull element ";
//	return ptr;
//}
