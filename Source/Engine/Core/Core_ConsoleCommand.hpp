#pragma once

#include "Core_API.hpp"
#include "Core_StringView.hpp"
#include "Core_Any.hpp"
#include "Core_StringHash.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	ConsoleCommand
		// Desc	:	Command that can be executed from the 
		//-----------------------------------------------------------------------------------------
		class ALBA_CORE_API ConsoleCommand
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				explicit ConsoleCommand(const StringView& aName);
				virtual ~ConsoleCommand();

				//=================================================================================
				// Public Methods
				//=================================================================================
				
				//---------------------------------------------------------------------------------
				// Execute
				//---------------------------------------------------------------------------------
				uint32				Execute(const StringView& aCommandString);

				//---------------------------------------------------------------------------------
				// Accessors
				//---------------------------------------------------------------------------------
				inline StringView			GetName() const;
				inline NoCaseStringHash32	GetNameId() const;

			protected:

				//=================================================================================
				// Protected Methods
				//=================================================================================

				//---------------------------------------------------------------------------------
				// Add Parameter
				//---------------------------------------------------------------------------------
				template <typename TDataType>
				void AddParameter(const StringView& aName, TDataType& aValue)
				{

				}

			private:

				//=================================================================================
				// Private Types
				//=================================================================================
				struct ParamTypeVTableBase
				{
					size_t(*FromStringFunc)(const StringView& aStr, void* aValueOut);
				};

				struct ParamData
				{
					ParamData()
						: myVTable(nullptr)
					{
					}

					FixedString<16>			myName;
					NoCaseStringHash32		myNameId;

					ParamTypeVTableBase*	myVTable;
				};

				//=================================================================================
				// Private Methods
				//=================================================================================

				//=================================================================================
				// Private Data
				//=================================================================================
				FixedString<32>			myName;
				NoCaseStringHash32		myNameId;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*inline*/ StringView ConsoleCommand::GetName() const
		{
			return StringView(myName.c_str(), myName.length());
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*inline*/ NoCaseStringHash32 ConsoleCommand::GetNameId() const
		{
			return myNameId;
		}
	}
}