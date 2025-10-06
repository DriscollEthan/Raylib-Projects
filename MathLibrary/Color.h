#pragma once

#include <cassert>  // For asserts
#include <cstdint>  // For int_32_t
#include <string>		// std::ToString
#include "utils.h"

namespace Driscoll
{
  struct Color
  {
    union
    {
      struct
      {
				char8_t a, b, g, r;
      };

      char8_t v[4];

      int32_t rgba;
    };

		static_assert(sizeof(char8_t) == 1, "Unexpected size for char8_t");
		static_assert(sizeof(int32_t) == 4, "Unexpected size for int32_t");

		Color()
		{
			r = g = b = a = 0;
		}

		Color(int32_t _rgba)
		{
			rgba = _rgba;
		}

		Color(char8_t red, char8_t green, char8_t blue, char8_t alpha)
		{
			r = red;
			g = green;
			b = blue;
			a = alpha;
		}

#ifdef RAYLIB_CPP_INCLUDE_RAYLIB_CPP_HPP_
		// implicit conversion from raylib Color to our Color
		Color(const raylib::Color& RColor)
		{
			r = RColor.r;
			g = RColor.g;
			b = RColor.b;
			a = RColor.a;
		}

		// implicit conversion from our Color to raylib Color
		operator raylib::Color() const
		{
			return { r, g, b, a };
		}
#endif

#ifdef RAYLIB_H
		// implicit conversion from raylib Color to our Color
		Color(const ::Color& RColor)
		{
			r = RColor.r;
			g = RColor.g;
			b = RColor.b;
			a = RColor.a;
		}

		// implicit conversion from our Color to raylib Color
		operator ::Color() const
		{
			return { r, g, b, a };
		}
#endif

		/*
		 * Returns this as a formatted string.
		 *
		 * @return A comma separated Vector with its components.
		 */
		std::string ToString() const
		{
			return "Red: " + std::to_string(r) + ", Green: " + std::to_string(g) + ", Blue: " + std::to_string(b) + ", Alpha: " + std::to_string(a);
		}

		/*
		 * Returns true if every component is exactly equal to the other.
		 *
		 * @param rhs The other Color.
		 * @return True if equal, otherwise false.
		 */
		bool operator==(const Color& rhs) const
		{
			return (r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a);

		}

		/*
		 * Returns true if any component not equal to the other.
		 *
		 * @param rhs The other Color.
		 * @return True if inequal, otherwise false.
		 */
		bool operator!=(const Color& rhs) const
		{
			return !(r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a);
		}

		 /*
			* Accesses the color as though it were an array of channels
			*
			* 0 => R
			* 1 => G
			* 2 => B
			* 3 => A
			*
			* @param dim The index
			* @return Returns a reference to the element at the requested index.
			*/
		char8_t& operator [](int dim)
		{
			switch (dim)
			{
			case 0:
				return v[3];
			case 1:
				return v[2];
			case 2:
				return v[1];
			case 3:
				return v[0];
			}
		}

		/*
		 * Accesses the color as though it were an array of channels
		 *
		 * 0 => R 
		 * 1 => G
		 * 2 => B
		 * 3 => A
		 *
		 * @param dim The index
		 * @return Returns a const reference to the element at the requested index.
		 */
		char8_t operator [](int dim) const
		{
			switch (dim)
			{
			case 0:
				return v[3];
			case 1:
				return v[2];
			case 2:
				return v[1];
			case 3:
				return v[0];
			}
		}

		//Reds
		inline static Color Red() { return Color(255, 0, 0, 255); }
		inline static Color DarkRed() {return Color(110, 0, 0, 255); }

		//Greens
		inline static Color Green() { return Color(0, 255, 0, 255); }


		//Blues
		inline static Color Blue() { return Color(0, 0, 255, 255); }
		inline static Color Cyan() { return Color(0, 255, 255, 255); }
		inline static Color Teal() { return Color(0, 128, 128, 255); }

		//White - Blacks
		inline static Color White() { return Color(255, 255, 255, 255); }
		inline static Color Grey() {return Color(128, 128, 128, 255); }
		inline static Color DarkGrey() {return Color (80, 80, 80, 255); }
		inline static Color Black() { return Color(0, 0, 0, 255); }
		inline static Color Clear() { return Color(255, 255, 255, 0); }

		//Mixtures
		inline static Color Yellow () { return Color(255, 255, 0, 255); }
		inline static Color Orange() { return Color(255, 165, 0, 255); }
		inline static Color Pink() { return Color(255, 77, 255, 255); }



  };
}