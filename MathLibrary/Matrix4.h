#pragma once

#include "Matrix3.h"
#include "Vector4D.h"
#include "Vector3D.h"

namespace Driscoll
{
	struct Matrix4
	{
		/*
		 *		 c1 c2 c3 c4
		 *	r1  1  2  3  4
		 *	r2  5	 6	7  8
		 *	r3  9  10 11 12
		 *	r4  13 14 15 16
		 *
		 * =========
		 *
		 * m1 m5 m9  m13
		 * m2 m6 m10 m14
		 * m3 m7 m11 m15
		 * m4	m8 m12 m16
		 */

		union
		{
			// 16 individual in column-order
			struct
			{
				float m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16;
			};

			// 16-float-wide array in column-order
			float v[16];
			// every inner array represents a column
			float mm[4][4];
		};

		/**
		 * @brief
		 * @param inM1  Value for M1	| Default = 0
		 * @param inM2 	Value for M2	| Default = 0
		 * @param inM3 	Value for M3	| Default = 0
		 * @param inM4 	Value for M4	| Default = 0
		 * @param inM5 	Value for M5	| Default = 0
		 * @param inM6 	Value for M6	| Default = 0
		 * @param inM7 	Value for M7	| Default = 0
		 * @param inM8 	Value for M8	| Default = 0
		 * @param inM9 	Value for M9	| Default = 0
		 * @param inM10 Value for M10	| Default = 0
		 * @param inM11 Value for M11	| Default = 0
		 * @param inM12 Value for M12	| Default = 0
		 * @param inM13 Value for M13	| Default = 0
		 * @param inM14 Value for M14	| Default = 0
		 * @param inM15 Value for M15	| Default = 0
		 * @param inM16 Value for M16	| Default = 0
		 */
		Matrix4(float inM1 = 0.0f, float inM2 = 0.0f, float inM3 = 0.0f, float inM4 = 0.0f,
			float inM5 = 0.0f, float inM6 = 0.0f, float inM7 = 0.0f, float inM8 = 0.0f,
			float inM9 = 0.0f, float inM10 = 0.0f, float inM11 = 0.0f, float inM12 = 0.0f,
			float inM13 = 0.0f, float inM14 = 0.0f, float inM15 = 0.0f, float inM16 = 0.0f)
		{
			m1 = inM1;
			m2 = inM2;
			m3 = inM3;
			m4 = inM4;
			m5 = inM5;
			m6 = inM6;
			m7 = inM7;
			m8 = inM8;
			m9 = inM9;
			m10 = inM10;
			m11 = inM11;
			m12 = inM12;
			m13 = inM13;
			m14 = inM14;
			m15 = inM15;
			m16 = inM16;
		}

		/**
		 * Initializes a matrix based on a 16-element array
		 *
		 * @details Does not perform bounds checking.
		 *
		 * @param inArr
		 */
		Matrix4(float* inArr) : Matrix4
		(
			inArr[0], inArr[1], inArr[2], inArr[3],
			inArr[4], inArr[5], inArr[6], inArr[7],
			inArr[8], inArr[9], inArr[10], inArr[11],
			inArr[12], inArr[13], inArr[14], inArr[15]
		)
		{}

		/**
		 * Initializes and returns an identity matrix.
		 *
		 * @return The identity matrix.
		 */
		static Matrix4 MakeIdentity()
		{
			return Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		}

