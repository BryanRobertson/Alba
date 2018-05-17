#include "Core_Precompile.hpp"
#include "Core_ModuleRepository.hpp"
#include "Core_FixedVector.hpp"
#include "Core_AnyDictionary.hpp"
#include "Core_Profile.hpp"
#include "Core_Time.hpp"

namespace Alba
{
	namespace Core
	{
		ALBA_IMPLEMENT_LOG_CATEGORY(ModuleLog);

		UniquePtr<ModuleRepository> ModuleRepository::ourInstance;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		ModuleRepository::ModuleRepository()
		{
			myModules.reserve(128);
			myModuleUpdaters.reserve(128);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		ModuleRepository::~ModuleRepository()
		{
			UnloadAndUnregisterAll();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ void ModuleRepository::Create()
		{
			ALBA_ASSERT(ourInstance == nullptr, "Module repository already exists!");
			ourInstance.reset(ALBA_NEW(AllocationType::Module, "ModuleRepository") ModuleRepository());
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ void ModuleRepository::Destroy()
		{
			ourInstance.reset();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ ModuleRepository& ModuleRepository::Get()
		{
			return *ourInstance;
		}

		//------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------
		void ModuleRepository::UnloadAndUnregisterAll()
		{
			FixedVector<Pair<NoCaseStringHash32, ModuleInfo>, 256> modules;
			for (auto& itr : myModules)
			{
				modules.push_back(itr);
			}

			for (const Pair<NoCaseStringHash32, ModuleInfo>& moduleInfo : modules)
			{
				moduleInfo.second.myUnloadFunc();
				moduleInfo.second.myUnregisterFunc();
			}
		}

		//------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------
		void ModuleRepository::Update(const Alba::Core::Time& aTime)
		{
			ALBA_PROFILE_SCOPED(ModuleRepository_Update);

			for (auto& updater : myModuleUpdaters)
			{
				updater.second(aTime);
			}
		}

		//------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------
		void ModuleRepository::RegisterModule(NoCaseStringHash32 aModuleNameId, ModuleRepository::ModuleInfo&& aModule)
		{
			ALBA_ASSERT(myModules.find(aModuleNameId) == myModules.end(), "Attempted to register the \"%s\" module twice!", aModuleNameId.LogString().c_str());
			myModules.insert(MakePair(aModuleNameId, std::move(aModule)));
		}

		//------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------
		void ModuleRepository::UnregisterModule(NoCaseStringHash32 aModuleNameId)
		{
			myModules.erase(aModuleNameId);
		}

		//------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------
		void ModuleRepository::RegisterUpdater(NoCaseStringHash32 aModuleNameId, UpdateFunc&& anUpdater)
		{
			myModuleUpdaters.insert(MakePair(aModuleNameId, std::move(anUpdater)));
		}

		//------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------
		void ModuleRepository::UnregisterUpdater(NoCaseStringHash32 aModuleNameId)
		{
			myModuleUpdaters.erase(aModuleNameId);
		}

		//------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------
		bool ModuleRepository::LoadModule(NoCaseStringHash32 aModuleNameId, const AnyDictionary& someParams)
		{
			auto itr = myModules.find(aModuleNameId);
			if (itr != myModules.end())
			{
				return itr->second.myLoadFunc(someParams);
			}
			else
			{
				ALBA_ASSERT(itr != myModules.end(), "Attempted to load unregistered module \"%s\"!", aModuleNameId.LogString().c_str());
			}
			
			return false;
		}

		//------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------
		void ModuleRepository::UnloadModule(NoCaseStringHash32 aModuleNameId)
		{
			auto itr = myModules.find(aModuleNameId);
			if (itr != myModules.end())
			{
				itr->second.myUnloadFunc();
			}
		}
	}
}

