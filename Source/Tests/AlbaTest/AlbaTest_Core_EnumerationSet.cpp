#include "AlbaTest_Precompile.hpp"
#include "AlbaTest_Core_EnumerationSet.hpp"
#include "Core_EnumerationTraits.hpp"
#include "Core_EnumerationSet.hpp"
#include "Core_Array.hpp"

namespace Alba
{
	namespace Tests
	{
		//-----------------------------------------------------------------------------------------
		// Create a test enumeration set type
		//-----------------------------------------------------------------------------------------
		enum class TestEnumeration
		{
			Apple,
			Banana,
			Mango,
			Orange,
			Peach,
			Pear,
			Pineapple
		};

		typedef Core::EnumerationSet<TestEnumeration> TestEnumerationSet;
	}

	//-----------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------
	template <>
	struct get_all_enum_values<::Alba::Tests::TestEnumeration>
	{
		typedef ::Alba::Tests::TestEnumeration TestEnumeration;

		static constexpr auto value = Core::MakeArray
		(
			TestEnumeration::Apple,
			TestEnumeration::Banana,
			TestEnumeration::Mango,
			TestEnumeration::Orange,
			TestEnumeration::Peach,
			TestEnumeration::Pear,
			TestEnumeration::Pineapple
		);
	};

	namespace Tests
	{
		ALBA_DECLARE_LOG_CATEGORY(AlbaTest);

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Test_CoreEnumerationSet()
		{
			//----------------------------------------------------------------------
			// Test Core::EnumerationSet
			//----------------------------------------------------------------------


			return true;
		}
	}
}