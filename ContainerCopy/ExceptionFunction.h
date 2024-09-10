#pragma once
#include <cassert>
#include "CustomException.h"

enum class ExceptionType
{
	OutOfRange,
	EmptyContainer,
};

class ExceptionFunction
{
public:
	static void CheckException(bool _IsOccurred, bool _DoAssert, const char* _ClassName, ExceptionType _ExceptionType)
	{
		try
		{
			if (_IsOccurred == true)
			{
				ThrowException(_ClassName, _ExceptionType);
			}
		}
		catch (std::exception& _Error)
		{
			std::cerr << _Error.what() << std::endl;
			assert(_DoAssert);
		}
	}

private:
	static void ThrowException(const char* _ClassName, ExceptionType _ExceptionType)
	{
		switch (_ExceptionType)
		{
		case ExceptionType::OutOfRange:
			throw CustomException::OutOfLange(_ClassName);
			break;
		case ExceptionType::EmptyContainer:
			throw CustomException::EmptyContainer(_ClassName);
			break;
		}
	}

};