		/**
		 * Multiplies this matrix against the given Matrix.
		 *
		 * Performs MATRIX multiplication, not just multiplying each member by
		 * the other.
		 *
		 * @param rhs The other matrix.
		 * @return The product of multiplying the 4x4 matrix by a 4x4.
		 */
		Matrix4 operator *(Matrix4 rhs) const
		{
			//Init Temp Matrix Var
			Matrix4 temp = *this;

			//Create Row Vector 3s from First Matrix
			Vector4D Row1 = { m1, m5, m9, m13 };
			Vector4D Row2 = { m2, m6, m10, m14 };
			Vector4D Row3 = { m3, m7, m11, m15 };
			Vector4D Row4 = { m4, m8, m12, m16 };

			//Create Column Vector 3s from rhs Matrix
			Vector4D Column1 = { rhs.m1, rhs.m2, rhs.m3, rhs.m4 };
			Vector4D Column2 = { rhs.m5, rhs.m6, rhs.m7, rhs.m8 };
			Vector4D Column3 = { rhs.m9, rhs.m10, rhs.m11, rhs.m12 };
			Vector4D Column4 = { rhs.m13, rhs.m14, rhs.m15, rhs.m16 };

			//Update the tempMaxtrix3 with Dot Prods from the Column and Rows
			temp.m1 = Row1.Dot(Column1);
			temp.m5 = Row1.Dot(Column2);
			temp.m9 = Row1.Dot(Column3);
			temp.m13 = Row1.Dot(Column4);

			temp.m2 = Row2.Dot(Column1);
			temp.m6 = Row2.Dot(Column2);
			temp.m10 = Row2.Dot(Column3);
			temp.m14 = Row2.Dot(Column4);

			temp.m3 = Row3.Dot(Column1);
			temp.m7 = Row3.Dot(Column2);
			temp.m11 = Row3.Dot(Column3);
			temp.m15 = Row3.Dot(Column4);

			temp.m4 = Row4.Dot(Column1);
			temp.m8 = Row4.Dot(Column2);
			temp.m12 = Row4.Dot(Column3);
			temp.m16 = Row4.Dot(Column4);

			return temp;
		}

		/**
		 * Assigns and returns the result of this Matrix multiplied against the
		 * other Matrix.
		 *
		 * @param rhs The other Matrix.
		 * @return The reference to this Matrix after multiplication.
		 */
		Matrix4& operator *=(Matrix4 rhs)
		{
			(*this) = (*this) * rhs;

			return *this;
		}
		/**
		 * Multiplies this matrix against the given Vector4, treating it like
		 * a 3x1 matrix.
		 *
		 * @param rhs The vector
		 * @return The product of multiplying the 4x4 by a 4x1
		 */
		Vector4D operator *(Vector4D rhs)
		{
			//Init Temp Matrix Var
			Vector4D temp = rhs;

			//Create Row Vector 3s from First Matrix
			Vector4D Row1 = { m1, m5, m9, m13 };
			Vector4D Row2 = { m2, m6, m10, m14 };
			Vector4D Row3 = { m3, m7, m11, m15 };
			Vector4D Row4 = { m4, m8, m12, m16 };

			//Update the tempMaxtrix3 with Dot Prods from the Column and Rows
			temp.x = Row1.Dot(rhs);
			temp.y = Row2.Dot(rhs);
			temp.z = Row3.Dot(rhs);
			temp.w = Row4.Dot(rhs);

			return temp;
		}

		/**
		 * Returns true if every component is exactly equal to the other.
		 *
		 * See also: Equals() for approximate equality.
		 *
		 * @param rhs The other Matrix.
		 * @return True if equal, otherwise false.
		 */
		bool operator == (const Matrix4& rhs) const
		{
			return Equals(rhs);
		}

		/**
		 * Returns false if any component is not exactly equal to the other.
		 *
		 * @param rhs The other Matrix.
		 * @return True if inequal, otherwise false.
		 */
		bool operator != (const Matrix4& rhs) const
		{
			return !Equals(rhs);
		}

		/**
		 * Returns true if every component is exactly equal to the other.
		 *
		 * @param rhs The other Matrix.
		 * @return True if equal, otherwise false.
		 */
		bool Equals(const Matrix4& rhs) const
		{
			for (int i = 0; i < 16; ++i)
			{
				if (v[i] != rhs.v[i])
				{
					return false;
				}
			}
			return true;
		}

		/**
		 * Returns true if every component is approximately equal to the other.
		 *
		 * @param rhs The other Matrix.
		 * @return True if equal, otherwise false.
		 */
		bool NearlyEquals(const Matrix4& rhs, float Tolerance = MAX_FLOAT_DELTA) const
		{
			for (int i = 0; i < 16; ++i)
			{
				//Get the difference between the values
				float temp = v[i] - rhs.v[i];
				//Get the absolute Value for an accurate comparison
				temp *= (temp < 0) ? -1 : 1;
				//Compare, and if one number is greater than the tolerance, the matrix must not be nearly equal.
				if (temp > Tolerance)
				{
					return false;
				}
			}
			//If we never leave early every element must be nearly equal to every element in the other matrix.
			return true;
		}

