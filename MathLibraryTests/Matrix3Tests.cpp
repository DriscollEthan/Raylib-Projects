#include "CppUnitTest.h"

#include "MathLibraryTests.h"
#include "MathUnitTestAssert.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using aie::test::CustomAssert;
using MathClasses::Vector3;
using MathClasses::Matrix3;

namespace MathLibraryTests
{
	TEST_CLASS(Matrix3Tests)
	{
	public:
		TEST_METHOD(OperatorEquality)
		{
			Matrix3 matA;
			matA.m1 = 1;
			matA.m2 = 2;
			matA.m3 = 3;

			matA.m4 = 4;
			matA.m5 = 5;
			matA.m6 = 6;

			matA.m7 = 7;
			matA.m8 = 8;
			matA.m9 = 9;

			Matrix3 matB;
			matB.m1 = 1;
			matB.m2 = 2;
			matB.m3 = 3;

			matB.m4 = 4;
			matB.m5 = 5;
			matB.m6 = 6;

			matB.m7 = 7;
			matB.m8 = 8;
			matB.m9 = 9;

			Matrix3 matC;
			matC.m1 = 10;
			matC.m2 = 11;
			matC.m3 = 12;

			matC.m4 = 13;
			matC.m5 = 14;
			matC.m6 = 15;

			matC.m7 = 16;
			matC.m8 = 17;
			matC.m9 = 18;

			Assert::AreEqual(matA, matB);
			Assert::AreEqual(matB, matA);
			Assert::AreNotEqual(matA, matC);
			Assert::AreNotEqual(matC, matA);
		}

		TEST_METHOD(OperatorInequality)
		{
			Matrix3 matA;
			matA.m1 = 1;
			matA.m2 = 2;
			matA.m3 = 3;

			matA.m4 = 4;
			matA.m5 = 5;
			matA.m6 = 6;

			matA.m7 = 7;
			matA.m8 = 8;
			matA.m9 = 9;

			Matrix3 matB;
			matB.m1 = 10;
			matB.m2 = 11;
			matB.m3 = 12;

			matB.m4 = 13;
			matB.m5 = 14;
			matB.m6 = 15;

			matB.m7 = 16;
			matB.m8 = 17;
			matB.m9 = 18;

			Matrix3 matA_duplicate;
			matA_duplicate.m1 = 1;
			matA_duplicate.m2 = 2;
			matA_duplicate.m3 = 3;

			matA_duplicate.m4 = 4;
			matA_duplicate.m5 = 5;
			matA_duplicate.m6 = 6;

			matA_duplicate.m7 = 7;
			matA_duplicate.m8 = 8;
			matA_duplicate.m9 = 9;

			CustomAssert::AreInequal(matA, matB);
			CustomAssert::AreInequal(matB, matA); // (symmetric)

			CustomAssert::AreNotInequal(matA, matA_duplicate);
		}

		TEST_METHOD(EqualsFunction)
		{
			Matrix3 matA;
			matA.m1 = 1;
			matA.m2 = 2;
			matA.m3 = 3;

			matA.m4 = 4;
			matA.m5 = 5;
			matA.m6 = 6;

			matA.m7 = 7;
			matA.m8 = 8;
			matA.m9 = 9;

			Matrix3 matB;
			matB.m1 = 1;
			matB.m2 = 2;
			matB.m3 = 3;

			matB.m4 = 4;
			matB.m5 = 5;
			matB.m6 = 6;

			matB.m7 = 7;
			matB.m8 = 8;
			matB.m9 = 9;

			Matrix3 matC;
			matC.m1 = 10;
			matC.m2 = 11;
			matC.m3 = 12;

			matC.m4 = 13;
			matC.m5 = 14;
			matC.m6 = 15;

			matC.m7 = 16;
			matC.m8 = 17;
			matC.m9 = 18;

			CustomAssert::AreEqualsMember(matA, matB);
			CustomAssert::AreEqualsMember(matB, matA);
			CustomAssert::AreNotEqualsMember(matA, matC);
			CustomAssert::AreNotEqualsMember(matC, matA);
		}

		TEST_METHOD(ConstructorDefault)
		{
			Matrix3 mat;

			Assert::AreEqual(0.f, mat.m1);
			Assert::AreEqual(0.f, mat.m2);
			Assert::AreEqual(0.f, mat.m3);

			Assert::AreEqual(0.f, mat.m4);
			Assert::AreEqual(0.f, mat.m5);
			Assert::AreEqual(0.f, mat.m6);

			Assert::AreEqual(0.f, mat.m7);
			Assert::AreEqual(0.f, mat.m8);
			Assert::AreEqual(0.f, mat.m9);
		}

		TEST_METHOD(ConstructorFloat)
		{
			Matrix3 mat(1.f, 2.f, 3.f,
				4.f, 5.f, 6.f,
				7.f, 8.f, 9.f);

			Assert::AreEqual(1.f, mat.m1);
			Assert::AreEqual(2.f, mat.m2);
			Assert::AreEqual(3.f, mat.m3);

			Assert::AreEqual(4.f, mat.m4);
			Assert::AreEqual(5.f, mat.m5);
			Assert::AreEqual(6.f, mat.m6);

			Assert::AreEqual(7.f, mat.m7);
			Assert::AreEqual(8.f, mat.m8);
			Assert::AreEqual(9.f, mat.m9);
		}

		TEST_METHOD(ConstructorArray)
		{
			float numbers[] =
			{
				1.f, 2.f, 3.f,
				4.f, 5.f, 6.f,
				7.f, 8.f, 9.f
			};
			Matrix3 mat(numbers);

			Assert::AreEqual(1.f, mat.m1);
			Assert::AreEqual(2.f, mat.m2);
			Assert::AreEqual(3.f, mat.m3);

			Assert::AreEqual(4.f, mat.m4);
			Assert::AreEqual(5.f, mat.m5);
			Assert::AreEqual(6.f, mat.m6);

			Assert::AreEqual(7.f, mat.m7);
			Assert::AreEqual(8.f, mat.m8);
			Assert::AreEqual(9.f, mat.m9);
		}
		TEST_METHOD(MakeIdentity)
		{
			Matrix3 mat = Matrix3::MakeIdentity();

			Assert::AreEqual(1.f, mat.m1);
			Assert::AreEqual(0.f, mat.m2);
			Assert::AreEqual(0.f, mat.m3);

			Assert::AreEqual(0.f, mat.m4);
			Assert::AreEqual(1.f, mat.m5);
			Assert::AreEqual(0.f, mat.m6);

			Assert::AreEqual(0.f, mat.m7);
			Assert::AreEqual(0.f, mat.m8);
			Assert::AreEqual(1.f, mat.m9);
		}
	};

