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

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	List<int> A;
	A.Push_Back(1);
	List<int>::Iterator Iter = A.Begin();
	std::cout << *Iter;
	return 0;
}

 
