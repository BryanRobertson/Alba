#pragma once

#include "Core.hpp"
#include "Core_UniquePtr.hpp"
#include "Core_StringHash.hpp"
#include "Core_VectorMap.hpp"
#include "Core_AnyDictionary.hpp"
#include "Core_LogCategory.hpp"

namespace Alba
{
	namespace Core
	{
		template <typename TDerived>
		class Module;

		ALBA_DECLARE_LOG_CATEGORY(ModuleLog);

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
				static ModuleRepository&	Get();

				//=================================================================================
				// Public Methods
				//=================================================================================
				bool		LoadModule(NoCaseStringHash32 aModuleNameId, const AnyDictionary& someParams = AnyDictionary());
				void		UnloadModule(NoCaseStringHash32 aModuleNameId);
				void		UnloadAndUnregisterAll();

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
					typedef bool(*LoadFunc)(const AnyDictionary& someParams);
					typedef void(*UnloadFunc)();

					UnregisterFunc myUnregisterFunc = nullptr;
					LoadFunc	   myLoadFunc		= nullptr;
					UnloadFunc	   myUnloadFunc		= nullptr;
				};

				typedef VectorMap<NoCaseStringHash32, ModuleInfo> Modules;

				//=================================================================================
				// Private Constructors
				//=================================================================================
				ModuleRepository(const ModuleRepository&) {}
				ModuleRepository(ModuleRepository&&) {}

				//=================================================================================
				// Private Methods
				//=================================================================================
				void		RegisterModule(NoCaseStringHash32 aModuleNameId, ModuleInfo&& aModule);
				void		UnregisterModule(NoCaseStringHash32 aModuleNameId);

				//=================================================================================
				// Private Data
				//=================================================================================
				Modules		myModules;
		};
	}
}