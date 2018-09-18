#pragma once

#include "Include.h"

void initThreadManager();

void addThread(bool &func);

template<class T>
class QueueThread {
	struct node {
		T element;
		node* next;
	};
private:
	node*  ptr;
public:
	QueueThread(void) : ptr(nullptr) {}
	~QueueThread() {
		this->clear();
	}
public:
	void  push(T element) { // Заталкивание в очередь
		node* e = new node();
		e->element = element;
		if (!ptr) {
			ptr = e;
			ptr->next = ptr;
		}
		else {
			e->next = ptr->next;
			ptr = ptr->next = e;
		}
	}

	T& front(void) { // Возращение данного элемента очереди
		return ptr->next->element;
	}

	void pop(void) { // Удаление следующего элемента очереди
		if (ptr == ptr->next) {
			delete ptr;
			ptr = nullptr;
			return;
		}
		node* tmp = ptr->next;
		ptr->next = tmp->next;
		delete tmp;
		tmp = nullptr;
	}

	size_t size(void) const { // Проверка размера очереди
		size_t cnt = 0u;
		const node* iter = ptr->next;
		do {
			cnt++;
			iter = iter->next;
		} while (iter != ptr->next);
		return cnt;
	}

	bool empty(void) const { // Проверка на пустую очередь
		return (!ptr);
	}

	void clear(void) { // Полное уничтожение очереди
		while (!this->empty())
			this->pop();
	}
};