#include "Core_Precompile.hpp"
#include "Core_ConsoleBasicCommands.hpp"
#include "Core_ConsoleModule.hpp"
#include "Core_FixedString.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TCommandType>
		void RegisterCommand()
		{
			ConsoleModule& consoleModule = ConsoleModule::Get();
			if (consoleModule.IsLoaded())
			{
				Console& console = consoleModule.Get();
				console.RegisterCommand<TCommandType>();
			}
		}

		//-----------------------------------------------------------------------------------------
		// Name	:	TestConsoleCommand
		// Desc	:	Console command for testing the console system
		//-----------------------------------------------------------------------------------------
#if 0
		class ALBA_CORE_API TestConsoleCommand : ConsoleCommand
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static void Register()
				{
					RegisterCommand<TestConsoleCommand>();
				}

				//=================================================================================
				// Public Constructors
				//=================================================================================
				TestConsoleCommand()
					: ConsoleCommand("testcommand")
				{
					AddParameter("int", myIntegerValue);
					AddParameter("bool", myBooleanValue);
					AddParameter("float", myFloatValue);
					AddParameter("string", myStringValue);
				}

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				void OnExecute(StringView /*aStringView*/)
				{

				}

				//=================================================================================
				// Private Data
				//=================================================================================
				int					myIntegerValue = 0;
				bool				myBooleanValue = false;
				float				myFloatValue = 0.0f;
				FixedString<16>		myStringValue = "";				
		};
#endif

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void RegisterBasicConsoleCommands()
		{

		}
	}
}