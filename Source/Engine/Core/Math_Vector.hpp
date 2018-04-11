#pragma once

#define EIGEN_MPL2_ONLY
	#pragma warning(push)
	#pragma warning(disable : 4127)
	#define eigen_assert ALBA_ASSERT
	#include <Eigen/Core>
	#pragma warning(pop)
#undef EIGEN_MPL2_ONLY

namespace Alba
{
	namespace Math
	{
		typedef Eigen::Vector2i Vector2i;
		typedef Eigen::Vector2f Vector2f;
		typedef Eigen::Vector2d Vector2d;

		typedef Eigen::Vector3i Vector3i;
		typedef Eigen::Vector3f Vector3f;
		typedef Eigen::Vector3d Vector3d;

		typedef Eigen::Vector4i Vector4i;
		typedef Eigen::Vector4f Vector4f;
		typedef Eigen::Vector4d Vector4d;
	}
}