#pragma once

#include "Core.hpp"
#include "Core_EnumerationSet.hpp"
#include "Core_Array.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_Vector.hpp"

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
			Write,
			Append,
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
			FileMode::Write,
			FileMode::Append,
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
		enum class FilePosition
		{
			Set			= SEEK_SET,
			Current		= SEEK_CUR,
			End			= SEEK_END
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class File final
		{
			public:
				
				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static File OpenFile(StringView aFileName, FileModeSet someFileModes = { FileMode::Read, FileMode::Text })
				{
					return File(aFileName, someFileModes);
				}

				//=================================================================================
				// Public Constructors/Destructors
				//=================================================================================
				File() = default;
				File(const File&) = delete;
				File(File&&) = default;

				File(StringView aFileName, FileModeSet someFileModes)
				{
					Open(aFileName, someFileModes);
				}

				~File()
				{
					if (IsOpen())
					{
						Close();
					}
				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				bool Open(StringView aFileName, FileModeSet someFileModes)
				{
					ALBA_ASSERT(!IsOpen());

					myFileName = aFileName;
					myFileModes = someFileModes;

					FixedString<8> mode;
					if (someFileModes.Contains(FileMode::Read))
					{
						mode.append("r");
					}

					if (someFileModes.Contains(FileMode::Write))
					{
						mode.append("w");
					}

					if (someFileModes.Contains(FileMode::Binary))
					{
						mode.append("b");
					}

					if (someFileModes.Contains(FileMode::Create))
					{
						mode.append("x");
					}

#					if defined(ALBA_COMPILER_VISUALSTUDIO)
						fopen_s(&myFile, aFileName.data(), mode.data());
#					else
						myFile = std::fopen(aFileName.data(), mode.data());
#					endif

					if (myFile)
					{
						SetPosition(0, FilePosition::End);
						myFileSize = GetPosition();
						SetPosition(0, FilePosition::Set);

						return true;
					}
					else
					{
						return false;
					}
				}

				ALBA_FORCEINLINE int SetPosition(int anOffset, FilePosition aPositionType)
				{
					ALBA_ASSERT(IsOpen());
					return std::fseek(myFile, anOffset, static_cast<int>(aPositionType));
				}

				//---------------------------------------------------------------------------------
				// Accessors
				//---------------------------------------------------------------------------------
				ALBA_FORCEINLINE size_t	GetSize() const
				{
					return myFileSize;
				}

				ALBA_FORCEINLINE int GetPosition() const
				{
					ALBA_ASSERT(IsOpen());
					return std::ftell(myFile);
				}

				ALBA_FORCEINLINE FileModeSet GetOpenMode() const
				{
					return myFileModes;
				}

				ALBA_FORCEINLINE bool IsOpen() const
				{
					return myFile != nullptr;
				}

				ALBA_FORCEINLINE void Close()
				{
					if (IsOpen())
					{
						std::fclose(myFile);
						myFile = nullptr;
					}
				}

				//---------------------------------------------------------------------------------
				// Read
				//---------------------------------------------------------------------------------
				template <typename TDataType>
				ALBA_FORCEINLINE size_t Read(TDataType* aDataOut, size_t aCount)
				{
					ALBA_ASSERT(IsOpen());
					return Read(aDataOut, sizeof(TDataType), aCount);
				}

				template <typename TDataType, class=enable_if_t<is_standard_layout_v<TDataType> > >
				ALBA_FORCEINLINE size_t Read(TDataType& aDataOut)
				{
					ALBA_ASSERT(IsOpen());
					return Read(&aDataOut, 1);
				}

				template <typename TCharType, typename TAllocator>
				ALBA_FORCEINLINE size_t Read(BasicString<TCharType, TAllocator>& aDataOut, size_t aCount)
				{
					ALBA_ASSERT(IsOpen());

					aDataOut.reserve(aCount);
					return Read(&aDataOut[0], sizeof(TCharType), aCount);
				}

				template <typename TCharType, size_t TCount, OverflowBehavior TOverflow, typename TAllocator>
				ALBA_FORCEINLINE size_t Read(FixedBasicString<TCharType, TCount, TOverflow, TAllocator>& aDataOut, size_t aCount)
				{
					ALBA_ASSERT(IsOpen());

					aDataOut.reserve(aCount);
					return Read(&aDataOut[0], sizeof(TCharType), aCount);
				}

				template <typename TDataType, typename TAllocator>
				ALBA_FORCEINLINE size_t Read(Vector<TDataType, TAllocator>& aDataOut, size_t aCount)
				{
					ALBA_ASSERT(IsOpen());

					aDataOut.reserve(aCount);
					return Read(&aDataOut[0], sizeof(TDataType), aCount);
				}

				template <typename TDataType, size_t TCount, OverflowBehavior TOverflow, typename TAllocator>
				ALBA_FORCEINLINE size_t Read(FixedVector<TDataType, TCount, TOverflow, TAllocator>& aDataOut, size_t aCount)
				{
					ALBA_ASSERT(IsOpen());

					aDataOut.reserve(aCount);
					return Read(&aDataOut[0], sizeof(TDataType), aCount);
				}

				template <typename TDataType=std::byte, size_t TSize=128, OverflowBehavior TOverflowBehavior = OverflowBehavior::Allowed, typename TOverflowAllocator = EASTLAllocatorType>
				FixedVector<TDataType, TSize, TOverflowBehavior, TOverflowAllocator> ReadToEnd()
				{
					ALBA_ASSERT(IsOpen());

					const size_t position = GetPosition();
					const size_t size = GetSize();
					const size_t readCount = size - position;

					FixedVector<TDataType, TSize, TOverflowBehavior, TOverflowAllocator> out;
					out.reserve(readCount);

					Read(&out[0], readCount);
					return out;
				}

				template <typename TDataType, size_t TSize=128, OverflowBehavior TOverflowBehavior=OverflowBehavior::Allowed, typename TOverflowAllocator=EASTLAllocatorType>
				size_t ReadToEnd(FixedVector<TDataType, TSize, TOverflowBehavior, TOverflowAllocator>& someDataOut)
				{
					ALBA_ASSERT(IsOpen());

					const size_t position = GetPosition();
					const size_t size = GetSize();
					const size_t readCount = size - position;

					someDataOut.clear();
					someDataOut.resize(readCount);

					return Read(&someDataOut[0], readCount);
				}

				template <typename TDataType=std::byte, typename TAllocator=EASTLAllocatorType>
				Vector<TDataType, TAllocator> ReadToEnd()
				{
					ALBA_ASSERT(IsOpen());

					const size_t position = GetPosition();
					const size_t size = GetSize();

					Vector<TDataType, TAllocator> out;
					out.resize(size - position);

					Read(&out[0], size - position);

					return out;
				}

				//---------------------------------------------------------------------------------
				// Write
				//---------------------------------------------------------------------------------
				template <typename TDataType>
				ALBA_FORCEINLINE size_t Write(const TDataType* aDataIn, size_t aCount)
				{
					ALBA_ASSERT(IsOpen());
					return Write(aDataIn, aCount);
				}

				template <typename TDataType, class = enable_if_t<is_standard_layout_v<TDataType> > >
				ALBA_FORCEINLINE size_t Write(const TDataType& aDataIn)
				{
					ALBA_ASSERT(IsOpen());
					return Write(&aDataIn, 1);
				}

				template <typename TCharType, size_t TCount, OverflowBehavior TOverflow, typename TAllocator>
				ALBA_FORCEINLINE size_t Write(FixedBasicString<TCharType, TCount, TOverflow, TAllocator>& someDataIn, size_t aCount=someDataIn.size())
				{
					ALBA_ASSERT(IsOpen());
					return Write(&someDataIn[0], sizeof(TCharType), aCount);
				}

				template <typename TCharType, typename TAllocator>
				ALBA_FORCEINLINE size_t Write(BasicString<TCharType, TAllocator>& someDataIn, size_t aCount=someDataIn.size())
				{
					ALBA_ASSERT(IsOpen());
					return Write(&someDataIn[0], sizeof(TCharType), aCount);
				}

				template <typename TDataType, size_t TCount, OverflowBehavior TOverflow, typename TAllocator>
				ALBA_FORCEINLINE size_t Write(FixedVector<TDataType, TCount, TOverflow, TAllocator>& someDataIn, size_t aCount = someDataIn.size())
				{
					ALBA_ASSERT(IsOpen());
					return Write(&someDataIn[0], sizeof(TCharType), std::min(aCount, someDataIn.size()));
				}

				template <typename TDataType, typename TAllocator>
				ALBA_FORCEINLINE size_t Write(Vector<TDataType, TAllocator>& someDataIn, size_t aCount = someDataIn.size())
				{
					ALBA_ASSERT(IsOpen());
					return Write(&someDataIn[0], sizeof(TDataType), std::min(aCount, someDataIn.size()));
				}

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				size_t Read(void* aDataOut, size_t anElementSize, size_t anElementCount)
				{
					ALBA_ASSERT(IsOpen());
					return std::fread(aDataOut, anElementSize, anElementCount, myFile);
				}

				size_t Write(void* aDataOut, size_t anElementSize, size_t anElementCount)
				{
					ALBA_ASSERT(IsOpen());
					return std::fwrite(aDataOut, anElementSize, anElementCount, myFile);
				}

				//=================================================================================
				// Private Data
				//=================================================================================
				String			myFileName;
				FileModeSet		myFileModes;
				std::FILE*		myFile			= nullptr;
				size_t			myFileSize		= 0;
		};
	}
}