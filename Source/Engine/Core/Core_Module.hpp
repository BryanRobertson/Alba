#pragma once

//-----------------------------------------------------------------------------------------
// Name	:	Module
// Desc	:	Composes the application into multiple self-contained modules that can be 
//			loaded and unloaded at runtime
//-----------------------------------------------------------------------------------------
#include "Core.hpp"
#include "Core_String.hpp"
#include "Core_UniquePtr.hpp"
#include "Core_ModuleRepository.hpp"
#include "Core_AnyDictionary.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name: ModuleState
		//-----------------------------------------------------------------------------------------
		enum class ModuleState : uint8
		{
			None,
			Registered,
			Loaded
		};

		//-----------------------------------------------------------------------------------------
		// Name	:	Module<TDerived>
		//-----------------------------------------------------------------------------------------
		template <typename TDerived>
		class Module
		{
			public:

				//=================================================================================
				// Public Types
				//=================================================================================
				typedef String ModuleName;

				//=================================================================================
				// Public Static Methods
				//=================================================================================

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				static void	Register()
				{
					ALBA_LOG_INFO(ModuleLog, "RegisterModule( \"%s\" )", GetName().c_str());

					ourInstance.reset(ALBA_NEW(AllocationType::Module, "Module") TDerived());

					ModuleRepository::ModuleInfo info;
					info.myUnregisterFunc = &TDerived::Unregister;
					info.myLoadFunc = &TDerived::Load;
					info.myUnloadFunc = &TDerived::Unload;

					const StringHash32 nameId(GetName());

					ModuleRepository::Get().RegisterModule(nameId, std::move(info));
					ourInstance->myState = ModuleState::Registered;

					static_cast<TDerived*>(ourInstance.get())->OnRegister();
				}

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				static void	Unregister()
				{
					ALBA_LOG_INFO(ModuleLog, "UnregisterModule( \"%s\" )", GetName().c_str());

					const StringHash32 nameId(GetName());

					ModuleRepository::Get().UnregisterModule(nameId);
					static_cast<TDerived*>(ourInstance.get())->OnUnregister();

					ourInstance.reset();
				}

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				static TDerived& Get()
				{
					return *ourInstance;
				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				static const ModuleName& GetName()
				{
					static const ModuleName moduleName(TDerived::GetModuleName());
					return moduleName;
				}

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				static ModuleState GetState()
				{
					return ourInstance ? ourInstance->myState : ModuleState::None;
				}

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				static bool IsLoaded()
				{
					return GetState() == ModuleState::Loaded;
				}

			private:

				//=================================================================================
				// Private Static Data
				//=================================================================================
				static UniquePtr<TDerived> ourInstance;

				//=================================================================================
				// Private Static Methods
				//=================================================================================

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				static bool Load(const AnyDictionary& someParams)
				{
					ALBA_LOG_INFO(ModuleLog, "LoadModule( \"%s\" )", GetName().c_str());

					ALBA_ASSERT(ourInstance != nullptr, "Trying to load unregistered module!");
					const bool result = static_cast<TDerived*>(ourInstance.get())->OnLoad(someParams);

					if (result)
					{
						ourInstance->myState = ModuleState::Loaded;
					}

					return result;
				}

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				static void Unload()
				{
					ALBA_LOG_INFO(ModuleLog, "UnloadModule( \"%s\" )", GetName().c_str());

					ALBA_ASSERT(ourInstance != nullptr, "Trying to unload unregistered module");
					static_cast<TDerived*>(ourInstance.get())->OnUnload();

					ourInstance->myState = ModuleState::Registered;
				}

				//=================================================================================
				// Private Data
				//=================================================================================
				ModuleState	 myState = ModuleState::None;
		};

		template <typename TDerived>
		UniquePtr<TDerived> Module<TDerived>::ourInstance;
	}
}