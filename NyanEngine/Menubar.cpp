#include "stdafx.h"
#include "Menubar.h"
#include "AssetBrowser.h"

void menubarCreate()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New scene"))
			{
				
			}
			ImGui::MenuItem("Open scene");
			ImGui::MenuItem("Save scene");
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			//if (ImGui::MenuItem("Show/Hide Asset Browser"))
				
				
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("About");
			ImGui::EndMenu();
		}
			
		ImGui::EndMainMenuBar();
	}

	assetBrowserCreate("AssetBrowser");
}