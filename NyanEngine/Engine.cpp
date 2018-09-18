#include "Engine.h"
#include "Scene.h"
#include "Render.h"
#include "Parser.h"
#include "ErrorLogger.h"
#include "ThreadManager.h"
//#include "Script.h"
#include "EngineFunctions_Lua.h"

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") // Скрыть консоль

Settings settings_token;
GameSettings game_token;
SceneSettings scene_token;

size_t initEngine(){
	addLogFile("Initializing engine...");
	//addThread(&parseGame);
	// TODO: Посмотреть аниме

	// HACK: Должен проверять наличие всех файлов
	bool dir = /*(checkDir("content/textures/1.jpg") &&*/ checkDir("user/nyan.log");

	/*
	if (checkDir("content//")) cout << "cont";
	if (checkDir("user//")) cout << "user";
	if (dir) cout << "dir";
	if (parseSettings) cout << "ParsSet";
	if (parseGame) cout << "ParsGam";
	if (InitScene) cout << "InitScene";
	*/
		//sf::Thread thread(&parseSettings);
		//sf::Thread thread1(&InitScene);
		//thread.launch();
		//thread1.launch();

	if (dir && parseSettings() && InitScene()) {
		addLogFile("Engine is initialized!");
		addLogFile("Parsing file scene!");

		//parseScene(); раскомментить обязательно

		addLogFile("Start rendering!");
		
		cout << "TEST SETTINGS:" << settings_token.renderer << endl;

		if (settings_token.renderer != "vulkan") {
			addLogFile("[ERROR] Render type is not selected!");
			addLogFile("[ERROR] The default is: SFML");

			if (Core::vulkanmode)
				settings_token.renderer = "vulkan";
			else
				settings_token.renderer = "sfml";
		}

		if (settings_token.renderer == "sfml" || settings_token.renderer == "SFML") { // Renderer SFML
			switch (renderDeviceSFML()) {
			case ERROR_FILE:
				addLogFile("[ERROR] No configuration values found. Check the .cfg files!");
				Core::criticalError = true;
				break;
			case ERROR_LOAD:
				addLogFile("[ERROR] Error loading file for rendering!");
				//Core::criticalError = true;
				break;
			default: addLogFile("[GERMAN] I fucking, but you do not have mistakes!");
			}
		} else if (settings_token.renderer == "vulkan" || settings_token.renderer == "VULKAN") { // Renderer Vulkan API
			renderDeviceVulkan();
			system("pause");
			//switch (renderDeviceVulkan()) {
			////case ERROR_FILE:
			////	addLogFile("[ERROR] No configuration values found. Check the .cfg files!");
			////	Core::criticalError = true;
			////	break;
			//case ERROR_LOAD:
			//	addLogFile("[ERROR] Error loading file for rendering!");
			//	//Core::criticalError = true;
			//	break;
			//default: addLogFile("[GERMAN] I fucking, but you do not have mistakes!");
			//}
		}
		else if (settings_token.renderer == "falcor" || settings_token.renderer == "FALCOR") { // Renderer Falcor Framework
			renderDeviceFalcor();
			system("pause");
		}

	}
	else if (false == dir) {
		addLogFile("[ERROR] Check content path!");
		Core::criticalError = true;
	}
	else {
		addLogFile("[ERROR] Check configuration files for errors!");
		Core::criticalError = true;
	}

	if (Core::criticalError) {
		addLogFile("[CRITICAL_ERROR] Engine noticed critical errors, check the log!");
		system("pause");
	}

	return EXIT_SUCCESS;
}

