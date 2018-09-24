#pragma once

#include "Core.hpp"
#include "Core_EnumerationSet.hpp"
#include "Core_Array.hpp"
#include "Core_TypeTraits.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	FileMode
		// Desc	:	Options for opening a file
		//			Remember to keep in sync with get_all_enum_values<FileMode> below
		//			or the related enumeration set will break
		//-----------------------------------------------------------------------------------------
		enum class FileMode : uint8
		{
			Read,
			Append,
			Write,
			Create,
			Text,
			Binary
		};
	}

	//-----------------------------------------------------------------------------------------
	// Traits for Core::FileMode (used for Core::EnumerationSet<FileMode>)
	//-----------------------------------------------------------------------------------------
	template <>
	struct get_all_enum_values<Core::FileMode>
	{
		using FileMode = Core::FileMode;

		static constexpr auto value = MakeArray
		(
			FileMode::Read,
			FileMode::Append,
			FileMode::Write,
			FileMode::Create,
			FileMode::Text,
			FileMode::Binary
		);
	};

	namespace Core
	{
		typedef EnumerationSet<FileMode> FileModeSet;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class File final
		{
			public:
				
				//=================================================================================
				// Public Static Methods
				//=================================================================================
				File		Open(StringView aFileName, FileModeSet someFileModes);

				//=================================================================================
				// Public Methods
				//=================================================================================

				//---------------------------------------------------------------------------------
				// Accessors
				//---------------------------------------------------------------------------------
				size_t		GetSize() const;
				size_t		GetPosition() const;

				//---------------------------------------------------------------------------------
				// Read
				//---------------------------------------------------------------------------------
				template <typename TDataType>
					size_t Read(TDataType* aDataOut, size_t aCount)
				{
					return Read(aDataOut, sizeof(TDataType), anElementCount);
				}

				template <typename TDataType, class=enable_if_t<is_standard_layout_v<TDataType> > >
					size_t Read(TDataType& aDataOut)
				{
					return Read(&aDataOut, 1);
				}

				//---------------------------------------------------------------------------------
				// Write
				//---------------------------------------------------------------------------------


			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				size_t Read(void* aDataOut, size_t anElementSize, size_t anElementCount);

				//=================================================================================
				// Private Data
				//=================================================================================
				String			myFileName;
				FileModeSet		myFileModes;
		};
	}
}