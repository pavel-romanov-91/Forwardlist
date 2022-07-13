#include<iostream>
using namespace std;



#define tab "\t"
#define delimetr "\n-----------------------------------\n"

class ForwardList;
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
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
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
	ForwardList(initializer_list<int>il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	ForwardList(const ForwardList& other)
	{
		/*Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}*/
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other) :ForwardList()
	{
		/*this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;*/
		*this = std::move(other);
		cout << "MoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//					Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		Element* Temp = other.Head;
		while (Temp)
		{
			this->push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "CopyAssigment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}

		//				Adding Elements
	void push_front(int Data)
	{
		////1)Создаем новый элемент
		//Element* New = new Element(Data);
		////2)Присоединяем новый элемент к началу списка
		//New->pNext = Head;
		////3)Говорим, что новый элемент является головой списка
		//Head = New;
		Head = new Element(Data, Head);
			 
		size++;
	}
	void push_back(int Data)
	{
		//if (Head == nullptr)return push_front(Data);
		////1) Создаем новый элемент:
		//Element* New = new Element(Data);
		////2) Дойти до конца скписка:
		//Element* Temp = Head;
		//while (Temp->pNext)Temp = Temp->pNext;
		////3) Присоединяем новый элемент к списку:
		//Temp->pNext = New;
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
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
		//Element* Temp = Head;
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;		//Переходим на следующие элементы
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количесво элементов: " << Element::count << endl;
	}
	friend ForwardList operator+(const ForwardList & left, const ForwardList & right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;
	Element* Temp = right.Head;
	/*while (Temp)
	{
		cat.push_back(Temp->Data);
		Temp = Temp->pNext;
	}*/
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	cout << "Operator + " << endl;
	return cat;
}

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RENGE_BASED_ARRAY


void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;			//Односвязный список
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	//list = list;
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

	//cout << delimetr << endl;
	//ForwardList list2 = list; //CopyConstructor
	//cout << delimetr << endl;
	//ForwardList list2;
	//list2 = list;
	//list2.print();


#endif // BACE_CHECK

#ifdef OPERATOR_PLUS_CHECK
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

	cout << delimetr << endl;
	//ForwardList list3=list1 + list2;
	ForwardList list3;
	list3 = list1 + list2;
	cout << delimetr << endl;
	list3.print();

#endif // OPERATOR_PLUS_CHECK

#ifdef RENGE_BASED_ARRAY
	int arr[] = { 3,5,8,13,21 };

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		cout << arr[i] << tab;
	cout << endl;

	for (int i : arr)	//range-based for (цикл for на основе диапазона, цикл for для контейнера)
		cout << i << tab;
	cout << endl;
#endif // RENGE_BASED_ARRAY

	/*ForwardList list = { 3,5,8,13,21 };
	list.print();*/
	
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
}
