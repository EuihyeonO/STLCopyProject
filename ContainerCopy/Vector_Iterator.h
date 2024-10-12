#pragma once
#include "iterator.h"

template <typename DataType>
class Vector_Iterator
{
public:
	using Iterator_Category = typename RandomAccess_Iterator_Tag;

public:
	Vector_Iterator(const DataType* _Node)
	{
		DataPtr = const_cast<DataType*>(_Node);
	}

	Vector_Iterator(const Vector_Iterator& _Other)
	{
		DataPtr = _Other.DataPtr;
	}

	Vector_Iterator& operator=(const Vector_Iterator& _Other)
	{
		DataPtr = _Other.DataPtr;
		return *this;
	}

	Vector_Iterator& operator=(Vector_Iterator&& _Other) noexcept
	{
		DataPtr = _Other.DataPtr;
		_Other.DataPtr = nullptr;

		return *this;
	}

	bool operator==(const Vector_Iterator& _Other) const
	{
		return (DataPtr == _Other.DataPtr);
	}

	bool operator!=(const Vector_Iterator& _Other) const
	{
		return !(*this == _Other);
	}

	Vector_Iterator& operator++()
	{
		++DataPtr;
		return *this;
	}

	Vector_Iterator operator++(int)
	{
		Vector_Iterator ReturnIter(*this);
		++(*this);
		return ReturnIter;
	}

	Vector_Iterator& operator--()
	{
		--DataPtr;
		return *this;
	}

	Vector_Iterator operator--(int)
	{
		Vector_Iterator ReturnIter(*this);
		--(*this);
		return ReturnIter;
	}

	DataType& operator*()
	{
		return *(DataPtr);
	}

	Vector_Iterator operator+(int _Offset) const
	{
		return Vector_Iterator(this->DataPtr + _Offset);
	}

	Vector_Iterator operator-(int _Offset) const
	{
		return Vector_Iterator(this->DataPtr - _Offset);
	}

protected:
	DataType* DataPtr = nullptr;
};

template<>
class Vector_Iterator<bool>
{
	class BitReference;

public:
	using Iterator_Category = typename RandomAccess_Iterator_Tag;

public:
	Vector_Iterator()
	{
	}

	Vector_Iterator(unsigned int* _DataPtr, size_t _BitIndex)
	{
		DataPtr = _DataPtr;
		BitIndex = _BitIndex;
	}

	Vector_Iterator(const Vector_Iterator& _Other)
	{
		DataPtr = _Other.DataPtr;
		BitIndex = _Other.BitIndex;
	}

	Vector_Iterator& operator=(const Vector_Iterator& _Other)
	{
		DataPtr = _Other.DataPtr;
		BitIndex = _Other.BitIndex;

		return *this;
	}

	Vector_Iterator& operator=(Vector_Iterator&& _Other) noexcept
	{
		DataPtr = _Other.DataPtr;
		BitIndex = _Other.BitIndex;
		_Other.DataPtr = nullptr;

		return *this;
	}

	bool operator==(const Vector_Iterator& _Other)
	{
		return (DataPtr == _Other.DataPtr && BitIndex == _Other.BitIndex);
	}

	bool operator!=(const Vector_Iterator& _Other)
	{
		return !(*this == _Other);
	}

	Vector_Iterator& operator++()
	{
		BitIndex++;

		if (BitIndex >= 32)
		{
			BitIndex = 0;
			DataPtr++;
		}

		return *this;
	}

	Vector_Iterator operator++(int)
	{
		Vector_Iterator ReturnIter(*this);
		++(*this);
		return ReturnIter;
	}

	Vector_Iterator& operator--()
	{
		BitIndex--;

		if (BitIndex < 0)
		{
			BitIndex = 31;
			DataPtr--;
		}

		return *this;
	}

	Vector_Iterator operator--(int)
	{
		Vector_Iterator ReturnIter(*this);
		--(*this);
		return ReturnIter;
	}

	Vector_Iterator operator+(int _Offset)
	{
		size_t ReturnBitIndex = BitIndex + _Offset;
		unsigned int* ReturnDataPtr = DataPtr;

		while (ReturnBitIndex >= 32)
		{
			ReturnBitIndex -= 32;
			ReturnDataPtr++;
		}

		return Vector_Iterator(ReturnDataPtr, ReturnBitIndex);
	}

	Vector_Iterator operator-(int _Offset)
	{
		size_t ReturnBitIndex = BitIndex - _Offset;
		unsigned int* ReturnDataPtr = DataPtr;

		while (ReturnBitIndex >= 32)
		{
			ReturnBitIndex += 32;
			ReturnDataPtr--;
		}

		return Vector_Iterator(ReturnDataPtr, ReturnBitIndex);
	}

	BitReference operator*()
	{
		return BitReference(DataPtr, BitIndex);
	}

private:
	class BitReference
	{
	public:
		BitReference(const unsigned int* _DataPtr, size_t _BitIndex)
		{
			DataPtr = const_cast<unsigned int*>(_DataPtr);
			BitIndex = _BitIndex;
		}

		operator bool() const
		{
			return (*DataPtr) & (1 << BitIndex);
		}

		void operator=(bool _Value)
		{
			(_Value == true) ? (*DataPtr) |= (1 << BitIndex) : (*DataPtr) &= ~(1 << BitIndex);
		}

	private:
		unsigned int* DataPtr = nullptr;
		size_t BitIndex = 0;
	};

private:
	unsigned int* DataPtr = nullptr;
	size_t BitIndex = 0;
};