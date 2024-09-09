#pragma once
#include <memory>
#include <exception>
#include <climits>
#include <cassert>

#include "RandomAccessIterator.h"
#include "CustomException.h"

/*****************************************************************************/
/********************************** Vector  **********************************/
/*****************************************************************************/

template<typename DataType>
class VectorBase
{
public:
	virtual void Reserve(const size_t _Capacity) = 0;
	virtual void Resize(const size_t _Size) = 0;
	virtual void Resize(const size_t _Size, const DataType& _Data) = 0;
	virtual void Resize(const size_t _Size, DataType&& _Data) = 0;
	
	virtual void Push_Back(const DataType& _Data) = 0;
	virtual void Push_Back(DataType&& _Data) = 0;
	virtual void Pop_back() = 0;
	
	virtual void Insert(const RandomAccessIterator<DataType>& _Where, const DataType& _Value) = 0;
	virtual void Clear() = 0;
	
	virtual const DataType& At(size_t _Index) = 0;
	virtual const DataType& Front() = 0;
	virtual const DataType& Back() = 0;
};

template<typename DataType>
class Vector : public VectorBase<DataType>
{
public:
	using Iterator = typename RandomAccessIterator<DataType>;

//Constructor
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

//Operator
public:
	const DataType& operator[](size_t _Index)
	{
		return MyElements[_Index];
	}

//Iterator Function
public:
	Iterator Begin()
	{
		return Iterator(BeginPtr);
	}
	
	Iterator End()
	{
		return  Iterator(EndPtr);
	}

//Vector Function (Memory)
public:
	void Reserve(const size_t _Capacity) override
	{
		ReAllocate(_Capacity);
	}

	void Resize(const size_t _Size) override
	{
		ReAllocate(_Size);
		MySize = _Size;
	}

	void Resize(const size_t _Size, const DataType& _Data) override
	{
		ReAllocate(_Size);

		for (size_t i = MySize; i < _Size; i++)
		{
			MyElements[i] = _Data;
		}

		MySize = _Size;
	}

	void Resize(const size_t _Size, DataType&& _Data) override
	{
		ReAllocate(_Size);

		for (size_t i = MySize; i < _Size; i++)
		{
			MyElements[i] = std::forward<DataType>(_Data);
		}

		MySize = _Size;
	}

//Vector Function (Data)
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

	void Push_Back(const DataType& _Data) override
	{
		if (MySize == MyCapacity)
		{
			ReAllocate(MyCapacity * 2);
		}
	
		MyElements[MySize] = _Data;

		++MySize;
		++EndPtr;
	}
	
	void Push_Back(DataType&& _Data) override
	{
		if (MySize == MyCapacity)
		{
			ReAllocate(MyCapacity * 2);
		}
	
		MyElements[MySize] = std::forward<DataType>(_Data);

		++MySize;
		++EndPtr;
	}

	const DataType& At(size_t _Index) override
	{
		try 
		{
			if (_Index >= MySize)
			{
				throw CustomException::OutOfLange(typeid(*this).name());
			}
		}
		catch (std::exception& _Error)
		{
			std::cerr << _Error.what() << std::endl;
			assert(false);
		}

		return MyElements[_Index];
	}

	const DataType& Front() override
	{
		return MyElements[0];
	}

	const DataType& Back() override
	{
		return MyElements[MySize - 1];
	}

	void Clear() override
	{
		MySize = 0;
		EndPtr = BeginPtr + 1;
	}

	void Pop_back() override
	{
		if (MySize > 0)
		{
			MySize--;
			EndPtr--;
		}
	}

	void Insert(const Iterator& _Where, const DataType& _Value) override
	{
		if (MySize + 1 >= MyCapacity)
		{
			Reserve(MyCapacity * 2);
		}
	
		Iterator EndIter = End();
	
		while (_Where != EndIter)
		{
			*EndIter = *(EndIter - 1);
		}
	}

//Only used in Class
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

/***********************************************************************************/
/********************************** Vector<bool>  **********************************/
/***********************************************************************************/

template <>
class Vector<bool> : public VectorBase<bool>
{
public:
	using Iterator = RandomAccessIterator<bool>;

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

//Operator
public:
	const bool operator[](size_t _Index)
	{
		size_t ArrayIndex = _Index / 32;
		size_t BitIndex = _Index % 32;

		bool ReturnBit = MyElements[ArrayIndex] & (1 << BitIndex);

		return ReturnBit;
	}

//Iterator Function
public:
	Iterator Begin()
	{
		return Iterator(BeginPtr, 0);
	}
	
