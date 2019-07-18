#include "stdafx.h"
#include "Console.h"

void consoleCreate(const char* name)
{
	ImGui::Begin(name);
	ImGui::SetWindowPos(name, ImVec2(0, 0));
	ImGui::SetWindowSize(name, ImVec2(WIDTH, (float)(HEIGHT * 0.18)));
	ImGui::InputTextMultiline("", "Console", 255);
	ImGui::InputText("", "", 255);

	if (ImGui::Button("Run")) {
		//window.setTitle(windowTitle);
	}

	ImGui::End();
}

size_t consoleHandler()
{
	
}