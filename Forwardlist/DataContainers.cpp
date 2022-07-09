#include<iostream>
using namespace std;



#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0;

class ForwardList
{
	Element* Head;	//Голова списка
	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstractor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "CopyConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//					Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		while (Head)pop_front();
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "CopyAssigment:\t" << this << endl;
		return *this;
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
		size++;
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
		size++;
	}
	void insert(int Data, int index)
	{
		if (index == 0 || Head == nullptr)return push_front(Data);
		if (index == size)return push_back(Data);
		if (index > size)
		{
			cout << "Eror: Out of range" << endl;
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//				Removing elements
	void pop_front()
	{
		Element* erased = Head;
		Head = Head->pNext;
		delete erased;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int index)
	{
		if (index == 0)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Erased->pNext;
		delete Erased;
		size--;
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
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количесво элементов: " << Element::count << endl;

	}
};

#define BASE_CHECK
//#define COUNT_CHECK


void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;			//Односвязный список
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	/*list.pop_front();
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
	list.print();*/

	//ForwardList list2 = list; //CopyConstructor
	ForwardList list2;
	list2 = list;
	list2.print();


#endif // BACE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
#endif // COUNT_CHECK

}
