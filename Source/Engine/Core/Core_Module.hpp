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
		class Module : public TDerived
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
					ourInstance = ALBA_NEW(AllocationType::Module, "Module");

					ModuleInfo info;
					info.myUnregisterFunc = &TDerived::Unregister;
					info.myLoadFunc = &TDerived::Load;
					info.myUnloadFunc = &TDerived::Unload;

					const StringHash32 nameId(GetName());

					ModuleRepository::GetInstance().RegisterModule(nameId, std::move(info));
					ourInstance.myState = ModuleState::Registered;

					static_cast<TDerived*>(this)->OnRegister();
				}

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				static void	Unregister()
				{
					const StringHash32 nameId(GetName());

					ModuleRepository::GetInstance().UnregisterModule(nameId);
					static_cast<TDerived*>(this)->OnUnregister();

					ourInstance.Reset();
				}

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				static bool Load()
				{
					ALBA_ASSERT(ourInstance != nullptr, "Trying to load unregistered module!");
					return static_cast<TDerived*>(this)->OnLoad();
				}

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				static bool Unload()
				{
					ALBA_ASSERT(ourInstance != nullptr, "Trying to unload unregistered module");
					return static_cast<TDerived*>(this)->OnUnload();
				}

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				static Module& GetInstance()
				{
					return *outInstance;
				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				static const ModuleName& GetName()
				{
					return static_cast<TDerived*>().GetModuleName();
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
				// Private Data
				//=================================================================================
				ModuleState		myState;
		};

		template <typename TDerived>
		UniquePtr<TDerived> Module<TDerived>::ourInstance;
	}
}