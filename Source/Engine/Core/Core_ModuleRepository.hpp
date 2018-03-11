#pragma once

#include "Core.hpp"
#include "Core_UniquePtr.hpp"
#include "Core_StringHash.hpp"
#include "Core_VectorMap.hpp"

namespace Alba
{
	namespace Core
	{
		template <typename TDerived>
		class Module;

		//-----------------------------------------------------------------------------------------
		// Name	:	ModuleRepository
		// Desc	:	A repository for all registered/loaded modules
		//-----------------------------------------------------------------------------------------
		class ModuleRepository final
		{
			public:

				template <typename TDerived>
				friend class Module;

				//=================================================================================
				// Public Constructors
				//=================================================================================
				ModuleRepository();
				~ModuleRepository();

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static void					Create();
				static void					Destroy();
				static ModuleRepository&	GetInstance();

				//=================================================================================
				// Public Methods
				//=================================================================================
				void  UnloadAndUnregisterAll();

			private:

				//=================================================================================
				// Private Static Data
				//=================================================================================
				static UniquePtr<ModuleRepository> ourInstance;

				//=================================================================================
				// Private Types
				//=================================================================================
				struct ModuleInfo
				{
					typedef void(*UnregisterFunc)();
					typedef bool(*LoadFunc)();
					typedef bool(*UnloadFunc)();

					UnregisterFunc myUnregisterFunc = nullptr;
					LoadFunc	   myLoadFunc		= nullptr;
					UnloadFunc	   myUnloadFunc		= nullptr;
				};

				typedef VectorMap<StringHash32, ModuleInfo> Modules;

				//=================================================================================
				// Private Methods
				//=================================================================================
				void		RegisterModule(StringHash32 aModuleNameId, ModuleInfo&& aModule);
				void		UnregisterModule(StringHash32 aModuleNameId);
				bool		LoadModule(StringHash32 aModuleNameId);
				bool		UnloadModule(StringHash32 aModuleNameId);

				//=================================================================================
				// Private Data
				//=================================================================================
				Modules		myModules;
		};
	}
}