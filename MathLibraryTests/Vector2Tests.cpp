#include "CppUnitTest.h"

#include "MathLibraryTests.h"
#include "MathUnitTestAssert.h"
#include "TestToString.h"

#include "Utils.h"
#include "Vector2D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using aie::test::CustomAssert;
using MathClasses::Vector2;
using MathClasses::ApproximatelyEquals;
using MathClasses::MAX_FLOAT_DELTA;

namespace MathLibraryTests
{
	TEST_CLASS(Vector2Tests)
	{
	public:
		TEST_METHOD(OperatorEquality)
		{
			Vector2 v2a(13.5f, -48.23f);
			Vector2 v2b(13.5f, -48.23f);
			Vector2 v2flip(-48.23f, 13.5f);
			Vector2 v2zero(0.0f, 0.0f);

			Assert::AreEqual(v2a, v2a);			// TRUE, (reflexive)
			Assert::AreEqual(v2a, v2b);			// TRUE, two equivalent values
			Assert::AreEqual(v2b, v2a);			// TRUE, two equivalent values (symmetric)
			Assert::AreNotEqual(v2zero, v2a);	// FALSE, different values
			Assert::AreNotEqual(v2flip, v2a);	// FALSE, different values
		}
		TEST_METHOD(OperatorInequality)
		{
			Vector2 v2a(13.5f, -48.23f);
			Vector2 v2b(0.0f, 0.0f);

			CustomAssert::AreInequal(v2a, v2b);
			CustomAssert::AreInequal(v2b, v2a); // (symmetric)
		}

		TEST_METHOD(EqualsFunction)
		{
			Vector2 vecA;
			vecA.x = 1;
			vecA.y = 2;

			Vector2 vecB;
			vecB.x = 1;
			vecB.y = 2;

			Vector2 vecC;
			vecC.x = 3;
			vecC.y = 4;

			CustomAssert::AreEqualsMember(vecA, vecB);		// TRUE, two equivalent values
			CustomAssert::AreEqualsMember(vecB, vecA);		// TRUE, symmetric
			CustomAssert::AreNotEqualsMember(vecA, vecC);
			CustomAssert::AreNotEqualsMember(vecC, vecA);
		}

		TEST_METHOD(ConstructorDefault)
		{
			Vector2 vec;
			Assert::AreEqual(0.f, vec.x);
			Assert::AreEqual(0.f, vec.y);
		}

		TEST_METHOD(ConstructorFloat)
		{
			Vector2 vec(1.f, 2.f);
			Assert::AreEqual(1.f, vec.x);
			Assert::AreEqual(2.f, vec.y);
		}

		TEST_METHOD(Magnitude)
		{
			Vector2 v2a(13.5f, -48.23f);
			float mag2 = v2a.Magnitude();
			Assert::AreEqual(50.0838f, mag2, MathClasses::MAX_FLOAT_DELTA);
		}

		TEST_METHOD(Normalised)
		{
			Vector2 v2a(13.5f, -48.23f);
			CustomAssert::AreEqualsMember(Vector2(0.269548f, -0.962987f), v2a.Normalised());
		}

		TEST_METHOD(Normalise)
		{
			Vector2 v2a(13.5f, -48.23f);
			v2a.Normalise();
			CustomAssert::AreEqualsMember(Vector2(0.269548f, -0.962987f), v2a);
		}

		TEST_METHOD(Dot)
		{
			Vector2 v2a(13.5f, -48.23f);
			Vector2 v2b(5, 3.99f);
			float dot3 = v2a.Dot(v2b);

			Assert::AreEqual(-124.9377f, dot3, MAX_FLOAT_DELTA);


			Vector2 v2c(0, 0);
			Vector2 v2d(5, 3.99f);
			dot3 = v2c.Dot(v2d);

			Assert::AreEqual(0.0f, dot3, MAX_FLOAT_DELTA);
		}
	};

