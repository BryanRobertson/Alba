#pragma once

#include "Framework_API.hpp"
#include "Core_Module.hpp"
#include "Core_Window.hpp"
#include "Core_UniquePtr.hpp"

namespace Alba
{
	namespace Framework
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	Framework
		//-----------------------------------------------------------------------------------------
		class FrameworkModule : public Core::Module<FrameworkModule>
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static const char* GetModuleName() { return "Alba.Framework"; }

				//=================================================================================
				// Public Methods
				//=================================================================================
				void	OnRegister();
				void	OnUnregister();

				bool	OnLoad(const Core::AnyDictionary& someParameters);
				void	OnUnload();		

				Core::Window& GetWindow() const 
				{
					return *ourApplicationWindow; 
				}

			private:

				//=================================================================================
				// Public Data
				//=================================================================================
				Core::UniquePtr<Core::Window> ourApplicationWindow;
		};
	}
}