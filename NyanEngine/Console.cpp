#include "stdafx.h"
#include "Console.h"

void consoleCreate(std::string_view name)
{
	ImGui::Begin(name.data());
	ImGui::SetWindowPos(name.data(), ImVec2(0, 0));
	ImGui::SetWindowSize(name.data(), ImVec2(WIDTH, HEIGHT * 0.18));
	ImGui::InputTextMultiline("", const_cast<char*>(consoleLine.c_str()), 4096, ImVec2(WIDTH, HEIGHT * 0.1), ImGuiInputTextFlags_ReadOnly);
	ImGui::InputText("", const_cast<char*>(commandLine.c_str()), 1024, ImGuiInputTextFlags_AlwaysInsertMode);

	consoleHandler();

	ImGui::End();
}

void printConsole(std::string_view text)
{
	consoleLine += text.data() + '\n';
}

size_t consoleHandler()
{
	if (ImGui::Button("Run")) {
		consoleLine += "> " + commandLine + '\n';

		if (commandLine == "help")
		{
			consoleLine += "Nyan Engine\nDevelopers:\nHerman Semenov (GermanAizek)";
		}
		else if (commandLine == "clear")
		{
			consoleLine.clear();
		}
		else if (commandLine == "videomode")
		{

		}

		commandLine.clear();
	}

	return 0;
}