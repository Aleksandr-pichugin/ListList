#include <iostream>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------\n"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;
	size_t size;
public:
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
		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)//postfix increment
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		//Comperison operators:
		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}

		//Deference operators:
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "RItConstructor:\t" << this << endl;
		}
		~ ReverseIterator()
		{
			cout << "RItDestructor:\t" << this << endl;
		}

		//Incremento/Decremento:
		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		//Comparison operators:
		bool operator==(const ReverseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		//Derefence operators:
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	// Constructors:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			push_back(*it);
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDisructor:\t" << this << endl;
	}

	//Adding elements

	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			Head = Head->pPrev = new Element(Data, Head, nullptr);
		}
		size++;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data); 
			New->pPrev = Tail;
		if (Head == nullptr && Tail == nullptr)
			Head = Tail = New;
		else
		{
			New->pPrev=Tail;
			Tail = Tail->pNext = New;
		}
		size++;
	}
	void insert(int Data, int idx)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			Element* Temp = Head;
			if (idx < size / 2)
			{
				Temp = Head;
				for (int i = 0; i < idx; i++)Temp = Temp->pNext;
			}
			else
			{
				Temp = Tail;
				for (int i = 0; i < size - idx - 1; i++)Temp = Temp->pPrev;
			}
			Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		}
		size++;
	}

	// Removing elements:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr) return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}
	size--;
	}

	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;

		}
		size--;
	}
	void erase(int idx)
	{
		if (idx <= 0)return pop_front();
		if (idx >= size)return pop_back();
		Element* Temp;
		if (idx < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < idx; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - idx - 1; i++)Temp = Temp->pPrev;
		}
		Element* erased = Temp;
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}
	
	//Metods
	void print()const
	{
		cout << delimiter << endl;
		cout << "Hed:\t" << Head << endl;\

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout
			<< Temp->pPrev << tab
			<< Temp << tab
			<< Temp->Data << tab
			<< Temp->pNext << endl;

		cout << "Tail:\t" << Tail << endl;
		cout<<"Количество элементов списка : "<<size<<endl;
		cout << delimiter << endl;
	}
	void reverse_print()const
	{
		cout << delimiter << endl;
		cout << "Tail\t" << Tail << endl;

		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout
			<< Temp->pPrev << tab
			<< Temp ->pNext<< tab
			<< Temp->Data << tab
			<< Temp->pPrev << endl;

		cout << "Head\t" << Head << endl;
		cout << "Количество элементов списка : " << size << endl;
		cout << delimiter << endl;
	}
};

//#define BASE_CHECK
void main() {

	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов:"; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	//list.insert(99, 4);
	list.print();
	list.erase(2);
	//list.reverse_print();
	for (int i = 0; i < 100; i++)list.pop_back();
	list.reverse_print();
#endif  BASE_CHECK


	List list = { 3,5,8,13,21 };
	//list.print();
	//list.reverse_print();
	for (int i : list)cout << i << tab; cout << endl;
	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
}