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
	void  push(T element) { // ������������ � �������
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

	T& front(void) { // ���������� ������� �������� �������
		return ptr->next->element;
	}

	void pop(void) { // �������� ���������� �������� �������
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

	size_t size(void) const { // �������� ������� �������
		size_t cnt = 0u;
		const node* iter = ptr->next;
		do {
			cnt++;
			iter = iter->next;
		} while (iter != ptr->next);
		return cnt;
	}

	bool empty(void) const { // �������� �� ������ �������
		return (!ptr);
	}

	void clear(void) { // ������ ����������� �������
		while (!this->empty())
			this->pop();
	}
};