		/**
		 * Returns this as a formatted string.
		 *
		 * @return A comma separated Vector with its components.
		 */
		std::string ToString() const
		{
			return "m1: " + std::to_string(m1) + ", m5: " + std::to_string(m5) + ", m9: " + std::to_string(m9) + ", m13: " + std::to_string(m13)
				 + "\nm2: " + std::to_string(m2) + ", m6: " + std::to_string(m6) + ", m10: " + std::to_string(m10) + ", m14: " + std::to_string(m14)
				 + "\nm3: " + std::to_string(m3) + ", m7 : " + std::to_string(m7) + ", m11 : " + std::to_string(m11) + ", m15: " + std::to_string(m15)
				 + "\nm4: " + std::to_string(m4) + ", m8 : " + std::to_string(m8) + ", m12 : " + std::to_string(m12) + ", m16: " + std::to_string(m16);
		}

		//
		// Transform Factory Methods
		//

		/**
		 * Creates a translation matrix that translates on the given X, Y, and Z
		 * axes.
		 *
		 * For use with 3-D math.
		 *
		 * @param x Amount to translate by on the X-axis.
		 * @param y Amount to translate by on the Y-axis.
		 * @param z Amount to translate by on the Z-axis.

		 * @return The translation matrix.
		 */
		static Matrix4 MakeTranslation(float x, float y, float z)
		{
			return Matrix4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, x, y, z, 1.0f);
		}

