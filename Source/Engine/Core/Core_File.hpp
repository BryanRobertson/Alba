#pragma once

#include "Core.hpp"
#include "Core_EnumerationSet.hpp"
#include "Core_Array.hpp"
#include "Core_TypeTraits.hpp"

#include <cstdio>
#include <cstdlib>

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
				File Open(StringView aFileName, FileModeSet someFileModes)
				{
					return File(aFileName, someFileModes);
				}

				//=================================================================================
				// Public Constructors/Destructors
				//=================================================================================
				File(const File&) = delete;
				File(File&&) = default;

				//=================================================================================
				// Public Methods
				//=================================================================================

				//---------------------------------------------------------------------------------
				// Accessors
				//---------------------------------------------------------------------------------
				ALBA_FORCEINLINE size_t	GetSize() const
				{
					return myFileSize;
				}

				ALBA_FORCEINLINE size_t	GetPosition() const
				{
					return std::ftell(myFile);
				}

				ALBA_FORCEINLINE FileModeSet GetOpenMode() const
				{
					return myFileModes;
				}

				ALBA_FORCEINLINE bool IsValid() const
				{
					return myFile != nullptr;
				}

				ALBA_FORCEINLINE void Close()
				{
					std::fclose(myFile);
					myFile = nullptr;
				}

				//---------------------------------------------------------------------------------
				// Read
				//---------------------------------------------------------------------------------
				template <typename TDataType>
				ALBA_FORCEINLINE size_t Read(TDataType* aDataOut, size_t aCount)
				{
					return Read(aDataOut, sizeof(TDataType), anElementCount);
				}

				template <typename TDataType, class=enable_if_t<is_standard_layout_v<TDataType> > >
				ALBA_FORCEINLINE size_t Read(TDataType& aDataOut)
				{
					return Read(&aDataOut, 1);
				}

				template <typename TCharType, size_t TCount, OverflowBehavior TOverflow, typename TAllocator>
				ALBA_FORCEINLINE size_t Read(FixedBasicString<TCharType, TCount, TOverflow, TAllocator>& aDataOut, size_t aCount)
				{
					aDataOut.reserve(aCount);
					return Read(&aDataOut[0], sizeof(TCharType), aCount);
				}

				template <typename TCharType, size_t TCount, OverflowBehavior TOverflow, typename TAllocator>
				ALBA_FORCEINLINE size_t Read(FixedBasicString<TCharType, TCount, TOverflow, TAllocator>& aDataOut, size_t aCount)
				{
					aDataOut.reserve(aCount);
					return Read(&aDataOut[0], sizeof(TCharType), aCount);
				}

				//---------------------------------------------------------------------------------
				// Write
				//---------------------------------------------------------------------------------
				template <typename TDataType>
				ALBA_FORCEINLINE size_t Write(const TDataType* aDataOut, size_t aCount)
				{
					return Write(aDataOut, aCount);
				}

				template <typename TDataType, class = enable_if_t<is_standard_layout_v<TDataType> > >
				ALBA_FORCEINLINE size_t Write(const TDataType& aDataOut)
				{
					return Write(&aDataOut, 1);
				}

				template <typename TCharType, size_t TCount, OverflowBehavior TOverflow, typename TAllocator>
				ALBA_FORCEINLINE size_t Write(FixedBasicString<TCharType, TCount, TOverflow, TAllocator>& aDataOut, size_t aCount=aDataOut.size())
				{
					return Write(&aDataOut[0], sizeof(TCharType), aCount);
				}

				template <typename TCharType, typename TAllocator>
				ALBA_FORCEINLINE size_t Write(BasicString<TCharType, TAllocator>& aDataOut, size_t aCount=aDataOut.size())
				{
					return Write(&aDataOut[0], sizeof(TCharType), aCount);
				}

			private:

				//=================================================================================
				// Private Constructors
				//=================================================================================
				File(StringView aFileName, FileModeSet someFileModes)
					: myFileName(aFileName)
					, myFileModes(someFileModes)
				{
					FixedString<8> mode;
					if (someFileModes.Contains(FileMode::Read))
					{
						mode.append("r");
					}

					if (someFileModes.Contains(FileMode::Write))
					{
						mode.append("w");
					}

					myFile = std::fopen(aFileName.data(), mode.data());
					if (myFile)
					{
						std::fseek(myFile, 0, SEEK_END);
						myFileSize = std::ftell(myFile);
						std::fseek(myFile, 0, SEEK_SET);
					}
				}

				//=================================================================================
				// Private Methods
				//=================================================================================
				size_t Read(void* aDataOut, size_t anElementSize, size_t anElementCount)
				{
					return std::fread(aDataOut, anElementSize, anElementCount, myFile);
				}

				size_t Write(void* aDataOut, size_t anElementSize, size_t anElementCount)
				{
					return std::fwrite(aDataOut, anElementSize, anElementCount, myFile);
				}

				//=================================================================================
				// Private Data
				//=================================================================================
				String			myFileName;
				FileModeSet		myFileModes;
				std::FILE*		myFile;
				size_t			myFileSize;
		};
	}
}