	TEST_CLASS(Matrix3Tests_Operator)
	{
		// mat3 * mat3
		TEST_METHOD(MultiplyMat3Mat3)
		{
			Matrix3 m3a(1, 3, 1, 2, 2, 2, 3, 1, 3);
			Matrix3 m3c(4, 6, 4, 5, 5, 6, 6, 4, 5);

			Matrix3 m3d = m3a * m3c;

			CustomAssert::AreEqualsMember(Matrix3(28, 28, 28, 33, 31, 33, 29, 31, 29), m3d);
		}
		// mat3 * mat3
		TEST_METHOD(MultiplyMat3Mat3Assign)
		{
			Matrix3 m3a(1, 3, 1, 2, 2, 2, 3, 1, 3);
			Matrix3 m3c(4, 6, 4, 5, 5, 6, 6, 4, 5);

			m3a *= m3c;

			CustomAssert::AreEqualsMember(Matrix3(28, 28, 28, 33, 31, 33, 29, 31, 29), m3a);
		}
		// mat3 * vec
		TEST_METHOD(MultiplyMat3Vec3)
		{
			Matrix3 m3b(-0.188076824f, 0.f, 0.982154310f,
				0.f, 1.f, 0.f,
				-0.982154310f, 0.f, -0.188076824f);

			Vector3 v3a(13.5f, -48.23f, 862);
			Vector3 v3b = m3b * v3a;

			CustomAssert::AreEqualsMember(Vector3(-849.156067f, -48.23f, -148.863144f), v3b);
		}

		TEST_METHOD(MultiplyMat3Vec2)
		{
			Matrix3 m3b(1,0,0, 0,1,0, 10,11,1);

			Vector2 v2a(13.5f, -48.23f);
			Vector2 v2b = m3b * v2a;

			CustomAssert::AreEqualsMember(Vector2(23.5f, -37.23f), v2b);
		}

		TEST_METHOD(MultiplyMat3Vec2_2)
		{
			// effectively rotates by 90 degrees (or PI/2)
			Matrix3 m3b(
			0.0,
			1.0,
			0.0,

			-1.0,
			0,
			0.0,

			0.0,
			0.0,
			1.0);

			Vector2 v2a(1.0f, 0.0f);
			Vector2 v2b = m3b * v2a;

			CustomAssert::AreEqualsMember(Vector2(0.0f, 1.0f), v2b);
		}
	};
}

