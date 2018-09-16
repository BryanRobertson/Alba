#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

namespace Alba
{
	namespace Math
	{ 
		template <typename TValueType>
		struct Constants;

		template <>
		struct Constants<float>
		{
			static constexpr float Pi			= 3.14159265358979323846f;
			static constexpr float HalfPi		= 1.57079632679489661923f;
			static constexpr float QuarterPi	= 0.785398163397448309616f;
			static constexpr float TwoPi		= 3.14159265358979323846f * 2.0f;
			static constexpr float OneOverPi	= 0.318309886183790671538f;
			static constexpr float TwoOverPi	= 0.636619772367581343076f;

			static constexpr float e			= 2.71828182845904523536f;

			static constexpr float EpsilonE4	= 1E-4f;
			static constexpr float EpsilonE5	= 1E-5f;
			static constexpr float EpsilonE6	= 1E-6f;
		};

		template <>
		struct Constants<double>
		{
			static constexpr double Pi			= 3.14159265358979323846;
			static constexpr double HalfPi		= 1.57079632679489661923;
			static constexpr double QuarterPi	= 0.785398163397448309616;
			static constexpr double TwoPi		= 3.14159265358979323846 * 2.0;
			static constexpr double OneOverPi	= 0.318309886183790671538;
			static constexpr double TwoOverPi	= 0.636619772367581343076;

			static constexpr double e			= 2.71828182845904523536;

			static constexpr double EpsilonE4	= 1E-4;
			static constexpr double EpsilonE5	= 1E-5;
			static constexpr double EpsilonE6	= 1E-6;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TInputValue>
		TInputValue Squared(const TInputValue& aValue)
		{
			return aValue * aValue;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		inline float Abs(float anInput)
		{
			return std::fabsf(anInput);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		inline double Abs(double anInput)
		{
			return std::fabs(anInput);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TInputValue>
		inline constexpr bool IsNearlyEqual(const TInputValue& aValue1, const TInputValue& aValue2,
			const TInputValue& anEpsilon = Constants<TInputValue>::EpsilonE6)
		{
			// TODO: Investigate improving this implementation
			// https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

			return Abs(aValue1 - aValue2) < anEpsilon;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		inline float Pow(float anInputValue, float aPower)
		{
			return std::powf(anInputValue, aPower);
		}

		inline double Pow(double anInputValue, double aPower)
		{
			return std::pow(anInputValue, aPower);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		inline float Sqrt(float anInputValue)
		{
			return std::sqrtf(anInputValue);
		}

		inline double Sqrt(double anInputValue)
		{
			return std::sqrt(anInputValue);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		inline float Sin(float anInputValue)
		{
			return std::sinf(anInputValue);
		}

		inline double Sin(double anInputValue)
		{
			return std::sin(anInputValue);
		}

		inline float ASin(float anInputValue)
		{
			return std::asinf(anInputValue);
		}

		inline double ASin(double anInputValue)
		{
			return std::asin(anInputValue);
		}

		inline float SinH(float anInputValue)
		{
			return std::sinhf(anInputValue);
		}

		inline double SinH(double anInputValue)
		{
			return std::sinh(anInputValue);
		}

		inline float Cos(float anInputValue)
		{
			return std::cosf(anInputValue);
		}

		inline double Cos(double anInputValue)
		{
			return std::cos(anInputValue);
		}

		inline float ACos(float anInputValue)
		{
			return std::acosf(anInputValue);
		}

		inline double ACos(double anInputValue)
		{
			return std::acos(anInputValue);
		}

		inline float CosH(float anInputValue)
		{
			return std::coshf(anInputValue);
		}

		inline double CosH(double anInputValue)
		{
			return std::cosh(anInputValue);
		}

		inline float Tan(float anInputValue)
		{
			return std::tanf(anInputValue);
		}

		inline double Tan(double anInputValue)
		{
			return std::tan(anInputValue);
		}

		inline float ATan(float anInputValue)
		{
			return std::atanf(anInputValue);
		}

		inline double ATan(double anInputValue)
		{
			return std::atan(anInputValue);
		}

		inline float TanH(float anInputValue)
		{
			return std::tanhf(anInputValue);
		}

		inline double TanH(double anInputValue)
		{
			return std::tanh(anInputValue);
		}

		inline float Cot(float anInputValue)
		{ 
			return Cos(anInputValue) / Sin(anInputValue);
		}

		inline double Cot(double anInputValue)
		{
			return Cos(anInputValue) / Sin(anInputValue);
		}

		inline float Sec(float anInputValue)
		{ 
			return 1.0f / Cos(anInputValue);
		}

		inline double Sec(double anInputValue)
		{
			return 1.0 / Cos(anInputValue);
		}

		inline float Csc(float anInputValue)
		{ 
			return 1.0f / Sin(anInputValue);
		}

		inline double Csc(double anInputValue)
		{
			return 1.0 / Sin(anInputValue);
		}

		inline float CotH(float anInputValue) 
		{ 
			return CosH(anInputValue) / SinH(anInputValue);
		}

		inline double CotH(double anInputValue)
		{
			return CosH(anInputValue) / SinH(anInputValue);
		}

		inline float SecH(float anInputValue) 
		{ 
			return 1.0f / CosH(anInputValue);
		}

		inline double SecH(double anInputValue)
		{
			return 1.0 / CosH(anInputValue);
		}

		inline float CscH(float anInputValue) 
		{ 
			return 1.0f / SinH(anInputValue);
		}

		inline double CscH(double anInputValue)
		{
			return 1.0 / SinH(anInputValue);
		}

		inline float ATan2(float aY, float aX)
		{
			return std::atan2f(aY, aX);
		}

		inline double ATan2(double aY, double aX)
		{
			return std::atan2(aY, aX);
		}

		//-----------------------------------------------------------------------------------------
		struct Temp
		{
			void TempFunc();
		};
	}
}