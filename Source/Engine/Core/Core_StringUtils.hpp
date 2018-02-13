//-------------------------------------------------------------------------------------------------
// Name	:	Core_StringFormatUtils.hpp
// Desc	:	String formatting utility functions
//-------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include "Core_BasicTypes.hpp"

namespace Core_StringUtils
{
	/*
	template <typename TStringType>
	void FormatString(TStringType& outString, const TStringType::value_type* format)
	{
		if (format)
		{
			outString = format;
		}
	}

	template <typename TStringType, typename TArg, typename ...TArgs>
	void FormatString(TStringType& outString, const TStringType::value_type* format, TArgs... args)
	{
		enum class ScanningState { Raw, Argument };
		ScanningState scanningState = ScanningState::Raw;

		// TODO: Something more efficient than this
		const auto args_tuple = std::make_tuple<args>();

		for (const TStringType::value_type* itr = format; format != '\0'; ++format)
		{
			if (scanningState == ScanningState::Raw && format == '{')
			{
				scanningState == ScanningStateArgument;
			}
		}
		//std::modf()
	}

	template <typename TStringType, typename ...TArgs>
	TStringType Format(const TStringType::value_type* format, TArgs... args)
	{
		static const uint padding = 16;

		// Reserve approximate space for result...
		// Actual result will obviously be bigger, but better than nothing
		TStringType result;
		result.reserve(std::strlen(format) + padding);

		// Format the string
		FormatString(result, format, args...);

		return result;
	}
	*/
}
