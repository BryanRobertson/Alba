#include "Input_Precompile.hpp"
#include "Input_Service.hpp"
#include "Input_InitParams.hpp"
#include "Input_Debug.hpp"

#include "Core_PlatformHeader.hpp"
#include "Core_Logging.hpp"
#include "Core_WindowModule.hpp"
#include "Core_Window.hpp"
#include "Core_WindowEventHandler.hpp"

#include "Core_Time.hpp"

namespace Alba
{
	namespace Input
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		#if defined(ALBA_PLATFORM_WINDOWS)
		namespace InputServiceInternal
		{
			//-----------------------------------------------------------------------------------------
			//-----------------------------------------------------------------------------------------
			static LRESULT UpdateCallback
			(
				InputService& anInputService,
				Keyboard& aKeyboard, 
				HWND hWnd, 
				UINT uMsg, 
				WPARAM wParam, 
				LPARAM lParam
			)
			{
				(void)anInputService;
				(void)hWnd;
				(void)lParam;
				
				switch (uMsg)
				{
					//-----------------------------------------------------------------------------
					// WM_KEYDOWN
					//-----------------------------------------------------------------------------
					case WM_KEYDOWN:
					{
						KeySet& pressed = aKeyboard.GetPressedKeysMutable();
						KeySet& released = aKeyboard.GetReleasedKeysMutable();

						const Key key = static_cast<Key>(wParam);

						pressed.Insert(key);
						released.Remove(key);
					}
					return 0;

					//-----------------------------------------------------------------------------
					// WM_KEYUP
					//-----------------------------------------------------------------------------
					case WM_KEYUP:
					{
						KeySet& pressed = aKeyboard.GetPressedKeysMutable();
						KeySet& released = aKeyboard.GetReleasedKeysMutable();

						const Key key = static_cast<Key>(wParam);

						pressed.Remove(key);
						released.Insert(key);
					}
					return 0;
				}

				return 1;
			}
		}
		#endif

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		InputService::InputService()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		InputService::~InputService()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 InputService::Init(const Core::AnyDictionary& someParams)
		{
			#if defined(ALBA_PLATFORM_WINDOWS)
			{
				// Get init paramas
				if (!someParams.Has<InitParams>())
				{
					ALBA_LOG_ERROR(Input, "Failed to initialise input service! Input init params missing!");
					return 1;
				}

				const InitParams& initParams = someParams.Get<InitParams>();

				// Get window handle
				HWND windowHandle = initParams.myPlatformData.Get<HWND>();
				if (windowHandle == nullptr)
				{
					ALBA_LOG_ERROR(Input, "Failed to initialise input service! Window handle invalid!");
					return 1;
				}

				// Get window
				Core::WindowModule& windowModule = Core::WindowModule::Get();
				if (!windowModule.IsLoaded())
				{
					ALBA_LOG_ERROR(Input, "Failed to initialise input service! Failed to get window module!");
					return 1;
				}

				myWindowHandle = reinterpret_cast<void*>(windowHandle);
				Core::Window* window = windowModule.Get().GetWindow(reinterpret_cast<void*>(windowHandle));
				if (!window)
				{
					ALBA_LOG_ERROR(Input, "Failed to initialise input service! Failed to get main window!");
					return 1;
				}

				// Hook up input handler
				Core::WindowEventHandler inputHandler;
				inputHandler.myHandlerFunc = [this](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
				{
					return InputServiceInternal::UpdateCallback(*this, myKeyboard, hWnd, uMsg, wParam, lParam);
				};

				window->SetInputHandler(inputHandler);

			}
			#endif

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void InputService::ShutDown()
		{
			// Clear input handler
			if (myWindowHandle)
			{
				Core::WindowModule& windowModule = Core::WindowModule::Get();
				if (windowModule.IsLoaded())
				{
					Core::Window* window = windowModule.Get().GetWindow(myWindowHandle);
					if (window)
					{
						// Unhook event handler
						window->SetInputHandler(Core::WindowEventHandler{});
					}
				}				
			}			
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void InputService::Update(const Core::Time& aTime)
		{
			myKeyboard.UpdateKeyHeldDurations(aTime);
		}
	}
}