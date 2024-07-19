#pragma once

template<typename DataType>
class Iterator
{
public:
	Iterator(DataType* _Ptr) : DataPtr(_Ptr)
	{
	}

private:
	const DataType* DataPtr = nullptr;
};

