#include "AlbaTest_Precompile.hpp"
#include "AlbaTest_Core_EnumerationSet.hpp"
#include "AlbaTest.hpp"

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
		typedef Core::EnumerationSet<TestEnumeration> TestEnumerationSet;
	}

	namespace Tests
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Test_CoreEnumerationSet()
		{
			//----------------------------------------------------------------------
			// Test Core::EnumerationSet
			//----------------------------------------------------------------------
			const TestEnumerationSet emptySet = {};
			const TestEnumerationSet appleSet = { TestEnumeration::Apple };
			const TestEnumerationSet appleSet2 = TestEnumeration::Apple;
			const TestEnumerationSet bananaSet = { TestEnumeration::Banana };

			ALBA_TEST(emptySet == emptySet);
			ALBA_TEST(!(emptySet != emptySet));
			ALBA_TEST(appleSet == appleSet2);
			ALBA_TEST(appleSet != bananaSet);
			ALBA_TEST(appleSet2 != bananaSet);
			
			const TestEnumerationSet all = 
			{ 
				TestEnumeration::Apple,
				TestEnumeration::Banana,
				TestEnumeration::Mango,
				TestEnumeration::Orange,
				TestEnumeration::Peach,
				TestEnumeration::Pear,
				TestEnumeration::Pineapple 
			};

			ALBA_TEST(emptySet.begin() == emptySet.end());
			ALBA_TEST(all.begin() != all.end());

			ALBA_TEST(all == TestEnumerationSet::All);
			ALBA_TEST(all != emptySet);

			TestEnumerationSet all2;
			for (TestEnumeration entry : all)
			{
				all2.Insert(entry);
			}

			ALBA_TEST(all == all2);
			ALBA_TEST(!(all != all2));

			return true;
		}
	}
}