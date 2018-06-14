#pragma once

#include "Math_Defines.hpp"

#pragma warning(push, 0)
#include <mathfu/matrix.h>
#include <mathfu/matrix_4x4.h>
#pragma warning(pop)

namespace Alba
{
	namespace Math
	{
		typedef mathfu::Matrix<float, 4, 4> Matrix44f;
		typedef mathfu::Matrix<float, 3, 3> Matrix33f;
		typedef mathfu::Matrix<float, 2, 2> Matrix22f;

		typedef mathfu::Matrix<double, 4, 4> Matrix44d;
		typedef mathfu::Matrix<double, 3, 3> Matrix33d;
		typedef mathfu::Matrix<double, 2, 2> Matrix22d;
	}
}