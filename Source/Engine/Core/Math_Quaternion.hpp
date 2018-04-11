#pragma once

#define EIGEN_MPL2_ONLY
	#pragma warning(push)
	#pragma warning(disable : 4127)
	#define eigen_assert ALBA_ASSERT
	#include <Eigen/Geometry>
	#pragma warning(pop)
#undef EIGEN_MPL2_ONLY

namespace Alba
{
	namespace Math
	{
		typedef Eigen::Quaternionf Quaternion4f;
		typedef Eigen::Quaterniond Quaternion4d;
	}
}