namespace MathLibraryTests_OPTIONAL
{
	TEST_CLASS(Matrix3Tests_Optional)
	{
		TEST_METHOD(Transposed)
		{
			Matrix3 m3a(1, 2, 3,
				4, 5, 6,
				7, 8, 9);

			m3a = m3a.Transposed();

			Assert::AreEqual(Matrix3(1, 4, 7, 2, 5, 8, 3, 6, 9), m3a);
		}
	};

	TEST_CLASS(Matrix3Tests_Optional_Operator)
	{
		TEST_METHOD(SubscriptReference)
		{
			Matrix3 m3a(1, 4, 1,
						2, 3, 2,
						3, 2, 3);

			Assert::AreEqual(m3a[0], 1.f);
			Assert::AreEqual(m3a[1], 4.f);
			Assert::AreEqual(m3a[2], 1.f);

			Assert::AreEqual(m3a[3], 2.f);
			Assert::AreEqual(m3a[4], 3.f);
			Assert::AreEqual(m3a[5], 2.f);

			Assert::AreEqual(m3a[6], 3.f);
			Assert::AreEqual(m3a[7], 2.f);
			Assert::AreEqual(m3a[8], 3.f);
		}

		TEST_METHOD(Subscript)
		{
			Matrix3 m3a(1, 4, 1,
				2, 3, 2,
				3, 2, 3);

			int i = 0;
			for (int c = 0; c < 3; ++c)
			{
				for (int r = 0; r < 3; ++r)
				{
					const int v = i;
					m3a.mm[c][r] = (float)v;
					Assert::AreEqual(m3a[c * 3 + r], (float)i);
					i += 5;
				}
			}
		}

		TEST_METHOD(Cast)
		{
			Matrix3 m3a(1, 4, 1,
				2, 3, 2,
				3, 2, 3);

			float* ptrMutable = (float*)m3a;
			m3a[0] = m3a[0];
			Assert::AreEqual(ptrMutable[0], 1.f);
			Assert::AreEqual(ptrMutable[1], 4.f);
			Assert::AreEqual(ptrMutable[2], 1.f);

			Assert::AreEqual(ptrMutable[3], 2.f);
			Assert::AreEqual(ptrMutable[4], 3.f);
			Assert::AreEqual(ptrMutable[5], 2.f);

			Assert::AreEqual(ptrMutable[6], 3.f);
			Assert::AreEqual(ptrMutable[7], 2.f);
			Assert::AreEqual(ptrMutable[8], 3.f);

			const float* ptrConst = (float*)m3a;
			Assert::AreEqual(ptrConst[0], 1.f);
			Assert::AreEqual(ptrConst[1], 4.f);
			Assert::AreEqual(ptrConst[2], 1.f);

			Assert::AreEqual(ptrConst[3], 2.f);
			Assert::AreEqual(ptrConst[4], 3.f);
			Assert::AreEqual(ptrConst[5], 2.f);

			Assert::AreEqual(ptrConst[6], 3.f);
			Assert::AreEqual(ptrConst[7], 2.f);
			Assert::AreEqual(ptrConst[8], 3.f);
		}
	};
}
