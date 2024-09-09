#include <iostream>
#include <chrono>
#include <vector>
#include <bitset>

#include "Vector.h"

class A
{
public:
	A()
	{
		if (Arr == nullptr)
		{
			Arr = new int[100];
		}
	}

	A(const A& _C)
	{
		if (Arr == nullptr)
		{
			Arr = new int[100];
		}

		for (int i = 0; i < 100; i++)
		{
			Arr[i] = _C.Arr[i];
		}
	}

	A(A&& _C) noexcept
	{
		if (Arr == nullptr)
		{
			Arr = _C.Arr;
		}
	}

	A& operator=(const A& _A)
	{
		for (int i = 0; i < 100; i++)
		{
			Arr[i] = _A.Arr[i];
		}

		return *this;
	}

	A& operator=(A&& _A) noexcept
	{
		if (Arr != nullptr)
		{
			delete[] Arr;
		}
		
		Arr = _A.Arr;
		_A.Arr = nullptr;

		return *this;
	}

private:
	int* Arr = nullptr;
};

int main()
{
	Vector<int> A;
	A.Push_Back(1);
	A.Push_Back(3);
	A.Push_Back(5);
	A.Push_Back(7);
	A.Push_Back(9);

	Vector<bool> B;
	B.Push_Back(true);
	B.Push_Back(true);

	return 0;
}