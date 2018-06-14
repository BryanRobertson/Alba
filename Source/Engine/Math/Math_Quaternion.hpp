#pragma once

#include "Math_Defines.hpp"

#pragma warning(push, 0)
#include <mathfu/quaternion.h>
#pragma warning(pop)

namespace Alba
{
	namespace Math
	{
		typedef mathfu::Quaternion<float>		Quaternionf;
		typedef mathfu::Quaternion<double>		Quaterniond;
	}
}