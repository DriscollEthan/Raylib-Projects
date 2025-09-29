#include "CppUnitTest.h"

#include "MathLibraryTests.h"
#include "MathUnitTestAssert.h"
#include "TestToString.h"

#include "Utils.h"
#include "Vector3D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using aie::test::CustomAssert;
using MathClasses::Vector3;
using Driscoll::ApproximatelyEquals;
using Driscoll::MAX_FLOAT_DELTA;

namespace MathLibraryTests
{
	TEST_CLASS(Vector3Tests)
	{
	public:

		TEST_METHOD(OperatorEquality)
		{
			Vector3 vecA;
			vecA.x = 1;
			vecA.y = 2;
			vecA.z = 3;

			Vector3 vecB;
			vecB.x = 1;
			vecB.y = 2;
			vecB.z = 3;

			Vector3 vecC;
			vecC.x = 3;
			vecC.y = 2;
			vecC.z = 1;

			Assert::AreEqual(vecA, vecB);
			Assert::AreEqual(vecB, vecA);
			Assert::AreNotEqual(vecA, vecC);
			Assert::AreNotEqual(vecC, vecA);
		}
		TEST_METHOD(OperatorInequality)
		{
			Vector3 v3a(1, 2, 3);
			Vector3 v3b(4, 5, 6);

			Vector3 v3a_duplicate(1, 2, 3);

			CustomAssert::AreInequal(v3a, v3b);
			CustomAssert::AreInequal(v3b, v3a); // (symmetric)

			CustomAssert::AreNotInequal(v3a, v3a_duplicate);
		}

		TEST_METHOD(EqualsFunction)
		{
			Vector3 vecA;
			vecA.x = 1;
			vecA.y = 2;
			vecA.z = 3;

			Vector3 vecB;
			vecB.x = 1;
			vecB.y = 2;
			vecB.z = 3;

			Vector3 vecC;
			vecC.x = 4;
			vecC.y = 5;
			vecC.z = 6;

			CustomAssert::AreEqualsMember(vecA, vecB);		// TRUE, two equivalent values
			CustomAssert::AreEqualsMember(vecB, vecA);		// TRUE, symmetric
			CustomAssert::AreNotEqualsMember(vecA, vecC);
			CustomAssert::AreNotEqualsMember(vecC, vecA);
		}
		TEST_METHOD(ConstructorDefault)
		{
			Vector3 vec;
			Assert::AreEqual(0.f, vec.x);
			Assert::AreEqual(0.f, vec.y);
			Assert::AreEqual(0.f, vec.z);
		}

		TEST_METHOD(ConstructorFloat)
		{
			Vector3 vec(1.f, 2.f, 3.f);
			Assert::AreEqual(1.f, vec.x);
			Assert::AreEqual(2.f, vec.y);
			Assert::AreEqual(3.f, vec.z);
		}

		TEST_METHOD(Magnitude)
		{
			Vector3 v3a(13.5f, -48.23f, 862);
			float mag3 = v3a.Magnitude();
			Assert::AreEqual(863.453735352f, mag3, MAX_FLOAT_DELTA);

			Vector3 v3b(0, 0, 0);
			mag3 = v3b.Magnitude();
			Assert::AreEqual(0.f, mag3, MAX_FLOAT_DELTA);
		}

		TEST_METHOD(Normalised)
		{
			Vector3 v3a(13.5f, -48.23f, 862);
			CustomAssert::AreEqualsMember(Vector3(0.0156349f, -0.0558571f, 0.998316f), v3a.Normalised());
		}

		TEST_METHOD(Normalise)
		{
			Vector3 v3a(13.5f, -48.23f, 862);
			v3a.Normalise();
			CustomAssert::AreEqualsMember(Vector3(0.0156349f, -0.0558571f, 0.998316f), v3a);
		}

		TEST_METHOD(Dot)
		{
			Vector3 v3a(13.5f, -48.23f, 862);
			Vector3 v3b(5, 3.99f, -12);
			float dot3 = v3a.Dot(v3b);

			Assert::AreEqual(-10468.9375f, dot3, MAX_FLOAT_DELTA);


			Vector3 v3c(0, 0, 0);
			Vector3 v3d(5, 3.99f, -12);
			dot3 = v3c.Dot(v3d);

			Assert::AreEqual(0.0f, dot3, MAX_FLOAT_DELTA);
		}

		TEST_METHOD(Cross)
		{
			Vector3 v3a(13.5f, -48.23f, 862);
			Vector3 v3b(5, 3.99f, -12);
			Vector3 v3c = v3a.Cross(v3b);

			CustomAssert::AreEqualsMember(Vector3(-2860.62011719f, 4472.00000000f, 295.01498413f), v3c);
		}
	};

