#include "Core_Precompile.hpp"
#include "Core_Module.hpp"

namespace Alba
{
	namespace Core
	{
		Module* Module::ourInstance = nullptr;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Module::Module(const char* aName)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Module::~Module()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ void	Module::Register()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ void	Module::Unregister()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Module::OnRegister()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Module::OnUnregister()
		{

		}
	}
}