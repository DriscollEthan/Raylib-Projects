#pragma once

#include "CppUnitTestAssert.h"

#include "MathLibraryTests.h"

namespace aie { namespace test {

	// NOTE: Tempting as it may be to use a 'using' declaration here for the MSFT Assert class,
	//		 do NOT do it in a header.
	//
	//		 See: https://stackoverflow.com/questions/6175705/scope-of-using-declaration-within-a-namespace

	class CustomAssert
	{
	public:
		template<typename T> static void AreEqualsMember(const T& expected, const T& actual, const wchar_t* message = nullptr)
		{
			if (!expected.Equals(actual))
			{
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(GetFailMessage(expected, actual).c_str());
			}
		}

		template<typename T> static void AreNotEqualsMember(const T& expected, const T& actual, const wchar_t* message = nullptr)
		{
			if (expected.Equals(actual))
			{
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(GetFailMessage(expected, actual).c_str());
			}
		}

		template<typename T> static void AreNotEqualOperator(const T& expected, const T& actual, const wchar_t* message = nullptr)
		{
			if (!(expected != actual))
			{
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(GetFailMessage(expected, actual).c_str());
			}
		}

		template<typename T> static void AreInequal(const T& expected, const T& actual, const wchar_t* message = nullptr)
		{
			return AreNotEqualOperator(expected, actual, message);
		}

		template<typename T> static void AreNotInequal(const T& expected, const T& actual, const wchar_t* message = nullptr)
		{
			if (expected != actual)
			{
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(GetFailMessage(expected, actual).c_str());
			}
		}

	private:
		template<typename T> static std::wstring GetFailMessage(const T& expected, const T& actual, const wchar_t* message = nullptr)
		{
			std::wstringstream Msg;
			Msg << L"Assert failed. " << message << L"\nExpected:" << expected << L" Actual:" << actual;

			return Msg.str();
		}
	};
} }
