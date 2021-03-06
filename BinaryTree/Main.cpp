//BinaryTree
#include<iostream>
using namespace std;

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		this->Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	~Tree()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	void insert(int Data)
	{
		insert(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int size()const
	{
		return size(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	void print()const
	{
		print(Root);
	}
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}
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
		if (Root == nullptr)return 0;
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		//return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		return Root->pLeft ? minValue(Root->pLeft) : Root->Data;
	}
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int size(Element* Root)const
	{
		return Root == nullptr ? 0 : size(Root->pLeft) + size(Root->pRight) + 1;
	}

	int sum(Element* Root)const
	{
		if (Root == nullptr) return 0;
		return Root->Data + sum(Root->pLeft) + sum(Root->pRight);
	}

	void print(Element* Root)const
	{
		if (Root == nullptr) return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	/*cout << "Минимальным значением является: " << tree.minValue() << endl;
	cout << "Максимальным значением является: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.size() << endl;*/
	cout << "Сумма элементов в дереве: " << tree.sum() << endl;
}

//TODO:
//1. Написать рекурсивную функцию int factorial(int n), которая принимает число,
//и возвращает факториал этого числа;
//2. Написать реурсивную функцию double power(double a, int n), которая возводит указанное число
//в указанную степень;
//----------------------------------------------------------
//1. В класс BinaryTree добавить методы :
//int minValue();
//int maxValue();
//int size();
//int sum();
//double avg();
//void erase(int Data);
//CopyMethods;
//MoveMethods;
//2. Функции должны вызываться из main() без передачи в них корня дерева;
//3. Вывести дерево в виде дерева;
//4. Сбалансировать Бинарное дерево;