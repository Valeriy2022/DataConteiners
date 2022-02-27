#include<iostream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

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
		cout << "EConstrcutor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestrcutor:\t" << this << endl;
	}
	friend class StackList;
	friend class Iterator;
};

int Element::count = 0;

class DL_Element :public Element
{
	DL_Element* pPrev;
public:
	DL_Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Element(Data, pNext)

	{
		cout << "DL_Constructor:\t" << this << endl;
	}
	~DL_Element()
	{
		cout << "DL_Destructor:\t" << this << endl;
	}
};



class StackList//Односвязный (однонаправленный) список
{
	Element* Head;	
	unsigned int size;
public:
	Element* getHead()const
	{
		return Head;
	}
	unsigned int get_size()const
	{
		return this->size;
	}
	StackList()
	{
		Head = nullptr;//Если голова указывает на 0, то список пуст.
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	StackList(unsigned int size) :StackList()
	{
		//this->Head = nullptr;
		//this->size = 0;
		for (int i = 0; i < size; i++)
		{
			push_front(0);
		}
	}
	~StackList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
		
	void push_front(int Data)
	{
		Head = new Element(Data, Head);
		size++;
	}	
	void pop_front()
	{
		if (Head == nullptr)return;		
		Element* Erased = Head;		
		Head = Erased->pNext;		
		delete Erased;
		size--;
	}	

	//					Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)			
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов : " << Head->count << endl;
	}
};

class QueueList//Двусвязный список
{
	DL_Element* DL_Head;
	DL_Element* Tail;
	unsigned int size;
public:
	
	QueueList()
	{
		DL_Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	
	~QueueList()
	{
		while (DL_Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

					
	void push(int Data)
	{
		if (DL_Head == nullptr && Tail == nullptr)
		{
			DL_Head = Tail = new DL_Element(Data);
			size++;
			return;
		}
		
		DL_Head = DL_Head->pPrev = new DL_Element(Data, DL_Head);
		size++;
	}
	void pop_front()
	{
		if (DL_Head == nullptr && Tail == nullptr)return;
		if (DL_Head == Tail)
		{
			delete DL_Head;
			DL_Head = Tail = nullptr;
			size--;
			return;
		}
		DL_Head = DL_Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (DL_Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	//					Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)			
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов : " << Head->count << endl;
	}
};




	void main()
{
	setlocale(LC_ALL, "");
	StackList List;
	List.push_front(1);
	List.push_front(2);
	List.push_front(3);
	List.push_front(4);
	List.push_front(5);
	List.print();
	List.pop_front();
	List.print();

	QueueList QList;
	QList.push_front(1);
	QList.push_front(2);
	QList.push_front(3);
	QList.push_front(4);
	QList.push_front(5);
	QList.print();


}

//TODO:
//	1. На базе односвязного списка реализовать класс Stack;
//	2. На базе двусвязного списка реализовать класс Queue(очередь);
