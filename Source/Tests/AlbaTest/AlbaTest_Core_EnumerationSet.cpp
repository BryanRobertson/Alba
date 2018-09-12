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

			//----------------------------------------------------------------------
			// Test constructors/equality operator/inequality operator
			//----------------------------------------------------------------------
			{
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
			}

			//----------------------------------------------------------------------
			// Test iterators
			//----------------------------------------------------------------------
			{
				TestEnumerationSet all2;
				for (TestEnumeration entry : TestEnumerationSet::All)
				{
					all2.Insert(entry);
				}

				ALBA_TEST(TestEnumerationSet::All == all2);
				ALBA_TEST(!(TestEnumerationSet::All != all2));
			}

			//----------------------------------------------------------------------
			// Set Difference / Intersection / Union
			//----------------------------------------------------------------------
			{
				const TestEnumerationSet a = { TestEnumeration::Mango, TestEnumeration::Peach };
				const TestEnumerationSet b = { TestEnumeration::Banana, TestEnumeration::Orange };
				const TestEnumerationSet c = { TestEnumeration::Pear, TestEnumeration::Peach, TestEnumeration::Pineapple };
				const TestEnumerationSet d = { TestEnumeration::Peach };
				const TestEnumerationSet e = { TestEnumeration::Pear };
				const TestEnumerationSet f = { TestEnumeration::Pineapple };

				ALBA_TEST(Intersection(a, c) == d);
				ALBA_TEST(d.Union(e).Union(f) == c);
				ALBA_TEST(c.Difference(d).Difference(e) == f);

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

				ALBA_TEST(all.Difference(f) == ~f);
			}

			//----------------------------------------------------------------------
			// Test access to raw bits
			//----------------------------------------------------------------------
			{
				const uint64 allBits = TestEnumerationSet::All.GetBits();
				ALBA_TEST(allBits == 0b1111111);
			}

			return true;
		}
	}
}