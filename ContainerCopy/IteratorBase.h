#pragma once

class IteratorBase
{
public:
	// ���������ڴ� ��ȯ���� �����̶� ���� �����ڿ� ���� ������δ� ���� ���� �Լ� ������ �ȵȴ�. 
	// ������ ����
	// ����� ������?

	virtual IteratorBase& operator++() = 0;

};

