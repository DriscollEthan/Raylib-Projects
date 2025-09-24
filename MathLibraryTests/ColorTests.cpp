#include "CppUnitTest.h"

#include "MathLibraryTests.h"
#include "MathUnitTestAssert.h"
#include "TestToString.h"

#include "Utils.h"
#include "Color.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using ::MathClasses::Color;

namespace MathLibraryTests
{
	TEST_CLASS(ColorTests)
	{
	public:
		// equality
		TEST_METHOD(OperatorEquality)
		{
			Color colorA;
			colorA.r = 255;
			colorA.b = 128;
			colorA.g = 64;
			colorA.a = 32;

			Color colorB;
			colorB.r = 255;
			colorB.b = 128;
			colorB.g = 64;
			colorB.a = 32;

			Color colorC;
			colorC.r = 16;
			colorC.b = 8;
			colorC.g = 4;
			colorC.a = 2;

			Assert::AreEqual(colorA, colorB);
			Assert::AreEqual(colorB, colorA);
			Assert::AreEqual(colorC, colorC);
			Assert::AreNotEqual(colorA, colorC);
			Assert::AreNotEqual(colorC, colorA);
			Assert::AreNotEqual(colorB, colorC);
			Assert::AreNotEqual(colorC, colorB);
		}

		TEST_METHOD(OperatorInequality)
		{
			Color colorA;
			colorA.r = 255;
			colorA.b = 128;
			colorA.g = 64;
			colorA.a = 32;

			Color colorB;
			colorB.r = 16;
			colorB.b = 8;
			colorB.g = 4;
			colorB.a = 2;

			Color colorA_duplicate;
			colorA_duplicate.r = 255;
			colorA_duplicate.b = 128;
			colorA_duplicate.g = 64;
			colorA_duplicate.a = 32;

			Assert::IsTrue(colorA != colorB);
			Assert::IsTrue(colorB != colorA);
			Assert::IsFalse(colorA != colorA_duplicate);
		}

		// default constructor
		TEST_METHOD(ConstructorDefault)
		{
			Color actual;

			Assert::AreEqual(Color(0, 0, 0, 0), actual);
		}

		// parameterized constructor
		TEST_METHOD(ConstructorRGBA)
		{
			Color actual(32, 64, 0, 255);

			Assert::AreEqual(Color(32, 64, 0, 255), actual);
		}

		// setting r
		TEST_METHOD(SetRed)
		{
			Color actual(32, 64, 0, 255);

			actual.r = 128;

			Assert::AreEqual(Color(128, 64, 0, 255), actual);
		}

		// setting g
		TEST_METHOD(SetGreen)
		{
			Color actual(32, 64, 0, 255);

			actual.g = 128;

			Assert::AreEqual(Color(32, 128, 0, 255), actual);
		}

		// setting b
		TEST_METHOD(SetBlue)
		{
			Color actual(32, 64, 0, 255);

			actual.b = 128;

			Assert::AreEqual(Color(32, 64, 128, 255), actual);
		}

		// setting a
		TEST_METHOD(SetAlpha)
		{
			Color actual(32, 64, 0, 255);

			actual.a = 128;

			Assert::AreEqual(Color(32, 64, 0, 128), actual);
		}

		TEST_METHOD(ColorChangesWithMacros)
		{
			Color actual = ORANGE;
			Assert::AreEqual(Color(255, 165, 0, 255), actual);

			actual = PINK;
			Assert::AreEqual(Color(255, 77, 255, 255), actual);

			actual = YELLOW;
			Assert::AreEqual(Color(255, 255, 0, 255), actual);
		}

		TEST_METHOD(Char8ToInt32)
		{
			Color actual = (94, 0, 0, 0);

			Assert::AreEqual(Color(1577058304), actual);
		}
	};
}
