#include "Core_Precompile.hpp"
#include "Core_Window.hpp"
#include "Core_Optional.hpp"
#include "Core_PlatformHeader.hpp"
#include "Core_WindowEventHandler.hpp"
#include "Core_Logging.hpp"
#include "Core_Platform.hpp"

namespace Alba
{
	namespace Core
	{
		static const char* theWindowClassName = "Alba::Core::WindowClass";
		enum class WindowsReturnCode 
		{ 
			Failed = 0 
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		ALBA_IMPLEMENT_LOG_CATEGORY(WindowLogCategory);

		//-----------------------------------------------------------------------------------------
		// Name	:	WindowImpl
		// Desc	:	Window implementation details
		//-----------------------------------------------------------------------------------------
		struct WindowImpl
		{
			WindowImpl(Window& aWindow)
				: myWindow(aWindow)
				, myPlatformWindowHandle(nullptr)
				, myIsQuitMessageReceived(false)
			{
				myEventHandler.Bind(this, &WindowImpl::DefaultWindowHandler);
			}

			//-----------------------------------------------------------------------------------------
			//-----------------------------------------------------------------------------------------
			bool Update()
			{
				MSG msg;

				//Check for window messages
				if (PeekMessage(&msg, myPlatformWindowHandle, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}

				return true;
			}

			//-----------------------------------------------------------------------------------------
			//-----------------------------------------------------------------------------------------
			LRESULT DefaultWindowHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
			{
				if (uMsg == WM_QUIT)
				{
					myIsQuitMessageReceived = true;
				}

				return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}

			//-----------------------------------------------------------------------------------------
			//-----------------------------------------------------------------------------------------
			static LRESULT CALLBACK MessageDispatcher(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
			{
				//---------------------------------------------------------------------------------
				// If instance pointer is setup, then route to the instance
				//---------------------------------------------------------------------------------
				if (WindowImpl* instance = reinterpret_cast<WindowImpl*>(GetWindowLongPtr(hWnd, GWLP_USERDATA)))
				{
					if (instance->myEventHandler.myHandlerFunc)
					{
						return instance->myEventHandler.myHandlerFunc(hWnd, uMsg, wParam, lParam);
					}
				}
				
				//---------------------------------------------------------------------------------
				// Setup instance pointer (or handle messages that get called before pointer is set up)
				//---------------------------------------------------------------------------------
				switch (uMsg)
				{
					case WM_NCCREATE:
					{
						//Use SetWindowLong to store pointer to instance
						//Get pointer from the lpCreateParams passed to CreateWindowEx
						WindowImpl* instance = reinterpret_cast<WindowImpl*> (reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
						SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(instance));
					}
					break;

					case WM_GETMINMAXINFO:
					{
						// This gets called before WM_NCCREATE, so the window pointer isn't set up yet
					}
					break;

					case WM_CLOSE:
					{
						PostQuitMessage(0);
					}
					break;
				}

				return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			void SetWindowTitle(const char* aTitle)
			{
				myTitleText = aTitle;
				SendMessage(myPlatformWindowHandle, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(aTitle));
			}

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			const FixedString<32>& GetWindowTitle() const
			{
				return myTitleText;
			}

			WindowEventHandler  myEventHandler;
			HWND				myPlatformWindowHandle = NULL;
			FixedString<32>		myTitleText;

			Window&				myWindow;
			bool				myIsQuitMessageReceived = false;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ UniquePtr<Window> Window::Create()
		{
			return UniquePtr<Window>(ALBA_NEW(AllocationType::Window, "Window") Window());
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Window::Window()
			: myImpl(ALBA_NEW(AllocationType::Window, "Window") WindowImpl(*this))
		{
			
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Window::~Window()
		{
			Destroy();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Window::Init(const WindowParams& aParams)
		{
			const HINSTANCE hInstance = GetModuleHandle(nullptr);

			//----------------------------------------------------------------------
			// Register window class
			//----------------------------------------------------------------------
			WNDCLASSEX windowClass;
			std::memset(&windowClass, 0, sizeof(windowClass));

			windowClass.cbSize				= sizeof(windowClass);
			windowClass.style				= CS_OWNDC;
			windowClass.hInstance			= hInstance;
			windowClass.hCursor				= LoadCursor(nullptr, IDC_ARROW);
			windowClass.lpszClassName		= theWindowClassName;
			windowClass.hIcon				= LoadIcon(GetModuleHandle(nullptr), "IDI_ICON1");
			windowClass.hIconSm				= LoadIcon(GetModuleHandle(nullptr), "IDI_ICON1");
			windowClass.lpfnWndProc			= &WindowImpl::MessageDispatcher;

			if (windowClass.hIcon == nullptr)
			{
				windowClass.hIcon = LoadIcon(NULL, "IDI_APPLICATION");
			}

			if (windowClass.hIconSm == nullptr)
			{
				windowClass.hIcon = LoadIcon(NULL, "IDI_APPLICATION");
			}

			ALBA_LOG(WindowLogCategory, LogLevel::Info, "RegisterWindowClass(%s)", theWindowClassName);

			if (RegisterClassEx(&windowClass) == int(WindowsReturnCode::Failed))
			{
				ALBA_LOG
				(
					WindowLogCategory, 
					LogLevel::Info, 
					"Failed! Error: {%d, \"%s\"}", 
					GetLastError(), 
					GetLastErrorString().c_str()
				);

				return false;
			}
			
			//----------------------------------------------------------------------
			// Create window
			//----------------------------------------------------------------------
			ALBA_LOG
			(
				WindowLogCategory,
				LogLevel::Info, 
				"CreateWindow(x=%d, y=%d, w=%d, h=%d)",
				aParams.myPosition.first, aParams.myPosition.second,
				aParams.mySize.first, aParams.mySize.second
			);

			const DWORD dwStyle		= WS_OVERLAPPED | WS_BORDER | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU;
			const DWORD dwExStyle	= WS_EX_WINDOWEDGE;

			myImpl->myPlatformWindowHandle = CreateWindowEx
			(
				dwExStyle,								//dwExStyle
				theWindowClassName,						//className
				aParams.myTitle.c_str(),				//lpWindowName
				dwStyle,								//dwStyle
				aParams.myPosition.first,				//x
				aParams.myPosition.second,				//y
				aParams.mySize.first,					//width
				aParams.mySize.second,					//height
				0,										//hWndParent
				0,										//hMenu
				hInstance,								//hInstance
				reinterpret_cast<LPVOID>(myImpl.get())	//lpParam
			);

			if (myImpl->myPlatformWindowHandle == nullptr)
			{
				ALBA_LOG
				(
					WindowLogCategory,
					LogLevel::Info,
					"Failed! Error: {%d, \"%s\"}",
					GetLastError(),
					GetLastErrorString().c_str()
				);

				UnregisterClass(theWindowClassName, hInstance);
				return false;
			}

			myPlatformData.Set<HWND>(myImpl->myPlatformWindowHandle);

			//----------------------------------------------------------------------
			// Show window
			//----------------------------------------------------------------------
			if (!aParams.myIsHidden)
			{
				ShowWindow(myImpl->myPlatformWindowHandle, SW_SHOW);
			}

			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Window::Destroy()
		{
			if (myImpl->myPlatformWindowHandle)
			{
				DestroyWindow(myImpl->myPlatformWindowHandle);
				UnregisterClass(theWindowClassName, GetModuleHandle(NULL));
			}			
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Window::Update()
		{
			return myImpl->Update();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Window::SetTitleText(const char* aStr)
		{
			myImpl->SetWindowTitle(aStr);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		FixedString<32> Window::GetTitleText() const
		{
			return myImpl->GetWindowTitle();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Window::SetEventHandler(const WindowEventHandler& aHandler)
		{
			myImpl->myEventHandler = aHandler;
		}
	}
}