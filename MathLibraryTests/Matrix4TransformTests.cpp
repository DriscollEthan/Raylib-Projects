#include "CppUnitTest.h"

#include "MathLibraryTests.h"
#include "MathUnitTestAssert.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using aie::test::CustomAssert;
using MathClasses::Matrix4;
using MathClasses::Vector3;
using MathClasses::Vector4;

namespace MathLibraryTests
{
	TEST_CLASS(Matrix4Tests_Transform)
	{
	public:
		// make trans from floats
		TEST_METHOD(MakeTranslationFloats)
		{
			Matrix4 actual = Matrix4::MakeTranslation(2.0f, 3.0f, 4.0f);

			CustomAssert::AreEqualsMember(
				Matrix4(1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					2.f, 3.f, 4.f, 1), actual);
		}

		// make trans from vector
		TEST_METHOD(MakeTranslationVector)
		{
			Matrix4 actual = Matrix4::MakeTranslation(Vector3(2.0f, 3.0f, 4.0f));

			CustomAssert::AreEqualsMember(
				Matrix4(1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					2.f, 3.f, 4.f, 1), actual);
		}

		// make rotX from float
		TEST_METHOD(MakeRotateXFloat)
		{
			Matrix4 actual = Matrix4::MakeRotateX(4.5f);

			CustomAssert::AreEqualsMember(
				Matrix4(1, 0, 0, 0,
					0, -0.210796f, -0.97753f, 0,
					0, 0.97753f, -0.210796f, 0,
					0, 0, 0, 1), actual);
		}

		// make rotY from float
		TEST_METHOD(MakeRotateYFloat)
		{
			Matrix4 actual = Matrix4::MakeRotateY(-2.6f);

			CustomAssert::AreEqualsMember(
				Matrix4(-0.856889f, 0, 0.515501f, 0,
					0, 1, 0, 0,
					-0.515501f, 0, -0.856889f, 0,
					0, 0, 0, 1), actual);
		}

		// make rotZ from float
		TEST_METHOD(MakeRotateZFloat)
		{
			Matrix4 actual = Matrix4::MakeRotateZ(0.72f);

			CustomAssert::AreEqualsMember(
				Matrix4(0.751806f, 0.659385f, 0, 0,
					-0.659385f, 0.751806f, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1), actual);
		}

		/*
		 * Test that rotation around the x axis is right-handed.
		 */
		TEST_METHOD(MakeRotateXIsRightHanded)
		{
			// Construct a rotation of 90 degrees around the x axis.
			const auto angle = std::acos(0.0f);
			const auto rotation = Matrix3::MakeRotateX(angle);

			// Apply the rotation to the +ve y axis.
			const auto rotatedVector = rotation * Vector3{ 0, 1, 0 };

			// If the coordinate system is right-handed, the result
			// should align with the +ve z axis.
			const auto expectedVector = Vector3{ 0, 0, 1 };

			CustomAssert::AreEqualsMember(expectedVector, rotatedVector);
		}

		/*
		 * Test that rotation around the y axis is right-handed.
		 */
		TEST_METHOD(MakeRotateYIsRightHanded)
		{
			// Construct a rotation of 90 degrees around the y axis.
			const auto angle = std::acos(0.0f);
			const auto rotation = Matrix3::MakeRotateY(angle);

			// Apply the rotation to the +ve x axis.
			const auto rotatedVector = rotation * Vector3{ 1, 0, 0 };

			// If the coordinate system is right-handed, the result
			// should align with the -ve z axis.
			const auto expectedVector = Vector3{ 0, 0, -1 };

			CustomAssert::AreEqualsMember(expectedVector, rotatedVector);
		}

		/*
		 * Test that rotation around the z axis is right - handed.
		 */
		TEST_METHOD(MakeRotateZIsRightHanded)
		{
			// Construct a rotation of 90 degrees around the z axis.
			const auto angle = std::acos(0.0f);
			const auto rotation = Matrix3::MakeRotateZ(angle);

			// Apply the rotation to the +ve x axis.
			const auto rotatedVector = rotation * Vector3{ 1, 0, 0 };

			// If the coordinate system is right-handed, the result
			// should align with the +ve y axis.
			const auto expectedVector = Vector3{ 0, 1, 0 };

			CustomAssert::AreEqualsMember(expectedVector, rotatedVector);
		}

		// make rot from euler (floats)
		TEST_METHOD(MakeRotateEulerFloat)
		{
			Matrix4 actual = Matrix4::MakeEuler(Vector3(1.0f, 2.0f, 3.0f));

			CustomAssert::AreEqualsMember(
				Matrix4(0.411982f, -0.058727f, -0.909297f, 0.f,
					-0.833738f, -0.426918f, -0.350176f, 0.f,
					-0.367631f, 0.902382f, -0.224845f, 0.f,
					0.f, 0.f, 0.f, 1.f),
				actual);
		}

		// make rot from euler (vector)
		TEST_METHOD(MakeRotateEulerVector)
		{
			Matrix4 actual = Matrix4::MakeEuler(Vector3(1.0f, 2.0f, 3.0f));

			CustomAssert::AreEqualsMember(
				Matrix4(0.411982f, -0.058727f, -0.909297f, 0.f,
					-0.833738f, -0.426918f, -0.350176f, 0.f,
					-0.367631f, 0.902382f, -0.224845f, 0.f,
					0.f, 0.f, 0.f, 1.f),
				actual);
		}

		// make scale from floats
		TEST_METHOD(MakeScaleFloat3D)
		{
			Matrix4 actual = Matrix4::MakeScale(2.0f, 3.0f, 4.0f);

			CustomAssert::AreEqualsMember(
				Matrix4(2.0f, 0, 0, 0,
					0, 3.0f, 0, 0,
					0, 0, 4.0f, 0,
					0, 0, 0, 1), actual);

		}

		// make scale from vector
		TEST_METHOD(MakeScaleVector3)
		{
			Matrix4 actual = Matrix4::MakeScale(Vector3(2.0f, 3.0f, 4.0f));

			CustomAssert::AreEqualsMember(
				Matrix4(2.0f, 0, 0, 0,
					0, 3.0f, 0, 0,
					0, 0, 4.0f, 0,
					0, 0, 0, 1), actual);
		}
	};
}
