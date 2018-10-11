#pragma once

#include "Core.hpp"
#include "Core_UniquePtr.hpp"
#include "Core_StringHash.hpp"
#include "Core_VectorMap.hpp"
#include "Core_Vector.hpp"
#include "Core_AnyDictionary.hpp"
#include "Core_LogCategory.hpp"
#include "Core_Function.hpp"

namespace Alba
{
	namespace Core
	{
		template <typename TDerived>
		class Module;

		class Time;

		ALBA_DECLARE_LOG_CATEGORY(Module);

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

				//---------------------------------------------------------------------------------
				// Load/Unload modules
				//---------------------------------------------------------------------------------
				template <typename TValueType>
				bool LoadModule(NoCaseStringHash32 aModuleNameId, const TValueType& aParam)
				{
					AnyDictionary params;
					params.Set(aParam);

					return LoadModule(aModuleNameId, std::move(params));
				}

				template <typename TValueType, class=enable_if<!is_lvalue_reference_v<TValueType>> >
				bool LoadModule(NoCaseStringHash32 aModuleNameId, TValueType&& aParam)
				{
					AnyDictionary params;
					params.Set(std::move(aParam));

					return LoadModule(aModuleNameId, std::move(params));
				}

				bool		LoadModule(NoCaseStringHash32 aModuleNameId, AnyDictionary someParams = AnyDictionary());
				void		UnloadModule(NoCaseStringHash32 aModuleNameId);
				void		UnloadAndUnregisterAll();

				//---------------------------------------------------------------------------------
				// Update
				//---------------------------------------------------------------------------------
				void		Update(const Time& aTime);

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
					typedef bool(*LoadFunc)(AnyDictionary someParams);
					typedef void(*UnloadFunc)();

					UnregisterFunc	myUnregisterFunc	= nullptr;
					LoadFunc		myLoadFunc			= nullptr;
					UnloadFunc		myUnloadFunc		= nullptr;
				};

				using UpdateFunc = FixedFunction<void(const Time& aTime)>;

				using Modules = VectorMap<NoCaseStringHash32, ModuleInfo> ;
				using ModuleUpdaters = VectorMap<NoCaseStringHash32, UpdateFunc>;

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

				void		RegisterUpdater(NoCaseStringHash32 aModuleNameId, UpdateFunc&& anUpdater);
				void		UnregisterUpdater(NoCaseStringHash32 aModuleNameId);

				//=================================================================================
				// Private Data
				//=================================================================================
				Modules				myModules;
				ModuleUpdaters		myModuleUpdaters;
		};
	}
}