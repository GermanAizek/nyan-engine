#include "stdafx.h"
#include "Engine.h"
#include "Scene.h"
#include "Render.h"
#include "Parser.h"
#include "ErrorLogger.h"
//#include "Script.h"
#include "EngineFunctions_Lua.h"

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") // Скрыть консоль

Settings settings_token;

int initEngine()
{
	addLogFile("Initializing engine...");
	// TODO: Посмотреть аниме

	// start system clock
	systemClock = std::chrono::system_clock::now();
	sf::Clock currentClock;

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

	if (dir && parseSettings())
	{
		addLogFile("Engine is initialized!");
		addLogFile("Parsing file scene!");

		//parseScene(); раскомментить обязательно

		addLogFile("Start rendering!");

		switch (renderDeviceSFML())
		{
		case ERROR_FILE:
			addLogFile("[ERROR] No configuration values found. Check the .cfg files!");
			Core::criticalError = true;
			break;
		case ERROR_LOAD:
			addLogFile("[ERROR] Error loading file for rendering!");
			//Core::criticalError = true;
			break;
		default:
			addLogFile("[GERMAN] I fucking, but you do not have mistakes!");
		}
	}
	else if (!dir)
	{
		addLogFile("[ERROR] Check content path!");
		Core::criticalError = true;
	}
	else
	{
		addLogFile("[ERROR] Check configuration files for errors!");
		Core::criticalError = true;
	}

	if (Core::criticalError)
	{
		addLogFile("[CRITICAL_ERROR] Engine noticed critical errors, check the log!");
		system("pause");
	}

	return EXIT_SUCCESS;
}

int main(size_t argc, char* argv[])
{
	std::ios_base::sync_with_stdio(0);

	#pragma omp for
	for (int i = 1; i < argc; ++i)
	{
		std::cout << "Start parameter used: " << argv[i] << '\n';

		if (!strcmp(argv[i], "-bench"))
		{
			addLogFile("Benchmark mode on!");
			Core::benchmode = true;
		}

		if (!strcmp(argv[i], "-debug"))
		{
			addLogFile("Debug mode on!");
			Core::debugmode = true;
		}

		if (!strcmp(argv[i], "-editor"))
		{
			addLogFile("Editor mode on!");
			EngineEvent::showEditor = true;
		}
	}

	if (Core::debugmode)
	{
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

	if (!Core::benchmode)
		initEngine();
	else
	{
		addLogFile("Start benchmark!\n");

		#pragma omp for
		for (int i = 0; i < 10; ++i) // Take avg time
		{

			auto begin = std::chrono::high_resolution_clock::now();
			initEngine();
			auto end = std::chrono::high_resolution_clock::now();

			addLogFile("Init engine time: " + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) + "ns\n");
		}
	}

	return EXIT_SUCCESS;
}

bool checkDir(std::string_view path) // TODO: Проверяет только файлы в каталогах, но не каталоги
{
	std::ifstream file;
	file.open(path.data());
	file.close();

	// TODO: Восстановление каталогов
	//const wchar_t lpath = path;
	//LPCTSTR s = L"char";
	//if (CreateDirectory(path, NULL)) {
	//	cout << "[AUTOFIX] Recovering directory ..." << path << "\n";
	//}

	if (file)
	{
		if (Core::debugmode)
			std::cout << "File verified: '" << path << "'\n";

		return true;
	}

	if (Core::debugmode)
		std::cout << "File not found: '" << path << "'\n";

	return false;
}