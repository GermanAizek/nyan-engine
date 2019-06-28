#include "stdafx.h"
#include "Console.h"

void consoleCreate(const char* name)
{
	ImGui::Begin(name);
	ImGui::InputTextMultiline("", "test console", HEIGHT >> 2);
	ImGui::InputText("", "", 255);

	if (ImGui::Button("Run")) {
		//window.setTitle(windowTitle);
	}

	ImGui::End();
}

size_t consoleHandler()
{
	
}