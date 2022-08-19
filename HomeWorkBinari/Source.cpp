#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define DEBUG

#define tab "\t"
#define delimiter "\n-----------------------------\n"

class Tree
{

	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pleft = nullptr, Element* pRight = nullptr) :
			Data(Data), pLeft(pleft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		friend class Tree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); it++)insert(*it, Root);
	}
	Tree(const Tree& other) :Tree()
	{
		copy(other.Root);
	}
	~Tree()
	{
		clear(Root);
		cout << "TDestructor:\t" << this << endl;
	}

	void insert(int Data)
	{
		insert(Data, this->Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int Count()const
	{
		return Count(Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	double Avg()const
	{
		return Avg(Root);
	}
	int depth()const
	{
		return depth(Root);
	}
	void clear()const
	{
		return clear(Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}

private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	int minValue(Element* Root)const
	{
		if (Root == nullptr)return int();
		if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)return int();
		if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);
	}
	int Count(Element* Root)const
	{
		if (Root == nullptr)return int();
		if (Root == nullptr)return 0;
		else return Count(Root->pLeft) + Count(Root->pRight) + 1;
	}
	int Sum(Element* Root)const
	{
		if (Root == nullptr)return int();
		else return Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}
	double Avg(Element* Root)const
	{
		return (double)Sum(Root) / Count(Root);
	}
	int depth(Element* Root)const
	{
		if (Root == NULL)
			return 0;
		else
		{
			int pLeft = depth(Root->pLeft);
			int pRight = depth(Root->pRight);
			if (pLeft <= pRight)
				return pRight + 1;
			else
				return pLeft + 1;
		}
	}
		
	
	void clear(Element* Root)const
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (Count(Root->pLeft) > Count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	void copy(Element* Root)
	{
		if (Root == nullptr)return;
		insert(Root->Data, this->Root);
		copy(Root->pLeft);
		copy(Root->pRight);
		cout << "CopyConstructor\t" << this << endl;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}

};



void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		int number = rand() % 100;
		cout << number << tab;
		tree.insert(number);
	}
	tree.print();
	cout << endl;
	cout << "Минемальное значение: " << tree.minValue() << endl;
	cout << "Максимальное значение: " << tree.maxValue() << endl;
	cout << "Количество элементов: " << tree.Count() << endl;
	cout << "Сумма элементов: " << tree.Sum() << endl;
	cout << "Среднее-арифметическое элементов: " << tree.Avg() << endl;
	cout << "Глубину дерева: " << tree.depth() << endl;
	int value;
	cout << "Удаление заданного значения из дерева: "; cin >> value;
	tree.erase(value);
	tree.print();
	Tree tree1 = tree;
	tree1.print();
}