		/**
		 * Creates a translation matrix that translates on the given X, Y, and Z
		 * axes.
		 *
		 * For use with 3-D math.
		 *
		 * @param vec Vector whose X, Y, and Z elements correspond to translation along those axes.
		 * @return The translation matrix.
		 */
		static Matrix4 MakeTranslation(Vector3D vec)
		{
			return Matrix4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, vec.x, vec.y, vec.z, 1.0f);
		}

		/**
		 * Creates a rotation matrix that rotates around the X-axis
		 *
		 * @param Rotation around the X-axis, expressed in radians.
		 * @return The rotation matrix.
		 */
		static Matrix4 MakeRotateX(float a)
		{
			/*
			 *	1   0   0   0
			 *	0  cos -sin 0
			 *	0  sin cos  0
			 *	0   0   0   1
			 */

			return Matrix4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, cosf(a), sinf(a), 0.0f, 0.0f, -sinf(a), cosf(a), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		}

		/**
		 * Creates a rotation matrix that rotates around the Y-axis
		 *
		 * @param Rotation around the Y-axis, expressed in radians.
		 * @return The rotation matrix.
		 */
		static Matrix4 MakeRotateY(float a)
		{
			/*
			 * cos  0   sin   0
			 *	0   1   0   0
			 * -sin 0  cos  0
			 *	0   0   0   1
			 */

			return Matrix4(cosf(a), 0.0f, -sinf(a), 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, sinf(a), 0.0f, cosf(a), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		}

		/**
		 * Creates a rotation matrix that rotates around the Z-axis
		 *
		 * @param Rotation around the Z-axis, expressed in radians.
		 * @return The rotation matrix.
		 */
		static Matrix4 MakeRotateZ(float a)
		{
			/*
			 * cos -sin 0   0
			 * sin cos  0   0
			 *	0   0   1   0
			 *	0   0   0   1
			 */

			return Matrix4(cosf(a), sinf(a), 0.0f, 0.0f, -sinf(a), cosf(a), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		}

		/**
		 * Creates a rotation matrix that applies a pitch, yaw, roll rotation
		 *
		 * Combined in a pitch, then yaw, then roll.
		 *
		 * @param pitch Amount to pitch, expressed in radians.
		 * @param yaw	Amount to yaw, expressed in radians.
		 * @param roll	Amount to roll, expressed in radians.
		 * @return The rotation matrix.
		 */
		static Matrix4 MakeEuler(float pitch, float yaw, float roll)
		{
			Matrix4 x = MakeRotateX(pitch);
			Matrix4 y = MakeRotateY(yaw);
			Matrix4 z = MakeRotateZ(roll);

			return (z * y * x);
		}

		/**
		 * Creates a rotation matrix that applies a pitch, yaw, roll rotation
		 * expressed as the X, Y, and Z components of a Vector.
		 *
		 * @param rot Vector containing how much to pitch (X), yaw (Y), and roll (Z)
		 * @return The rotation matrix.
		 */
		static Matrix4 MakeEuler(Vector3D rot)
		{
			Matrix4 x = MakeRotateX(rot.x);
			Matrix4 y = MakeRotateY(rot.y);
			Matrix4 z = MakeRotateZ(rot.z);

			return (z * y * x);
		}

		/**
		 * Creates a scaling matrix that applies to the X and Y axes.
		 *
		 * The third column is reserved for translation.
		 *
		 * For use with 3D-maths.
		 *
		 * @param xScale Scalar for the X-axis.
		 * @param yScale Scalar for the Y-axis.
		 * @param zScale Scalar for the Z-axis.
		 * @return The scaling matrix.
		 */
		static Matrix4 MakeScale(float xScale, float yScale, float zScale)
		{
			/*
			 * xScale 0      0      0
			 * 0      yScale 0      0
			 * 0      0      zScale 0
			 * 0      0      0      1
			 */
			return Matrix4(xScale, 0.0f, 0.0f, 0.0f, 0.0f, yScale, 0.0f, 0.0f, 0.0f, 0.0f, zScale, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		}

		/**
		 * Creates a scaling matrix that applies to the X, Y, and Z axis with
		 * no homogeneous coordinates, not allowing for any translation. The
		 * amount to scale by on each axis is expressed as the components of
		 * a Vector's X, Y, and Z.
		 *
		 * For use with 3D-maths.
		 *
		 * @param scale Scale factor expressed as a Vector.
		 * @return The scaling matrix.
		 */
		static Matrix4 MakeScale(Vector3D scale)
		{
			return Matrix4(scale.x, 0.0f, 0.0f, 0.0f, 0.0f, scale.y, 0.0f, 0.0f, 0.0f, 0.0f, scale.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		}

		/*
		 * OPTIONAL
		 */

		 /**
			* Transposes the matrix, swapping the values along the diagonal defined
			* as m1, m6, m11, m16.
			*
			* In other words, it turns its columns into rows.
			*
			* @return The transposed matrix.
			*/
		Matrix4 Transposed() const
		{
			Matrix4 temp = (*this);

			temp.m2 = m5;
			temp.m3 = m9;
			temp.m4 = m13;
			temp.m5 = m2;
			temp.m7 = m10;
			temp.m8 = m14;
			temp.m9 = m3;
			temp.m10 = m7;
			temp.m12 = m15;
			temp.m13 = m4;
			temp.m14 = m8;
			temp.m15 = m12;

			return temp;
		}

		/**
		 * Accesses the matrix as though it were an array of floats in columns.
		 *
		 * @param dim The index (accessed by "columns").
		 * @return Returns a reference to the element at the requested index.
		 */
		float& operator [](int dim)
		{
			return v[dim];
		}

		/**
		 * Accesses the matrix as though it were an array of floats in columns.
		 *
		 * @param dim The index (accessed by "columns").
		 * @return Returns a const reference to the element at the requested index.
		 */
		const float& operator [](int dim) const
		{
			return v[dim];
		}

		/**
		 * Casts the matrix as though it were an array of floats in columns.
		 *
		 * @return Returns a float* pointing to the first element of the "array".
		 */
		operator float* ()
		{
			return &v[0];
		}

		/**
		 * Casts the matrix as though it were an array of floats in columns.
		 *
		 * @return Returns a const float* pointing to the first element of the "array".
		 */
		operator const float* () const
		{
			return &v[0];
		}
	};
}	