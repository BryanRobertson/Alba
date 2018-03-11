#include "Core_Precompile.hpp"
#include "Core_ModuleRepository.hpp"
#include "Core_FixedVector.hpp"

namespace Alba
{
	namespace Core
	{
		UniquePtr<ModuleRepository> ModuleRepository::ourInstance;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		ModuleRepository::ModuleRepository()
		{

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
		/*static*/ ModuleRepository& ModuleRepository::GetInstance()
		{
			return *ourInstance;
		}

		//------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------
		void ModuleRepository::UnloadAndUnregisterAll()
		{
			FixedVector<Pair<StringHash32, ModuleInfo>, 256> modules;
			for (auto& itr : myModules)
			{
				modules.push_back(itr);
			}

			for (const Pair<StringHash32, ModuleInfo>& moduleInfo : modules)
			{
				moduleInfo.second.myUnloadFunc();
				moduleInfo.second.myUnregisterFunc();
			}
		}

		//------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------
		void ModuleRepository::RegisterModule(StringHash32 aModuleNameId, ModuleRepository::ModuleInfo&& aModule)
		{
			myModules.insert(MakePair(aModuleNameId, std::move(aModule)));
		}

		//------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------
		void ModuleRepository::UnregisterModule(StringHash32 aModuleNameId)
		{
			myModules.erase(aModuleNameId);
		}

		//------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------
		bool ModuleRepository::LoadModule(StringHash32 aModuleNameId)
		{
			auto itr = myModules.find(aModuleNameId);
			if (itr != myModules.end())
			{
				return itr->second.myLoadFunc();
			}
			
			return false;
		}

		//------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------
		bool ModuleRepository::UnloadModule(StringHash32 aModuleNameId)
		{
			auto itr = myModules.find(aModuleNameId);
			if (itr != myModules.end())
			{
				return itr->second.myUnloadFunc();
			}

			return false;
		}
	}
}