	TEST_CLASS(Vector3Tests_Operator)
	{
		TEST_METHOD(Add)
		{
			Vector3 v3a(13.5f, -48.23f, 862);
			Vector3 v3b(5, 3.99f, -12);
			Vector3 v3c = v3a + v3b;

			CustomAssert::AreEqualsMember(Vector3(18.5f, -44.24f, 850), v3c);
		}

		TEST_METHOD(AddAssign)
		{
			Vector3 v3a(13.5f, -48.23f, 862);
			Vector3 v3b(5, 3.99f, -12);
			v3a += v3b;

			CustomAssert::AreEqualsMember(Vector3(18.5f, -44.24f, 850), v3a);
		}

		TEST_METHOD(Subtract)
		{
			Vector3 v3a(13.5f, -48.23f, 862);
			Vector3 v3b(5, 3.99f, -12);
			Vector3 v3c = v3a - v3b;

			CustomAssert::AreEqualsMember(Vector3(8.5f, -52.22f, 874), v3c);
		}

		TEST_METHOD(SubtractAssign)
		{
			Vector3 v3a(13.5f, -48.23f, 862);
			Vector3 v3b(5, 3.99f, -12);
			v3a -= v3b;

			CustomAssert::AreEqualsMember(Vector3(8.5f, -52.22f, 874), v3a);
		}

		TEST_METHOD(MultiplyVectorScalar)
		{
			Vector3 v3a(13.5f, -48.23f, 862);
			Vector3 v3c = v3a * 0.256f;

			CustomAssert::AreEqualsMember(Vector3(3.45600008965f, -12.3468809128f, 220.672012329f), v3c);
		}

		TEST_METHOD(MultiplyVectorScalarAssign)
		{
			Vector3 v3a(13.5f, -48.23f, 862);
			v3a *= 0.256f;

			CustomAssert::AreEqualsMember(Vector3(3.45600008965f, -12.3468809128f, 220.672012329f), v3a);
		}

		TEST_METHOD(MultiplyScalarVector)
		{
			Vector3 v3a(13.5f, -48.23f, 862);
			Vector3 v3c = 0.256f * v3a;

			CustomAssert::AreEqualsMember(Vector3(3.45600008965f, -12.3468809128f, 220.672012329f), v3c);
		}

		TEST_METHOD(ScalarDivide)
		{
			Vector3 v3a(13.5f, -48.23f, 862);
			Vector3 v3c = v3a / 0.256f;

			CustomAssert::AreEqualsMember(Vector3(52.734371f, -188.398422f, 3367.187256f), v3c);
		}

		TEST_METHOD(ScalarDivideAssign)
		{
			Vector3 v3a(13.5f, -48.23f, 862);
			v3a /= 0.256f;

			CustomAssert::AreEqualsMember(Vector3(52.734371f, -188.398422f, 3367.187256f), v3a);
		}
	};
}

namespace MathLibraryTests_OPTIONAL
{
	TEST_CLASS(Vector3Tests_Optional)
	{
		TEST_METHOD(SafeNormalise)
		{
			Vector3 v3b(0, 0, 0);
			v3b.SafeNormalise();
			CustomAssert::AreEqualsMember(Vector3(0, 0, 0), v3b);
		}

		TEST_METHOD(SafeNormalised)
		{
			Vector3 v3b(0, 0, 0);
			CustomAssert::AreEqualsMember(Vector3(0, 0, 0), v3b.SafeNormalised());
		}
	};
//
//	TEST_CLASS(Vector3Tests_Optional_Operator)
//	{
//		TEST_METHOD(Subscript)
//		{
//			Vector3 v3a(0, 0, 0);
//			v3a[0] = 3;
//			Assert::AreEqual(v3a[0], 3.f);
//			v3a[1] = 4;
//			Assert::AreEqual(v3a[1], 4.f);
//			v3a[2] = 6;
//			Assert::AreEqual(v3a[2], 6.f);
//		}
//
//		TEST_METHOD(SubscriptReference)
//		{
//			const Vector3 v3a(13.5f, -48.23f, 862);
//		
//			Assert::AreEqual(v3a[0], 13.5f);
//			Assert::AreEqual(v3a[1], -48.23f);
//			Assert::AreEqual(v3a[2], 862.f);
//		}
//
//		TEST_METHOD(Cast)
//		{
//			Vector3 v3a(10, 2, 6);
//		
//			float* ptrMutable = (float*)v3a;
//			Assert::AreEqual(ptrMutable[0], 10.f);
//			Assert::AreEqual(ptrMutable[1], 2.f);
//			Assert::AreEqual(ptrMutable[2], 6.f);
//		
//			const float* ptrConst = (float*)v3a;
//			Assert::AreEqual(ptrConst[0], 10.f);
//			Assert::AreEqual(ptrConst[1], 2.f);
//			Assert::AreEqual(ptrConst[2], 6.f);
//		}
	}

