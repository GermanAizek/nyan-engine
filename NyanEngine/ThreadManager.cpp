#include "stdafx.h"
#include "ThreadManager.h"
#include "Engine.h"
// TODO: ������� ��������� �������� �� ������� � ������������ ������ ������� ������ �� �������, ������ � dev/threadmanager/
extern int counts_threads = std::thread::hardware_concurrency();
extern std::vector<QueueThread<int>> queue(counts_threads);

void initThreadManager() {

	//for (size_t i = 0; i < counts_threads; ++i) {
		
		std::vector<QueueThread<int>> queue(counts_threads);

		if (Core::debugmode) {
			std::cout << counts_threads << " threads will use the engine.\n";
			std::cout << "size queue: " << queue.size() << "\n";  // �������� ������ �������
		}

		//for (int i = 1; i <= 7; i++) queue[i].push(i * 100); // ���������� ������� �� �����


		//while (!queue.empty()) {  // ������ ������� �� ������� �� ���������� ��������
		//	cout << queue.front() << endl;
		//	queue.pop();
		//}
		//queue.clear(); // ������� ������� �� �����

		if (queue.empty()) std::cout << "queue NULL\n";
	//}
}

void addThread(bool &func) {
	for (size_t i = 0; i < queue.size(); ++i) {
		if (queue[i].empty()) {
			queue[i].push(func);
			break;
		}
	}
}