#pragma once

class IteratorBase
{
public:
	// 후위증감자는 반환형이 값형이라 전위 증감자와 같은 방식으로는 순수 가상 함수 선언이 안된다. 
	// 공변성 문제
	// 방법이 없을까?

	virtual IteratorBase& operator++() = 0;

};

