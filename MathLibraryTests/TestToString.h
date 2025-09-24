#pragma once

#include <iomanip>
#include <limits>
#include <string>
#include <sstream>

#include "CppUnitTestAssert.h"
#include "MathLibraryTests.h"

namespace Microsoft::VisualStudio::CppUnitTestFramework {
	using MathClasses::Vector2;
	using MathClasses::Vector3;
//	using MathClasses::Vector4;
	using MathClasses::Matrix3;
//	using MathClasses::Matrix4;
	using MathClasses::Color;

	namespace Detail
	{
		/// @return A wstringstream that writes floats at maximum precision.
		inline auto MakeWideStringStreamForFloats()
		{
			auto ss = std::wstringstream{};

			// Ensure floats are printed in maximum precision, so it's possible
			// to accurately compare expected and actual results.
			ss << std::setprecision(std::numeric_limits<float>::digits10 + 1);

			return ss;
		}
	}

	template<> inline std::wstring ToString<Vector2>(const Vector2& t)
	{
		auto ss = Detail::MakeWideStringStreamForFloats();

		constexpr auto delimiter = L", ";
		ss << L"("
			<< t.x << delimiter
			<< t.y << L")";

		return ss.str();
	}

	template<> inline std::wstring ToString<Vector3>(const Vector3& t)
	{
		auto ss = Detail::MakeWideStringStreamForFloats();

		constexpr auto delimiter = L", ";
		ss << L"("
			<< t.x << delimiter
			<< t.y << delimiter
			<< t.z << L")";

		return ss.str();
	}

	//template<> inline std::wstring ToString<Vector4>(const Vector4& t)
	//{
	//	auto ss = Detail::MakeWideStringStreamForFloats();
	//
	//	constexpr auto delimiter = L", ";
	//	ss << L"("
	//		<< t.x << delimiter
	//		<< t.y << delimiter
	//		<< t.z << delimiter
	//		<< t.w << L")";
	//
	//	return ss.str();
	//}

	template<> inline std::wstring ToString<Matrix3>(const Matrix3& t)
	{
		auto ss = Detail::MakeWideStringStreamForFloats();

		// Print each column as a vector.
		constexpr auto delimiter = L", ";
		ss << L"["
			<< ToString(Vector3{ t.mm[0][0], t.mm[0][1], t.mm[0][2] }) << delimiter
			<< ToString(Vector3{ t.mm[1][0], t.mm[1][1], t.mm[1][2] }) << delimiter
			<< ToString(Vector3{ t.mm[2][0], t.mm[2][1], t.mm[2][2] }) << L"]";

		return ss.str();
	}

	//template<> inline std::wstring ToString<Matrix4>(const Matrix4& t)
	//{
	//	auto ss = Detail::MakeWideStringStreamForFloats();
	//
	//	// Print each column as a vector.
	//	constexpr auto delimiter = L", ";
	//	ss << L"["
	//		<< ToString(Vector4{ t.mm[0][0], t.mm[0][1], t.mm[0][2], t.mm[0][3] }) << delimiter
	//		<< ToString(Vector4{ t.mm[1][0], t.mm[1][1], t.mm[1][2], t.mm[1][3] }) << delimiter
	//		<< ToString(Vector4{ t.mm[2][0], t.mm[2][1], t.mm[2][2], t.mm[2][3] }) << delimiter
	//		<< ToString(Vector4{ t.mm[3][0], t.mm[3][1], t.mm[3][2], t.mm[3][3] }) << L"]";
	//
	//	return ss.str();
	//}

	template<> inline std::wstring ToString<Color>(const Color& t)
	{
		auto ss = std::wstringstream{};

		// Print each column as a vector.
		constexpr auto delimiter = L", ";
		ss << L"["
			<< (unsigned char)t.r << delimiter
			<< (unsigned char)t.g << delimiter
			<< (unsigned char)t.b << delimiter
			<< (unsigned char)t.a << L"]";

		return ss.str();
	}
}
