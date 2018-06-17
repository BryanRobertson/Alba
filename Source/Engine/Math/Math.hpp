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
			static constexpr float Pi			= M_PI;
			static constexpr float HalfPi		= M_PI_2;
			static constexpr float QuarterPi	= M_PI_4;
			static constexpr float TwoPi		= M_PI * 2.0f;

			static constexpr float e			= M_E;

			static constexpr float EpsilonE4	= 1E-4f;
			static constexpr float EpsilonE5	= 1E-5f;
			static constexpr float EpsilonE6	= 1E-6f;
		};

		template <>
		struct Constants<double>
		{
			static constexpr double Pi			= M_PI;
			static constexpr double HalfPi		= M_PI_2;
			static constexpr double QuarterPi	= M_PI_4;
			static constexpr double TwoPi		= M_PI * 2.0;

			static constexpr double e			= M_E;

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