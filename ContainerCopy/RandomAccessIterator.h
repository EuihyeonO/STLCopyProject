#pragma once

#include<iostream>

template <typename DataType>
class RandomAccessIterator
{
public:
	RandomAccessIterator()
	{
	}

	RandomAccessIterator(const DataType* _DataPtr)
	{
		DataPtr = const_cast<DataType*>(_DataPtr);
	}

	RandomAccessIterator(const RandomAccessIterator& _Other)
	{
		DataPtr = _Other.DataPtr;
	}

	RandomAccessIterator& operator=(const RandomAccessIterator& _Other)
	{
		DataPtr = _Other.DataPtr;
		return *this;
	}

	RandomAccessIterator& operator=(RandomAccessIterator&& _Other) noexcept
	{
		DataPtr = _Other.DataPtr;
		_Other.DataPtr = nullptr;

		return *this;
	}

	bool operator==(const RandomAccessIterator& _Other)
	{
		return (DataPtr == _Other.DataPtr);
	}

	bool operator!=(const RandomAccessIterator& _Other)
	{
		return !(*this == _Other);
	}
	
	RandomAccessIterator& operator++()
	{
		(DataPtr)++;
		return *this;
	}

	RandomAccessIterator operator++(int)
	{
		RandomAccessIterator ReturnIter(*this);
		++(*this);
		return ReturnIter;
	}

	RandomAccessIterator& operator--()
	{
		(DataPtr)--;
		return *this;
	}

	RandomAccessIterator operator--(int)
	{
		RandomAccessIterator ReturnIter(*this);
		--(*this);
		return ReturnIter;
	}
	 
	RandomAccessIterator& operator+(int _Offset)
	{
		DataPtr += _Offset;
		return *this;
	}

	RandomAccessIterator& operator-(int _Offset)
	{
		DataPtr -= _Offset;
		return *this;
	}

	DataType& operator*()
	{
		return *(DataPtr);
	}

	void Debug()
	{
		std::cout << *(DataPtr);
	}

private:
	DataType* DataPtr = nullptr;
};

template<>
class RandomAccessIterator<bool>
{
	class BitReference;

public:
	RandomAccessIterator()
	{
	}

	RandomAccessIterator(unsigned int* _DataPtr, size_t _BitIndex)
	{
		DataPtr = _DataPtr;
		BitIndex = _BitIndex;
	}

	RandomAccessIterator(const RandomAccessIterator& _Other)
	{
		DataPtr = _Other.DataPtr;
		BitIndex = _Other.BitIndex;
	}

	RandomAccessIterator& operator=(const RandomAccessIterator& _Other)
	{
		DataPtr = _Other.DataPtr;
		BitIndex = _Other.BitIndex;

		return *this;
	}

	RandomAccessIterator& operator=(RandomAccessIterator&& _Other) noexcept
	{
		DataPtr = _Other.DataPtr;
		BitIndex = _Other.BitIndex;
		_Other.DataPtr = nullptr;

		return *this;
	}

	bool operator==(const RandomAccessIterator& _Other)
	{
		return (DataPtr == _Other.DataPtr && BitIndex == _Other.BitIndex);
	}

	bool operator!=(const RandomAccessIterator& _Other)
	{
		return !(*this == _Other);
	}

	RandomAccessIterator& operator++()
	{
		BitIndex++;

		if (BitIndex >= 32)
		{
			BitIndex = 0;
			DataPtr++;
		}

		return *this;
	}

	RandomAccessIterator operator++(int)
	{
		RandomAccessIterator ReturnIter(*this);
		++(*this);
		return ReturnIter;
	}

	RandomAccessIterator& operator--()
	{
		BitIndex--;

		if (BitIndex < 0)
		{
			BitIndex = 31;
			DataPtr--;
		}

		return *this;
	}

	RandomAccessIterator operator--(int)
	{
		RandomAccessIterator ReturnIter(*this);
		--(*this);
		return ReturnIter;
	}

	RandomAccessIterator operator+(int _Offset)
	{
		size_t ReturnBitIndex = BitIndex + _Offset;
		unsigned int* ReturnDataPtr = DataPtr;

 		while (ReturnBitIndex >= 32)
		{
			ReturnBitIndex -= 32;
			ReturnDataPtr++;
		}

		return RandomAccessIterator(ReturnDataPtr, ReturnBitIndex);
	}

	RandomAccessIterator operator-(int _Offset)
	{
		size_t ReturnBitIndex = BitIndex - _Offset;
		unsigned int* ReturnDataPtr = DataPtr;

		while (ReturnBitIndex >= 32)
		{
			ReturnBitIndex += 32;
			ReturnDataPtr--;
		}

		return RandomAccessIterator(ReturnDataPtr, ReturnBitIndex);
	}

	BitReference operator*()
	{
		return BitReference(DataPtr, BitIndex);
	}

	void Debug()
	{
		std::cout << *(DataPtr);
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
			if (_Value == true)
			{
				(*DataPtr) |= (1 << BitIndex);
			}
			else
			{
				(*DataPtr) &= ~(1 << BitIndex);
			}
		}

	private:
		unsigned int* DataPtr = nullptr;
		size_t BitIndex = 0;
	};

private:
	unsigned int* DataPtr = nullptr;
	size_t BitIndex = 0;
};