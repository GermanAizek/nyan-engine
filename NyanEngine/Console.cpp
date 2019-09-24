#include "stdafx.h"
#include "Console.h"
#include "Engine.h"

int CLB(ImGuiTextEditCallbackData* data)
{

	float controlWidth = *(float*)data->UserData,
		textWidth = ImGui::CalcTextSize(data->Buf).x;

	if (controlWidth <= textWidth)
	{
		data->InsertChars(data->CursorPos - 1, "\n");
		data->BufDirty = true;
	}

	return data->BufTextLen;
}

void consoleCreate(std::string_view name)
{
	ImGui::Begin(name.data());

	ImVec2 min = ImGui::GetWindowContentRegionMin();
	ImVec2 max = ImGui::GetWindowContentRegionMax();
	max.x = (max.x - min.x);
	max.y -= min.y + ImGui::GetItemsLineHeightWithSpacing() * 3;

	float w = ImGui::CalcItemWidth();
	ImGui::InputTextMultiline("", const_cast<char*>(consoleLine.c_str()), (size_t)consoleLine.size(), max, ImGuiInputTextFlags_CallbackAlways, CLB, &(w));
	ImGui::InputText("", const_cast<char*>(commandLine.c_str()), (size_t)commandLine.size());

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
		ImGui::SameLine();
		consoleLine += "> " + commandLine + '\n';

		if (commandLine == "help")
			consoleLine += "Nyan Engine\nDevelopers:\nHerman Semenov (GermanAizek)";
		else if (commandLine == "clear")
			consoleLine.clear();
		else if (commandLine == "videomode")
		{

		}
		else if (commandLine == "stats")
			EngineEvent::showStats = true;
		else
			consoleLine += "[ERROR] '" + commandLine + "' command not found!";

		commandLine.clear();
	}

	return 0;
}