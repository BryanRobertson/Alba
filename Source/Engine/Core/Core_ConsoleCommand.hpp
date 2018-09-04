#pragma once

#include "Core_API.hpp"
#include "Core_StringView.hpp"
#include "Core_Any.hpp"
#include "Core_StringHash.hpp"
#include "Core_ConsoleCommandInternal.hpp"
#include "Core_Vector.hpp"

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
				uint32						Execute(const StringView& aCommandString);

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
					ParamData& param = myParams.push_back();

					param.myOutputData	= aValue;
					param.myName		= aName;
					param.myNameId		= NoCaseStringHash32(aName);
					param.myVTable		= &GetVTable<TDataType>();
				}

			private:

				//=================================================================================
				// Private Types
				//=================================================================================
				typedef ConsoleCommandInternal::ParamTypeVTableBase ParamTypeVTableBase;

				struct ParamData
				{
					ParamData()
						: myVTable(nullptr)
						, myOutputData(nullptr)
					{
					}

					FixedString<16>			myName;
					NoCaseStringHash32		myNameId;
					ParamTypeVTableBase*	myVTable;
					void*					myOutputData;
				};

				//=================================================================================
				// Private Methods
				//=================================================================================
				template <typename TDataType>
				static const ParamTypeVTableBase& GetVTable()
				{
					static ConsoleCommandInternal::ParamTypeVTable<TDataType> ourVTable;
					return ourVTable;
				}

				//=================================================================================
				// Private Data
				//=================================================================================
				FixedString<32>				myName;
				NoCaseStringHash32			myNameId;
				FixedVector<ParamData, 4>	myParams;
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