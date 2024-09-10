#pragma once

#include <iostream>
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

	class EmptyContainer : public std::exception
	{
	public:
		EmptyContainer()
		{

		}

		EmptyContainer(const char* _ClassName)
		{
			ClassName = _ClassName;
		}

		const char* what() const noexcept override
		{
			static std::string ExMsg = "Exception is detected : EmptyContainer\nClassName : " + ClassName;
			return ExMsg.c_str();
		}

	private:
		std::string ClassName = "";
	};
};