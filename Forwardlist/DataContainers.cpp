﻿#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;	//Голова списка
public:
	ForwardList()
	{
		Head = nullptr;
		cout << "LConstractor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

		//				Adding Elements
	void push_front(int Data)
	{
		//1)Создаем новый элемент
		Element* New = new Element(Data);
		//2)Присоединяем новый элемент к началу списка
		New->pNext = Head;
		//3)Говорим, что новый элемент является головой списка
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) Создаем новый элемент:
		Element* New = new Element(Data);
		//2) Дойти до конца скписка:
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		//3) Присоединяем новый элемент к списку:
		Temp->pNext = New;
	}
	void insert(int Data, int index)
	{
		if (index == 0 || Head == nullptr)return push_front(Data);
		if (index)return;
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;
		Temp->pNext = new Element(Data, Temp->pNext);
	}

	//				Removing elements
	void pop_front()
	{
		Element* erased = Head;
		Head = Head->pNext;
		delete erased;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}
	void erase(int index)
	{
		if (index)return;
		if (index == 0)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		delete Erased;
		Temp->pNext = Erased->pNext;
	}

	//				Methods:
	void print()const
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;		//Переходим на следующие элементы
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;			//Односвязный список
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.pop_front();
	list.pop_back();
	list.print();

	int index;
	int value;

	cout << "Введите индекс добовляемого элемента: "; cin >> index;
	cout << "Ведите значение добавляемого элемента: "; cin >> value;

	list.insert(value, index);
	list.print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
}