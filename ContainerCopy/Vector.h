#pragma once
#include <memory>
#include "DataStructureBase.h"

template<typename DataType>
class Vector : public DataStructureBase<DataType>
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
		++EndPtr;
	}

	void Push_Back(const DataType& _Data)
	{
		if (MySize == MyCapacity)
		{
			ReAllocate(MyCapacity * 2);
		}
	
		MyElements[MySize] = _Data;

		++MySize;
		++EndPtr;
	}
	
	void Push_Back(DataType&& _Data)
	{
		if (MySize == MyCapacity)
		{
			ReAllocate(MyCapacity * 2);
		}
	
		MyElements[MySize] = std::forward<DataType>(_Data);

		++MySize;
		++EndPtr;
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

template <>
class Vector<bool>
{
public:
	//Default
	Vector() : MySize(0), MyCapacity(32)
	{
		if (MyElements == nullptr)
		{
			MyElements = new unsigned int[MyCapacity]();
			BeginPtr = MyElements;
		}
	}

	//Only Size
	Vector(const size_t _Size)
	{
		if (BeginPtr == nullptr)
		{
			MySize = _Size;
			MyCapacity = _Size + (32 - (_Size % 32));

			MyElements = new unsigned int[MyCapacity](0);
			BeginPtr = MyElements;
		}
	}
	
	//Size, Data
	Vector(const size_t _Size, const bool _Data)
	{
		if (BeginPtr == nullptr)
		{
			MySize = _Size;
			MyCapacity = _Size + (32 - (_Size % 32));

			MyElements = new unsigned int[MyCapacity](0);
			BeginPtr = MyElements;
			
			if (_Data == true)
			{
				RangedBitOn(0, 0, _Size / 32, _Size % 32);
			}
			else
			{
				RangedBitOff(0, 0, _Size / 32, _Size % 32);
			}
		}
	}

	~Vector()
	{
		if (MyElements != nullptr)
		{
			delete[] MyElements;

			BeginPtr = nullptr;
			MyElements = nullptr;
		}
	}

private:
	void BitOff(size_t _Index, size_t _Bit)
	{
		MyElements[_Index] &= ~(1 << _Bit);
	}

	void BitOn(size_t _Index, size_t _Bit)
	{
		MyElements[_Index] |= (1 << _Bit);
	}

	void RangedBitOn(size_t _StartIndex, size_t _StartBit, size_t _EndIndex, size_t _EndBit)
	{
		size_t Start = _StartIndex * 32 + _StartBit;
		size_t End = _EndIndex * 32 + _EndBit;

		for (size_t i = Start; i < End; i++)
		{
			size_t Index = i / 32;
			size_t Bit = i % 32;

			MyElements[Index] |= (1 << Bit);
		}
	}

	void RangedBitOff(size_t _StartIndex, size_t _StartBit, size_t _EndIndex, size_t _EndBit)
	{
		size_t Start = _StartIndex * 32 + _StartBit;
		size_t End = _EndIndex * 32 + _EndBit;

		for (size_t i = Start; i < End; i++)
		{
			size_t Index = i / 32;
			size_t Bit = i % 32;

			MyElements[Index] &= ~(1 << Bit);
		}

	}

private:
	unsigned int* BeginPtr = nullptr;
	unsigned int* MyElements = nullptr;

	size_t MySize = 0;
	size_t MyCapacity = 0;
};

