#pragma once
#include <exception>

class CustomException
{
public:
	class OutOfLange : public std::exception
	{
	public:
		OutOfLange()
		{

		}

		OutOfLange(const char* _ClassName)
		{
			ClassName = _ClassName;
		}

		const char* what() const noexcept override
		{
			static std::string ExMsg = "Exception is detected : OutOfLange\nClassName : " + ClassName;
			return ExMsg.c_str();
		}

	private:
		std::string ClassName = "";
	};
};