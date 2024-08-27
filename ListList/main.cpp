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
		Element(int Data, Element* pNext = nullptr, Element* pprev = nullptr)
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
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
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
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			Head = Tail = new Element(Data);
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
		cout<<"���������� ��������� ������ : "<<size<<endl;
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
		cout << "���������� ��������� ������ : " << size << endl;
		cout << delimiter << endl;
	}
};

void main() {

	setlocale(LC_ALL, "");
	int n;
	cout << "������� ���������� ���������:"; cin >> n;
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
}