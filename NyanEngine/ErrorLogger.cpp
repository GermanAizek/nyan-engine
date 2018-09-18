#include "ErrorLogger.h"

// TODO: Добавить время когда произошла ошибка
// TODO: Добавить больше параметров функции: (тип ошибки, ошибка, путь файла)
void addLogFile(std::string error) {
	std::ofstream log("user/nyan.log", std::ios_base::app);
	if (log.is_open()) {
		time_t t = time(NULL);
		std::string time = ctime(&t);
		time.replace(time.find("\n"), 1, "");
		log << "[" << time << "] " << error << "\n"; // user/nyan.log
		std::cout << "[" << time << "] " << error << "\n"; // standart console
		log.close();
	}
	else {

		if (CreateDirectory(L"user", NULL)) {
			system("cls");
			std::cout << "[ERROR] Can not access user/nyan.log!\n";
			std::cout << "[AUTOFIX] Recovering a file user/nyan.log ...\n";
			std::cout << "[AUTOFIX] File user/nyan.log restored!\n";
			system("nyanengine.exe");
			exit(EXIT_SUCCESS);
		}
		else
			std::cout << "[AUTOFIX_ERROR] Failed to restore user/nyan.log!\n";
		}
}