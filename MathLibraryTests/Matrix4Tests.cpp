#include "CppUnitTest.h"

#include "MathLibraryTests.h"
#include "MathUnitTestAssert.h"
#include "TestToString.h"

#include "DriscollMathUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using aie::test::CustomAssert;
using MathClasses::Matrix4;
using MathClasses::Vector4;

namespace MathLibraryTests
{
	TEST_CLASS(Matrix4Tests)
	{
	public:
		TEST_METHOD(OperatorEquality)
		{
			Matrix4 matA;
			matA.m1 = 1;
			matA.m2 = 2;
			matA.m3 = 3;
			matA.m4 = 4;
		
			matA.m5 = 5;
			matA.m6 = 6;
			matA.m7 = 7;
			matA.m8 = 8;
		
			matA.m9 = 9;
			matA.m10 = 10;
			matA.m11 = 11;
			matA.m12 = 12;
		
			matA.m13 = 13;
			matA.m14 = 14;
			matA.m15 = 15;
			matA.m16 = 16;
		
			Matrix4 matB;
			matB.m1 = 1;
			matB.m2 = 2;
			matB.m3 = 3;
			matB.m4 = 4;
		
			matB.m5 = 5;
			matB.m6 = 6;
			matB.m7 = 7;
			matB.m8 = 8;
		
			matB.m9 = 9;
			matB.m10 = 10;
			matB.m11 = 11;
			matB.m12 = 12;
		
			matB.m13 = 13;
			matB.m14 = 14;
			matB.m15 = 15;
			matB.m16 = 16;
		
			Matrix4 matC;
			matC.m1 = 17;
			matC.m2 = 18;
			matC.m3 = 19;
			matC.m4 = 20;
		
			matC.m5 = 21;
			matC.m6 = 22;
			matC.m7 = 23;
			matC.m8 = 24;
		
			matC.m9 = 25;
			matC.m10 = 26;
			matC.m11 = 27;
			matC.m12 = 28;
		
			matC.m13 = 29;
			matC.m14 = 30;
			matC.m15 = 31;
			matC.m16 = 32;
		
			Assert::AreEqual(matA, matB);
			Assert::AreEqual(matB, matA);
			Assert::IsTrue(!(matA == matC));
			Assert::IsTrue(!(matC == matA));
		}
		TEST_METHOD(OperatorInequality)
		{
			Matrix4 matA;
			matA.m1 = 1;
			matA.m2 = 2;
			matA.m3 = 3;
			matA.m4 = 4;
		
			matA.m5 = 5;
			matA.m6 = 6;
			matA.m7 = 7;
			matA.m8 = 8;
		
			matA.m9 = 9;
			matA.m10 = 10;
			matA.m11 = 11;
			matA.m12 = 12;
		
			matA.m13 = 13;
			matA.m14 = 14;
			matA.m15 = 15;
			matA.m16 = 16;
		
			Matrix4 matB;
			matB.m1 = 17;
			matB.m2 = 18;
			matB.m3 = 19;
			matB.m4 = 20;
		
			matB.m5 = 21;
			matB.m6 = 22;
			matB.m7 = 23;
			matB.m8 = 24;
		
			matB.m9 = 25;
			matB.m10 = 26;
			matB.m11 = 27;
			matB.m12 = 28;
		
			matB.m13 = 29;
			matB.m14 = 30;
			matB.m15 = 15;
			matB.m16 = 16;
		
			Matrix4 matA_duplicate;
			matA_duplicate.m1 = 1;
			matA_duplicate.m2 = 2;
			matA_duplicate.m3 = 3;
			matA_duplicate.m4 = 4;
		
			matA_duplicate.m5 = 5;
			matA_duplicate.m6 = 6;
			matA_duplicate.m7 = 7;
			matA_duplicate.m8 = 8;
		
			matA_duplicate.m9 = 9;
			matA_duplicate.m10 = 10;
			matA_duplicate.m11 = 11;
			matA_duplicate.m12 = 12;
		
			matA_duplicate.m13 = 13;
			matA_duplicate.m14 = 14;
			matA_duplicate.m15 = 15;
			matA_duplicate.m16 = 16;
		
			Assert::IsTrue(matA != matB);
			Assert::IsTrue(matB != matA); // (symmetric)
		
			Assert::IsFalse(matA != matA_duplicate);
		}
		TEST_METHOD(EqualsFunction)
		{
			Matrix4 matA;
			matA.m1 = 1;
			matA.m2 = 2;
			matA.m3 = 3;
			matA.m4 = 4;
		
			matA.m5 = 5;
			matA.m6 = 6;
			matA.m7 = 7;
			matA.m8 = 8;
		
			matA.m9 = 9;
			matA.m10 = 10;
			matA.m11 = 11;
			matA.m12 = 12;
		
			matA.m13 = 13;
			matA.m14 = 14;
			matA.m15 = 15;
			matA.m16 = 16;
		
			Matrix4 matB;
			matB.m1 = 1;
			matB.m2 = 2;
			matB.m3 = 3;
			matB.m4 = 4;
		
			matB.m5 = 5;
			matB.m6 = 6;
			matB.m7 = 7;
			matB.m8 = 8;
		
			matB.m9 = 9;
			matB.m10 = 10;
			matB.m11 = 11;
			matB.m12 = 12;
		
			matB.m13 = 13;
			matB.m14 = 14;
			matB.m15 = 15;
			matB.m16 = 16;
		
			Matrix4 matC;
			matC.m1 = 17;
			matC.m2 = 18;
			matC.m3 = 19;
			matC.m4 = 20;
		
			matC.m5 = 21;
			matC.m6 = 22;
			matC.m7 = 23;
			matC.m8 = 24;
		
			matC.m9 = 25;
			matC.m10 = 26;
			matC.m11 = 27;
			matC.m12 = 28;
		
			matC.m13 = 29;
			matC.m14 = 30;
			matC.m15 = 31;
			matC.m16 = 32;
		
			CustomAssert::AreEqualsMember(matA, matB);
			CustomAssert::AreEqualsMember(matB, matA);
			CustomAssert::AreNotEqualsMember(matA, matC);
			CustomAssert::AreNotEqualsMember(matC, matA);
		}
		// default constructor
		TEST_METHOD(Constructor)
		{
			Matrix4 mat;

			Assert::AreEqual(0.f, mat.m1);
			Assert::AreEqual(0.f, mat.m2);
			Assert::AreEqual(0.f, mat.m3);
			Assert::AreEqual(0.f, mat.m4);

			Assert::AreEqual(0.f, mat.m5);
			Assert::AreEqual(0.f, mat.m6);
			Assert::AreEqual(0.f, mat.m7);
			Assert::AreEqual(0.f, mat.m8);

			Assert::AreEqual(0.f, mat.m9);
			Assert::AreEqual(0.f, mat.m10);
			Assert::AreEqual(0.f, mat.m11);
			Assert::AreEqual(0.f, mat.m12);

			Assert::AreEqual(0.f, mat.m13);
			Assert::AreEqual(0.f, mat.m14);
			Assert::AreEqual(0.f, mat.m15);
			Assert::AreEqual(0.f, mat.m16);
		}
		// parameterized constructor (individual)
		TEST_METHOD(ConstructorFloat)
		{
			Matrix4 mat(1.0f, 2.0f, 3.0f, 4.0f,
				5.0f, 6.0f, 7.0f, 8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f);

			Assert::AreEqual(1.f, mat.m1);
			Assert::AreEqual(2.f, mat.m2);
			Assert::AreEqual(3.f, mat.m3);
			Assert::AreEqual(4.f, mat.m4);

			Assert::AreEqual(5.f, mat.m5);
			Assert::AreEqual(6.f, mat.m6);
			Assert::AreEqual(7.f, mat.m7);
			Assert::AreEqual(8.f, mat.m8);

			Assert::AreEqual(9.f, mat.m9);
			Assert::AreEqual(10.f, mat.m10);
			Assert::AreEqual(11.f, mat.m11);
			Assert::AreEqual(12.f, mat.m12);

			Assert::AreEqual(13.f, mat.m13);
			Assert::AreEqual(14.f, mat.m14);
			Assert::AreEqual(15.f, mat.m15);
			Assert::AreEqual(16.f, mat.m16);
		}
		// parameterized constructor (array)
		TEST_METHOD(ConstructorArray)
		{
			float numbers[] =
			{
				1.f, 2.f, 3.f, 4.f,
				5.f, 6.f, 7.f, 8.f,
				9.f, 10.f, 11.f, 12.f,
				13.f, 14.f, 15.f, 16.f
			};
			Matrix4 mat(numbers);

			Assert::AreEqual(1.f, mat.m1);
			Assert::AreEqual(2.f, mat.m2);
			Assert::AreEqual(3.f, mat.m3);
			Assert::AreEqual(4.f, mat.m4);

			Assert::AreEqual(5.f, mat.m5);
			Assert::AreEqual(6.f, mat.m6);
			Assert::AreEqual(7.f, mat.m7);
			Assert::AreEqual(8.f, mat.m8);

			Assert::AreEqual(9.f, mat.m9);
			Assert::AreEqual(10.f, mat.m10);
			Assert::AreEqual(11.f, mat.m11);
			Assert::AreEqual(12.f, mat.m12);

			Assert::AreEqual(13.f, mat.m13);
			Assert::AreEqual(14.f, mat.m14);
			Assert::AreEqual(15.f, mat.m15);
			Assert::AreEqual(16.f, mat.m16);
		}

		// make identity
		TEST_METHOD(MakeIdentity)
		{
			Matrix4 mat = Matrix4::MakeIdentity();

			Assert::AreEqual(1.f, mat.m1);
			Assert::AreEqual(0.f, mat.m2);
			Assert::AreEqual(0.f, mat.m3);
			Assert::AreEqual(0.f, mat.m4);

			Assert::AreEqual(0.f, mat.m5);
			Assert::AreEqual(1.f, mat.m6);
			Assert::AreEqual(0.f, mat.m7);
			Assert::AreEqual(0.f, mat.m8);

			Assert::AreEqual(0.f, mat.m9);
			Assert::AreEqual(0.f, mat.m10);
			Assert::AreEqual(1.f, mat.m11);
			Assert::AreEqual(0.f, mat.m12);


			Assert::AreEqual(0.f, mat.m13);
			Assert::AreEqual(0.f, mat.m14);
			Assert::AreEqual(0.f, mat.m15);
			Assert::AreEqual(1.f, mat.m16);
		}
	};

