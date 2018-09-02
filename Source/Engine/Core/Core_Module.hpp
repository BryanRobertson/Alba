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
#include "Core_Logging.hpp"

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
					ALBA_LOG_INFO(Module, "RegisterModule( \"%s\" )", GetName().c_str());

					ourInstance.reset(ALBA_NEW(AllocationType::Module, "Module") TDerived());

					ModuleRepository::ModuleInfo info;
					info.myUnregisterFunc = &TDerived::Unregister;
					info.myLoadFunc = &TDerived::Load;
					info.myUnloadFunc = &TDerived::Unload;

					const NoCaseStringHash32 nameId(GetName());

					ModuleRepository::Get().RegisterModule(nameId, std::move(info));
					ourInstance->myState = ModuleState::Registered;

					if constexpr (HasOnRegisterMethod<TDerived>::Value)
					{
						static_cast<TDerived*>(ourInstance.get())->OnRegister();
					}					
				}

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				static void	Unregister()
				{
					ALBA_LOG_INFO(Module, "UnregisterModule( \"%s\" )", GetName().c_str());

					const NoCaseStringHash32 nameId(GetName());

					ModuleRepository::Get().UnregisterModule(nameId);
					
					if constexpr (HasOnUnregisterMethod<TDerived>::Value)
					{
						static_cast<TDerived*>(ourInstance.get())->OnUnregister();
					}
					
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
				// Private Types
				//=================================================================================
				template<typename T>
				struct HasUpdateMethod
				{
					private:

						template <typename T2> static constexpr decltype(std::declval<T2>().Update(Alba::Core::Time()), bool()) Check(int) { return true; }
						template <typename T2> static constexpr bool Check(...) { return false; }

					public:

						static constexpr bool Value = Check<T>(int());
				};

				template<typename T>
				struct HasOnRegisterMethod
				{
					private:

						// We test if the type has serialize using decltype and declval.
						template <typename T2> static constexpr decltype(std::declval<T2>().OnRegister(), bool()) Check(int) { return true; }
						template <typename T2> static constexpr bool Check(...) { return false; }


					public:

						static constexpr bool Value = Check<T>(int());					
				};

				template<typename T>
				struct HasOnUnregisterMethod
				{
					private:

						// We test if the type has serialize using decltype and declval.
						template <typename T2> static constexpr decltype(std::declval<T2>().OnUnregister(), bool()) Check(int) { return true; }
						template <typename T2> static constexpr bool Check(...) { return false; }

					public:

						static constexpr bool Value = Check<T>(int());
				};


				//=================================================================================
				// Private Static Data
				//=================================================================================
				static UniquePtr<TDerived> ourInstance;

				//=================================================================================
				// Private Static Methods
				//=================================================================================

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				static bool Load(AnyDictionary someParams)
				{
					ALBA_LOG_INFO(Module, "LoadModule( \"%s\" )", GetName().c_str());

					ALBA_ASSERT(ourInstance != nullptr, "Trying to load unregistered module!");
					const bool result = static_cast<TDerived*>(ourInstance.get())->OnLoad(std::move(someParams));

					if (result)
					{
						ourInstance->myState = ModuleState::Loaded;

						// Register Update method if we have one
						if constexpr (HasUpdateMethod<TDerived>::Value)
						{
							const NoCaseStringHash32 nameId(GetName());

							TDerived* instance = ourInstance.get();

							ModuleRepository& moduleRepository = ModuleRepository::Get();
							moduleRepository.RegisterUpdater(nameId, [instance](const Time& aTime) 
							{ 
								instance->Update(aTime); 
							});
						}
					}

					return result;
				}

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				static void Unload()
				{
					ALBA_LOG_INFO(Module, "UnloadModule( \"%s\" )", GetName().c_str());

					ALBA_ASSERT(ourInstance != nullptr, "Trying to unload unregistered module");
					static_cast<TDerived*>(ourInstance.get())->OnUnload();

					// Unregister updater if we have an Update method
					if constexpr (HasUpdateMethod<TDerived>::Value)
					{
						const NoCaseStringHash32 nameId(GetName());

						ModuleRepository& moduleRepository = ModuleRepository::Get();
						moduleRepository.UnregisterUpdater(nameId);
					}

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