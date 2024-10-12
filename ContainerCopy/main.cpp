#include <vector>
#include <list>
#include <set>
#include <type_traits>
#include <crtdbg.h>
#include <iostream>

#include "Vector.h"
#include "List.h"
#include "Iterator.h"
#include "Set.h"

class A
{
public:
	A(){}
	A(int _A, int _B)
	{
		int C = 0;
	}
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Vector<bool> BoolVector;

	BoolVector.Push_Back(false);

	Vector<bool>::Iterator BoolIter = BoolVector.Begin();


	return 0;
}

 