	TEST_CLASS(Vector2Tests_Operator)
	{
		TEST_METHOD(Add)
		{
			Vector2 v2a(13.5f, -48.23f);
			Vector2 v2b(5, 3.99f);
			Vector2 v2c = v2a + v2b;

			CustomAssert::AreEqualsMember(Vector2(18.5f, -44.24f), v2c);
		}

		TEST_METHOD(AddAssign)
		{
			Vector2 v2a(13.5f, -48.23f);
			Vector2 v2b(5, 3.99f);
			v2a += v2b;

			CustomAssert::AreEqualsMember(Vector2(18.5f, -44.24f), v2a);
		}

		TEST_METHOD(Subtract)
		{
			Vector2 v2a(13.5f, -48.23f);
			Vector2 v2b(5, 3.99f);
			Vector2 v2c = v2a - v2b;

			CustomAssert::AreEqualsMember(Vector2(8.5f, -52.22f), v2c);
		}

		TEST_METHOD(SubtractAssign)
		{
			Vector2 v2a(13.5f, -48.23f);
			Vector2 v2b(5, 3.99f);
			v2a -= v2b;

			CustomAssert::AreEqualsMember(Vector2(8.5f, -52.22f), v2a);
		}

		TEST_METHOD(MultiplyVectorScalar)
		{
			Vector2 v2a(13.5f, -48.23f);
			Vector2 v2c = v2a * 0.256f;

			CustomAssert::AreEqualsMember(Vector2(3.45600008965f, -12.3468809128f), v2c);
		}

		TEST_METHOD(MultiplyVectorScalarAssign)
		{
			Vector2 v2a(13.5f, -48.23f);
			v2a *= 0.256f;

			CustomAssert::AreEqualsMember(Vector2(3.45600008965f, -12.3468809128f), v2a);
		}

		TEST_METHOD(MultiplyScalarVector)
		{
			Vector2 v2a(13.5f, -48.23f);
			Vector2 v2c = 0.256f * v2a;

			CustomAssert::AreEqualsMember(Vector2(3.45600008965f, -12.3468809128f), v2c);
		}

		TEST_METHOD(DivideScalar)
		{
			Vector2 v2a(13.5f, -48.23f);
			Vector2 v2c = v2a / 0.256f;

			CustomAssert::AreEqualsMember(Vector2(52.734371f, -188.398422f), v2c);
		}

		TEST_METHOD(DivideScalarAssign)
		{
			Vector2 v2a(10, 2);

			float* p = (float*)v2a;
			Assert::AreEqual(p[0], 10.f);
			Assert::AreEqual(p[1], 2.f);

			const float* q = (float*)v2a;
			Assert::AreEqual(q[0], 10.f);
			Assert::AreEqual(q[1], 2.f);
		}
	};
}

namespace MathLibraryTests_OPTIONAL
{
	TEST_CLASS(Vector2Tests_Optional)
	{
		TEST_METHOD(SafeNormalise)
		{
			Vector2 v2b(0, 0);
			v2b.SafeNormalise();
			CustomAssert::AreEqualsMember(Vector2(0, 0), v2b);
		}

		TEST_METHOD(SafeNormalised)
		{
			Vector2 v2b(0, 0);
			CustomAssert::AreEqualsMember(Vector2(0, 0), v2b.SafeNormalised());
		}
	};

	TEST_CLASS(Vector2Tests_Optional_Operator)
	{
		TEST_METHOD(Subscript)
		{
			const Vector2 v2a(13.5f, -48.23f);

			Assert::AreEqual(v2a[0], 13.5f);
			Assert::AreEqual(v2a[1], -48.23f);
		}

		TEST_METHOD(SubscriptReference)
		{
			Vector2 v2a(0, 0);
			v2a[0] = 3.f;
			Assert::AreEqual(v2a[0], 3.f);
			v2a[1] = 4.f;
			Assert::AreEqual(v2a[1], 4.f);
		}

		TEST_METHOD(Cast)
		{
			Vector2 v2a(10.f, 2.f);

			float* ptrMutable = (float*)v2a;
			Assert::AreEqual(ptrMutable[0], 10.f);
			Assert::AreEqual(ptrMutable[1], 2.f);

			const float* ptrConst = (float*)v2a;
			Assert::AreEqual(ptrConst[0], 10.f);
			Assert::AreEqual(ptrConst[1], 2.f);
		}
	};
}
