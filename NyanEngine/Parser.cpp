#include "stdafx.h"
#include "Parser.h"
#include "ErrorLogger.h"
#include "Engine.h"

#include <json.hpp>
using json = nlohmann::json;

json j2 = {
	{ "pi", 3.141 },
	{ "happy", true },
	{ "name", "Niels" },
	{ "nothing", nullptr },
	{ "answer",{
		{ "everything", 42 }
	} },
	{ "list",{ 1, 0, 2 } },
	{ "object",{
		{ "currency", "USD" },
		{ "value", 42.99 }
	} }
};

//// read a JSON file
//ifstream in("file.json", ios_base::binary);
//in >> j2;
//
//// write prettified JSON to another file
//ofstream out("pretty.json", ios_base::binary);
//out << std::setw(4) << j2 << std::endl;

extern Settings settings_token;

// HACK: Перестал печатать если он пустой или его нет. При целостности считывать.
bool parseSettings() {
	std::ifstream settings("settings.cfg", std::ios_base::app | std::ios_base::binary);
	std::string tmp,temp;
	getline(settings, temp);

	if (settings.is_open()){
		addLogFile("[Engine] Parsing settings.cfg...");
		for (size_t i = 0; i<2; ++i) settings >> tmp; settings >> settings_token.w;// width
		for (size_t i = 0; i<2; ++i) settings >> tmp; settings >> settings_token.h;// height
		for (size_t i = 0; i<2; ++i) settings >> tmp; settings >> settings_token.vsync;// vsync
		for (size_t i = 0; i<2; ++i) settings >> tmp; settings >> settings_token.windowed;// windowed
		for (size_t i = 0; i<2; ++i) settings >> tmp; settings >> settings_token.frameratemax;// frameratemax
		settings.close();
	}
	else if (settings.eof() && temp.empty()) {
		addLogFile("[ERROR] settings.cfg not find!");
		std::cout << "[AUTOFIX] Recovering a file settings.cfg ...\n";

		std::ofstream settings("settings.cfg", std::ios_base::app | std::ios_base::binary);
		settings << "width = " << settings_token.w << "\n";// width
		settings << "height = " << settings_token.h << "\n";// height
		settings << "vsync = " << settings_token.vsync << "\n";// vsync
		settings << "windowed = " << settings_token.windowed << "\n";// windowed
		settings << "frameratemax = " << settings_token.frameratemax << "\n";// frameratemax
		settings << "devgameinconfig = " << settings_token.devconfig << "\n";// devgameinconfig
		settings.close();

		std::cout << "[AUTOFIX] File settings.cfg restored!\n";
		//system("nyanengine.exe");
		//exit(EXIT_SUCCESS);
		return false;
	}

	// Recovering
	//if (NULL == settings_token.w) settings_token.w = 1024;
	//if (NULL == settings_token.h) settings_token.w = 768;
	return true;
}