	TEST_CLASS(Matrix4Tests_Operator)
	{
	public:
		//mat4* vec4;
		TEST_METHOD(MultiplyMat4Vec4)
		{
			// homogeneous point translation
			Matrix4 m4b(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				55, 44, 99, 1);
		
			Vector4 v4a(13.5f, -48.23f, -54, 1);
		
			Vector4 actual = m4b * v4a;
			CustomAssert::AreEqualsMember(Vector4(68.5f, -4.23f, 45, 1), actual);
		}
		//mat4 * mat4
		TEST_METHOD(MultiplyMat4Mat4)
		{
			Matrix4 m4a(1, 4, 1, 7,
				2, 3, 2, 8,
				3, 2, 3, 9,
				4, 1, 4, 1);

			Matrix4 m4b(4, 7, 3, 4,
				5, 6, 4, 6,
				6, 5, 6, 8,
				7, 4, 5, 2);

			Matrix4 actual = m4a * m4b;

			CustomAssert::AreEqualsMember(Matrix4(43, 47, 43, 115,
				53, 52, 53, 125,
				66, 59, 66, 144,
				38, 52, 38, 128),
				actual);
		}
	};
}
namespace MathLibraryTests_OPTIONAL
{
	TEST_CLASS(Matrix4Tests_Optional)
	{
		//TEST_METHOD(Transposed)
		//{
		//	Matrix4 m4a(1, 2, 3, 4,
		//		5, 6, 7, 8,
		//		9, 10, 11, 12,
		//		13, 14, 15, 16);
		//
		//	m4a = m4a.Transposed();
		//
		//	CustomAssert::AreEqualsMember(Matrix4(1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16), m4a);
		//}
	};

