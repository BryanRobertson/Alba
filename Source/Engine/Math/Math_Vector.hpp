#pragma once

#include "Math_Defines.hpp"

#pragma warning(push, 0)
#include <mathfu/vector.h>
#pragma warning(pop)

namespace Alba
{
	namespace Math
	{
		typedef mathfu::Vector<float, 2>		Vector2f;
		typedef mathfu::Vector<float, 3>		Vector3f;
		typedef mathfu::Vector<float, 4>		Vector4f;

		typedef mathfu::Vector<double, 2>		Vector2d;
		typedef mathfu::Vector<double, 3>		Vector3d;
		typedef mathfu::Vector<double, 4>		Vector4d;

		typedef mathfu::Vector<std::int32_t, 2> Vector2i;
		typedef mathfu::Vector<std::int32_t, 3> Vector3i;
		typedef mathfu::Vector<std::int32_t, 4> Vector4i;

		typedef mathfu::Vector<std::int16_t, 2> Vector2s;
		typedef mathfu::Vector<std::int16_t, 3> Vector3s;
		typedef mathfu::Vector<std::int16_t, 4> Vector4s;
	}
}