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
extern GameSettings game_token;
extern SceneSettings scene_token;
// HACK: Перестал печатать если он пустой или его нет. При целостности считывать.
bool parseSettings() {
	ifstream settings("settings.cfg", ios_base::app | ios_base::binary);
	string tmp,temp;
	getline(settings, temp);

	if (settings.is_open()){
		addLogFile("[Engine] Parsing settings.cfg...");
		for (size_t i = 0; i<2; ++i) settings >> tmp; settings >> settings_token.renderer;// render
		for (size_t i = 0; i<2; ++i) settings >> tmp; settings >> settings_token.w;// width
		for (size_t i = 0; i<2; ++i) settings >> tmp; settings >> settings_token.h;// height
		for (size_t i = 0; i<2; ++i) settings >> tmp; settings >> settings_token.vsync;// vsync
		for (size_t i = 0; i<2; ++i) settings >> tmp; settings >> settings_token.windowed;// windowed
		for (size_t i = 0; i<2; ++i) settings >> tmp; settings >> settings_token.frameratemax;// frameratemax
		settings.close();
	}
	else if (settings.eof() && temp.empty()) {
		addLogFile("[ERROR] settings.cfg not find!");
		cout << "[AUTOFIX] Recovering a file settings.cfg ...\n";

		ofstream settings("settings.cfg", ios_base::app | ios_base::binary);
		settings << "renderer = " << settings_token.renderer << "\n";// width
		settings << "width = " << settings_token.w << "\n";// width
		settings << "height = " << settings_token.h << "\n";// height
		settings << "vsync = " << settings_token.vsync << "\n";// vsync
		settings << "windowed = " << settings_token.windowed << "\n";// windowed
		settings << "frameratemax = " << settings_token.frameratemax << "\n";// frameratemax
		settings << "devgameinconfig = " << settings_token.devconfig << "\n";// devgameinconfig
		settings.close();

		cout << "[AUTOFIX] File settings.cfg restored!\n";
		//system("nyanengine.exe");
		//exit(EXIT_SUCCESS);
		return false;
	}

	if (true == settings_token.devconfig) {
		cout << "[Engine] Activated devmode in config file 'game.dat'!\n";
		parseGame();
	}

	cout << "TEST SETTINGS:" << settings_token.renderer << endl;
	// Recovering
	//if (NULL == settings_token.w) settings_token.w = 1024;
	//if (NULL == settings_token.h) settings_token.w = 768;
	return true;
}

bool parseGame() {
	std::ifstream game("game.dat", ios_base::app | ios_base::binary);
	std::string tmp;//,temp;
	//getline(game, temp);

	if (game.is_open()){
		for (size_t i = 0; i<2; ++i) game >> tmp; game >> game_token.namewindow;// namewindow
		for (size_t i = 0; i<2; ++i) game >> tmp; game >> game_token.countscenes;// scenes
		game.close();
	}
	else {
		addLogFile("[ERROR] game.dat not find!");
		return false;
	}
	/*
	else if (game.eof() && temp.empty()) {
		addLogFile("[ERROR] game.dat not find!");
		cout << "[AUTOFIX] Recovering a file game.dat ...\n";

		ofstream game("game.dat", ios_base::app);
		game << "namewindow = " << game_token.namewindow << "\n";// namewindow
		game << "scenes = " << game_token.countscenes << "\n";// scenes
		game.close();

		cout << "[AUTOFIX] File game.cfg restored!\n";
		//system("nyanengine.exe");
		//exit(EXIT_SUCCESS);
		return false;
	}
	*/
	return true;
}

bool parseScene() {
	ifstream scenes("main.scene", ios_base::app | ios_base::binary);

	json j;
	if (scenes.is_open()) {
		addLogFile("[Engine] Parsing scenes...");
		scenes >> j;
		scenes.close();
	}

	cout << std::setw(4) << j << std::endl;
	
	// TODO: Переделай парсинг файлов сцен под json
	double x, y, z;

	if (scenes.is_open()) {
		addLogFile("[Engine] Parsing scenes...");
		scenes >> scene_token.namescene;// name
		scenes >> scene_token.count_obj;// count
		for (size_t i = 0; i < scene_token.count_obj; i++) {
			//scenes >> glm::to_string(scene_token.coordinatesObj[i]);// coords objects
			scenes >> x; scenes >> y; scenes >> z;
			scene_token.coordinatesObj[i] = glm::vec3(x,y,z);
		}
		scenes.close();
	}
	else if (scenes.eof()) {
		addLogFile("[ERROR] Scenes not find!");
		//system("nyanengine.exe");
		exit(EXIT_SUCCESS);
		return false;
	}
	//

	if (Core::debugmode) {
		cout << scene_token.namescene << "\n";
		for (size_t i = 0; i < scene_token.count_obj; i++) cout << "pos[" << i << "] = " << glm::to_string(scene_token.coordinatesObj[i]) << "\n";// debug out
	}

	return true;
}