	TEST_CLASS(Matrix4Tests_Optional_Operator)
	{
		//TEST_METHOD(SubscriptReference)
		//{
		//	Matrix4 m4a(1, 4, 1, 7,
		//		2, 3, 2, 8,
		//		3, 2, 3, 9,
		//		4, 1, 4, 1);
		//
		//	Assert::AreEqual(m4a[0], 1.f);
		//	Assert::AreEqual(m4a[1], 4.f);
		//	Assert::AreEqual(m4a[2], 1.f);
		//	Assert::AreEqual(m4a[3], 7.f);
		//
		//	Assert::AreEqual(m4a[4], 2.f);
		//	Assert::AreEqual(m4a[5], 3.f);
		//	Assert::AreEqual(m4a[6], 2.f);
		//	Assert::AreEqual(m4a[7], 8.f);
		//
		//	Assert::AreEqual(m4a[8], 3.f);
		//	Assert::AreEqual(m4a[9], 2.f);
		//	Assert::AreEqual(m4a[10], 3.f);
		//	Assert::AreEqual(m4a[11], 9.f);
		//
		//	Assert::AreEqual(m4a[12], 4.f);
		//	Assert::AreEqual(m4a[13], 1.f);
		//	Assert::AreEqual(m4a[14], 4.f);
		//	Assert::AreEqual(m4a[15], 1.f);
		//}
		//
		//TEST_METHOD(Subscript)
		//{
		//	Matrix4 m4a(1, 4, 1, 7,
		//		2, 3, 2, 8,
		//		3, 2, 3, 9,
		//		4, 1, 4, 1);
		//
		//	int i = 0;
		//	for (int c = 0; c < 4; ++c)
		//	{
		//		for (int r = 0; r < 4; ++r)
		//		{
		//			const int v = i;
		//			m4a.mm[c][r] = (float)v;
		//			Assert::AreEqual(m4a[c * 4 + r], (float)i);
		//			i += 5;
		//		}
		//	}
		//}
		//
		//TEST_METHOD(Cast)
		//{
		//	Matrix4 m4a(1, 4, 1, 7,
		//		2, 3, 2, 8,
		//		3, 2, 3, 9,
		//		4, 1, 4, 1);
		//
		//	float* ptrMutable = (float*)m4a;
		//	Assert::AreEqual(ptrMutable[0], 1.f);
		//	Assert::AreEqual(ptrMutable[1], 4.f);
		//	Assert::AreEqual(ptrMutable[2], 1.f);
		//	Assert::AreEqual(ptrMutable[3], 7.f);
		//
		//	Assert::AreEqual(ptrMutable[4], 2.f);
		//	Assert::AreEqual(ptrMutable[5], 3.f);
		//	Assert::AreEqual(ptrMutable[6], 2.f);
		//	Assert::AreEqual(ptrMutable[7], 8.f);
		//
		//	Assert::AreEqual(ptrMutable[8], 3.f);
		//	Assert::AreEqual(ptrMutable[9], 2.f);
		//	Assert::AreEqual(ptrMutable[10], 3.f);
		//	Assert::AreEqual(ptrMutable[11], 9.f);
		//
		//	Assert::AreEqual(ptrMutable[12], 4.f);
		//	Assert::AreEqual(ptrMutable[13], 1.f);
		//	Assert::AreEqual(ptrMutable[14], 4.f);
		//	Assert::AreEqual(ptrMutable[15], 1.f);
		//
		//	const float* ptrConst = (float*)m4a;
		//	Assert::AreEqual(ptrConst[0], 1.f);
		//	Assert::AreEqual(ptrConst[1], 4.f);
		//	Assert::AreEqual(ptrConst[2], 1.f);
		//	Assert::AreEqual(ptrConst[3], 7.f);
		//
		//	Assert::AreEqual(ptrConst[4], 2.f);
		//	Assert::AreEqual(ptrConst[5], 3.f);
		//	Assert::AreEqual(ptrConst[6], 2.f);
		//	Assert::AreEqual(ptrConst[7], 8.f);
		//
		//	Assert::AreEqual(ptrConst[8], 3.f);
		//	Assert::AreEqual(ptrConst[9], 2.f);
		//	Assert::AreEqual(ptrConst[10], 3.f);
		//	Assert::AreEqual(ptrConst[11], 9.f);
		//
		//	Assert::AreEqual(ptrConst[12], 4.f);
		//	Assert::AreEqual(ptrConst[13], 1.f);
		//	Assert::AreEqual(ptrConst[14], 4.f);
		//	Assert::AreEqual(ptrConst[15], 1.f);
		//}
	};
}
