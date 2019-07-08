#pragma once

#include "SoundManager.h"
#include "Dialog.h"

bool InitScene();

class Scene {
public:
	std::string Name;
	size_t Frame;
	std::string Texture;
	std::vector<Dialog> dialogs; // Вектор диалогов
};