int main(size_t argc, char* argv[]){
	ios_base::sync_with_stdio(0);
	system("title Engine log");

	#pragma omp for
	for (int i = 1; i < argc; ++i){
		cout << "Start parameter used: " << argv[i] << "\n";
		if (!strcmp(argv[i], "/bench")){
			addLogFile("Benchmark mode on!");
			Core::benchmode = true;
		}

		if (!strcmp(argv[i], "/debug")){
			addLogFile("Debug mode on!");
			Core::debugmode = true;
		}

		if (!strcmp(argv[i], "/vulkan")) {
			addLogFile("Vulkan API enable!");
			settings_token.renderer = "vulkan";
			Core::vulkanmode = true;
		}
	}

	cout << "Hello friend! Welcome to Nyan Engine by GermanAizek\n";

	if (Core::debugmode) {

		/*
		// Test LUA script
		const char* name = "test.lua";
		cout << "Testing Lua scripts...\n";
		cout << "==========================\n" << name << "\n==========================\n";
		lua_State *ls = luaL_newstate(); // создаем виртуальную машину Lua
		luaL_openlibs(ls); // загружаем стандартные библиотеку
		luaL_dofile(ls, name); // выполняем скрипт
		lua_close(ls); // закрываем Lua
		cout << "==========================\n";
		cout << "SIZE STRUCT lua_Debug:" << sizeof(lua_Debug) << "\n";
		cout << "SIZE PTR STRUCT CallInfo:" << sizeof(struct CallInfo*) << "\n";
		cout << "SIZE const char*:" << sizeof(const char*) << "\n";
		cout << "SIZE int:" << sizeof(int) << "\n";
		cout << "SIZE char:" << sizeof(char) << "\n";
		cout << "SIZE unsigned char:" << sizeof(unsigned char) << "\n";


		//Test();
		//Script script;
		script.Create();
		script.RegisterConstant<lua_CFunction>(Write, "Write");
		script.RegisterConstant<lua_CFunction>(CreateBox, "CreateBox");
		script.RegisterConstant<lua_CFunction>(SetColorSpace, "SetColorSpace");
		script.DoFile("test.lua");
		script.Close();
		//
		*/

		// Test Python script
		/*
		PyObject *pName, *pModule, *pDict,
			*pClass, *pInstance, *pValue;
		int i, arg[2];

		if (argc < 4)
		{
			printf(
				"Usage: exe_name python_fileclass_name function_name\n");
			return 1;
		}

		// некоторый код пропущен...

		// построить имя вызываемого класса
		pClass = PyDict_GetItemString(pDict, argv[2]);

		// создать экземпляр класса
		if (PyCallable_Check(pClass))
		{
			pInstance = PyObject_CallObject(pClass, NULL);
		}

		// построить список параметров
		if (argc > 4)
		{
			for (i = 0; i < argc - 4; i++)
			{
				arg[i] = atoi(argv[i + 4]);
			}
			// вызвать метод класса с двумя параметрами
			pValue = PyObject_CallMethod(pInstance,
				argv[3], "(ii)", arg[0], arg[1]);
		}
		else
		{
			// вызвать метод класса без параметров
			pValue = PyObject_CallMethod(pInstance, argv[3], NULL);
		}
		if (pValue != NULL)
		{
			cout << "Return of call : " << pValue << "\n";
			//printf("Return of call : %d\n", PyInt_AsLong(pValue));
			Py_DECREF(pValue);
		}
		else
		{
			PyErr_Print();
		}
		*/
		//

	}

	initThreadManager();

	if(!Core::benchmode) initEngine();
	else {
		cout << "Start benchmark!\n";
		#pragma omp for
		for (int i = 0; i < 10; ++i) { //Для получения среднего времени

			auto begin = std::chrono::high_resolution_clock::now();
			initEngine();
			auto end = std::chrono::high_resolution_clock::now();

			cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns\n";
		}
	}

	return EXIT_SUCCESS;
}

bool checkDir(const char* path) { // HACK: Проверяет только файлы в каталогах, но не каталоги
	ifstream file;
	file.open(path);
	file.close();

	// HACK: Восстановление каталогов
	//const wchar_t lpath = path;
	//LPCTSTR s = L"char";
	//if (CreateDirectory(path, NULL)) {
	//	cout << "[AUTOFIX] Recovering directory ..." << path << "\n";
	//}

	if (file) {
		if (Core::debugmode) cout << "File verified: '" << path << "'\n";
		return true;
	}

	if (Core::debugmode) cout << "File not found: '" << path << "'\n";

	return false;
}