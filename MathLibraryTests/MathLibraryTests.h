#pragma once

/*
 * [YOUR INCLUDE]
 * 
 * Include your math headers here.
 */

#include "DriscollMathUtils.h"

namespace MathClasses
{
	/*
	 * [FORWARD DECLARATIONS]
	 * 
	 * Use this if your namespace or typename for your math type differs.
	 * 
	 * Uncomment and replace the typename on the right-side of the
	 * alias with your type as you need. Make sure to include your headers at
	 * the top of this file.
	 * 
	 * This file is included at the top of every test source file and will
	 * affect their references to the following types:
	 */

	using Vector2 = Driscoll::Vector2D;
	using Vector3 = Driscoll::Vector3D;
	// using Vector4 = YourVector4;
	using Matrix3 = Driscoll::Matrix3;
	// using Matrix4 = YourMatrix4;
	using Color = Driscoll::Color;
}
