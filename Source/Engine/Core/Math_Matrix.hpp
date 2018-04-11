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
		typedef Eigen::Matrix2i	Matrix2i;
		typedef Eigen::Matrix2f Matrix2f;
		typedef Eigen::Matrix2d Matrix2d;

		typedef Eigen::Matrix3i	Matrix3i;
		typedef Eigen::Matrix3f Matrix3f;
		typedef Eigen::Matrix3d Matrix3d;

		typedef Eigen::Matrix4i Matrix4i;
		typedef Eigen::Matrix4f Matrix4f;
		typedef Eigen::Matrix4d Matrix4d;
	}
}