	Iterator End()
	{
		return  ++Iterator(BeginPtr + (MySize / 32), (MySize % 32));
	}

//Vector Function (Memory)
public:
	virtual void Reserve(const size_t _Capacity)
	{
		ReAllocate(_Capacity);
	}
	
	virtual void Resize(const size_t _Size)
	{
		ReAllocate(_Size);
		MySize = _Size;
	}

	virtual void Resize(const size_t _Size, const bool& _Data)
	{
		ReAllocate(_Size);

		size_t CurSize = MySize;
		unsigned int ArrayData = (_Data == true ? UINT_MAX : 0);

		size_t CurArrayIndex = CurSize / 32;
		size_t MaxArrayIndex = _Size / 32;

		while (CurArrayIndex < MaxArrayIndex)
		{
			MyElements[CurArrayIndex] = ArrayData;
			CurArrayIndex++;
		}
	}

	virtual void Resize(const size_t _Size, bool&& _Data)
	{
		//bool은 R-Value를 따로 처리할 필요는 없을 것 같다. 순수 가상 함수 때문에, 강제 정의 (상위 클래스에 선언된 함수를 좀 수정해야 할듯?)
		bool Data = _Data;
		Resize(_Size, Data);
	}

public:
	virtual void Push_Back(const bool& _Data)
	{
		if (MySize + 1 >= MyCapacity)
		{
			ReAllocate(MyCapacity * 2);
		}

		size_t EndArrayIndex = MySize / 32;
		size_t EndBitIndex = MySize % 32;

		if (_Data == true)
		{
			BitOn(EndArrayIndex, EndBitIndex);
		}
		else
		{
			BitOff(EndArrayIndex, EndBitIndex);
		}

		MySize++;
	}

	virtual void Push_Back(bool&& _Data)
	{
		bool Data = _Data;
		Push_Back(Data);
	}

	virtual void Pop_back()
	{
		if (MySize > 0)
		{
			MySize--;
		}
	}
	
	virtual void Insert(const Iterator& _Where, const bool& _Value)
	{
		if (MySize + 1 >= MyCapacity)
		{
			ReAllocate(MyCapacity * 2);
		}

		MySize++;

		Iterator StartIter = _Where;
		Iterator EndIter = End();


		while (StartIter != EndIter)
		{
			bool PrevValue = *(EndIter - 1);
			*EndIter = PrevValue;
			EndIter--;
		}

		Iterator InsertIter = _Where;
		*InsertIter = _Value;

		std::cout << *Begin() << *(Begin() + 1) << *(Begin() + 2) << std::endl;
	}

	virtual void Clear() 
	{
		MySize = 0;
	}
	
	virtual const bool& At(size_t _Index) 
	{
		try
		{
			if (_Index >= MySize)
			{
				throw CustomException::OutOfLange(typeid(*this).name());
			}
		}
		catch (std::exception& _Error)
		{
			std::cerr << _Error.what() << std::endl;
			assert(false);
		}

		return MyElements[_Index];
	}

	virtual const bool& Front() 
	{
		return (*BeginPtr & (1 << 0)); 
	}

	virtual const bool& Back()
	{
		unsigned int* _EndElement = BeginPtr + (MySize / 32);
		size_t BitIndex = MySize % 32;

		return (*_EndElement & (1 << BitIndex));
	}

//Only used in class
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

	void ReAllocate(const size_t _Capacity)
	{
		if (_Capacity <= MyCapacity)
		{
			return;
		}

		size_t Shared_32 = _Capacity / 32;
		size_t RealCapacity = Shared_32 + 1;


		unsigned int* NewPtr = new unsigned int[RealCapacity]();

		for (size_t i = 0; i < RealCapacity; i++)
		{
			NewPtr[i] = std::move(MyElements[i]);
		}

		BeginPtr = NewPtr;
		delete[] MyElements;

		MyElements = NewPtr;
		MyCapacity = _Capacity;
	}

private:
	unsigned int* BeginPtr = nullptr;
	unsigned int* MyElements = nullptr;

	size_t MySize = 0;
	size_t MyCapacity = 0;
};

