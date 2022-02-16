//List2
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class List
{
	class Element
	{
		int Data;		//Значение элемента
		Element* pNext;	//Адрес следующего элемента
		Element* pPrev;	//Адрес предыдущего элемента
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;
	size_t size;//size_t - unsigned int
	/*Element* Head;
	Element* Tail;
	unsigned int size;*/

	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}

		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}
		Iterator& operator++()	//Prefix increment
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)//Postfix increment
		{
			Iterator old = *this;	
			Temp = Temp->pNext;		
			return old;	
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}

	};
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}

	List(const initializer_list<int>& il) :List()
	{		
		cout << typeid(il.begin()).name() << endl;		
		for (int const* it = il.end() - 1; it != il.begin() - 1; it--)
		{
			push_front(*it);
		}
	}

	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	//			Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;*/
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		//Element* New = new Element(Data);//1)
		//New->pPrev = Tail;//2)
		//Tail->pNext = New;//3)
		//Tail = New;//4)
		Tail = Tail->pNext = new Element(Data,0,Tail);
		size++;
	}
	void insert(int index, int Data)
	{
		if (index > size)return;
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - 1 - index; i++)Temp = Temp->pPrev;
		}
		//Неважно, с какой стороны мы добрались до нужного элемента, 
		//процедура добавления нового элемента быдет идентичной:
		//Element* New = new Element(Data);
		//New->pNext = Temp;//1)
		//New->pPrev = Temp->pPrev;//2)
		//Temp->pPrev->pNext = New;//3)
		//Temp->pPrev = New;//4)

		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}

	//			Removing elements:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int index)
	{
		if (index > size)return;
		if (Head == nullptr && Tail == nullptr) return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		if (index == 0)
		{			
			pop_front();
			return;
		}

	    if (index == size)
		{
			pop_back();			
			return;
		}

		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - 1 - index; i++)Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
		
	}

	//			Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
};

//#define BASE_CHECK
#define RANGE_BASE_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
    list.push_front(555);
	list.print();
	list.push_back(555);
	list.print();


	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index-1, value);
	list.print();
	
	list.reverse_print();

	int index;
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index-1);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

#ifdef RANGE_BASE_FOR_LIST
	List list = { 3,5,8,13,21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASE_FOR_LIST
	
}

//void main()
//{
//	setlocale(LC_ALL, "");
//	int n;
//	cout << "Введите размер списка: "; cin >> n;
//	List list;
//	for (int i = 0; i < n; i++)
//	{
//		list.push_front(rand() % 100);
//	}
//	list.print();
//	/*list.reverse_print();*/
//	list.push_back(555);
//	list.print();
//	list.push_front(555);
//	list.print();
//}

//TODO:

//Проверочный код должен заработать:
//List list = { 3, 5, 8, 13, 21 };
//for (int i : list)cout << i << tab; cout << endl;

//
//Destructor;
//CopyMethods;
//MoveMethods;
//ILconstructor;
//List list = { 3,5,8,13,21 };
//for (int i : list) cout << i << tab; cout << endl;