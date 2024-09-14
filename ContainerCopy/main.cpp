#include <vector>
#include <list>
#include <set>
#include <type_traits>

#include "Vector.h"
#include "List.h"
#include "Iterator.h"
#include "Set.h"
int main()
{
	Set<int> A;

	srand(time(NULL));

	A.Insert(10);
	A.Insert(20);
	A.Insert(30);
	A.Insert(15);
	A.Insert(25);
	A.Insert(5);
	A.Insert(1);

	A.Print();

	return 0;
}

 
