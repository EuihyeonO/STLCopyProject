#pragma once
#include <memory>

template<typename DataType>
class Vector 
{
public:
	//Default
	Vector() : MySize(0), MyCapacity(4)
	{
		if (MyElements == nullptr)
		{
			MyElements = new DataType[MyCapacity]();
			
			BeginPtr = MyElements;
			EndPtr = MyElements;
		}
	}

	//Only Size
	Vector(const size_t _Size) : MySize(_Size), MyCapacity(_Size)
	{
		if (BeginPtr == nullptr)
		{
			MyElements = new DataType[MyCapacity]();

			BeginPtr = MyElements;
			EndPtr = BeginPtr + _Size;
		}
	}

	//Size, Data (L-Value)
	Vector(const size_t _Size, const DataType& _Data) : MySize(_Size), MyCapacity(_Size)
	{
		if (BeginPtr == nullptr)
		{
			MyElements = new DataType[MyCapacity];

			BeginPtr = MyElements;
			EndPtr = BeginPtr + _Size;

			for (size_t i = 0; i < _Size; i++)
			{
				MyElements[i] = _Data;
			}
		}
	}

	//Size, Data (R-Value)
	Vector(const size_t _Size, DataType&& _Data) : MySize(_Size), MyCapacity(_Size)
	{
		if (BeginPtr == nullptr)
		{
			MyElements = new DataType[MyCapacity];

			BeginPtr = MyElements;
			EndPtr = BeginPtr + _Size;

			for (size_t i = 0; i < _Size; i++)
			{
				MyElements[i] = std::forward<DataType>(_Data);
			}
		}
	}

	~Vector()
	{
		if (MyElements != nullptr)
		{
			delete[] MyElements;

			BeginPtr = nullptr;
			EndPtr = nullptr;
			MyElements = nullptr;
		}
	}

public:
	void Reserve(const size_t _Capacity)
	{
		ReAllocate(_Capacity);
	}

	void Resize(const size_t _Size)
	{
		ReAllocate(_Size);
		MySize = _Size;
	}

	void Resize(const size_t _Size, const DataType& _Data)
	{
		ReAllocate(_Size);

		for (int i = MySize; i < _Size; i++)
		{
			MyElements[i] = _Data;
		}

		MySize = _Size;
	}

	void Resize(const size_t _Size, DataType&& _Data)
	{
		ReAllocate(_Size);

		for (size_t i = MySize; i < _Size; i++)
		{
			MyElements[i] = std::forward<DataType>(_Data);
		}

		MySize = _Size;
	}

public:
	template<typename... Valty>
	void Emplace_Back(Valty&&... _Value)
	{
		if (MySize == MyCapacity)
		{
			ReAllocate(MyCapacity * 2);
		}

		new (&MyElements[MySize]) DataType(std::forward<Valty>(_Value)...);

		++MySize;
	}

	void Push_Back(const DataType& _Data)
	{
		if (MySize == MyCapacity)
		{
			ReAllocate(MyCapacity * 2);
		}
	
		MyElements[MySize] = _Data;
		++MySize;
	}
	
	void Push_Back(DataType&& _Data)
	{
		if (MySize == MyCapacity)
		{
			ReAllocate(MyCapacity * 2);
		}
	
		MyElements[MySize] = std::forward<DataType>(_Data);
		++MySize;
	}

private:
	void ReAllocate(const size_t _Capacity)
	{
		if (_Capacity <= MyCapacity)
		{
			return;
		}


		DataType* NewPtr = new DataType[_Capacity]();

		for (size_t i = 0; i < MySize; i++)
		{
			NewPtr[i] = std::move(MyElements[i]);
		}

		BeginPtr = NewPtr;
		EndPtr = BeginPtr + MySize;

		delete[] MyElements;

		MyElements = NewPtr;

		MyCapacity = _Capacity;
	}

private:
	DataType* BeginPtr = nullptr;
	DataType* EndPtr = nullptr;

	DataType* MyElements = nullptr;
	
	size_t MySize = 0;
	size_t MyCapacity = 0;
};