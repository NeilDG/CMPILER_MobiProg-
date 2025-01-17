#include "Window.h"
#include "imgui.h"

//declare for handling mouse and key events in IMGUI.
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static Window* windowInstance = NULL;

Window::Window()
{
    windowInstance = this;
}

Window::~Window()
{
}


LRESULT CALLBACK WndProc(HWND windowHandle, UINT msg, WPARAM wparam, LPARAM lparam) {
    //Used for processing input events for IMGUI
    if (ImGui_ImplWin32_WndProcHandler(windowHandle, msg, wparam, lparam))
        return true;

    switch (msg) {
    case WM_CREATE: {
        windowInstance->onCreate();
        break;
    }
    case WM_SETFOCUS: {
        windowInstance->onFocus();
        break;
    }
    case WM_KILLFOCUS: {
        windowInstance->onDefocus();
        break;
    }
    case WM_DESTROY: {
        windowInstance->onDestroy();
        ::PostQuitMessage(0);
        break;
    }
    default:
        return::DefWindowProc(windowHandle, msg, wparam, lparam);
    }
}
bool Window::createWindow()
{
    WNDCLASSEX wcx;
    // Fill in the window class structure with parameters 
    // that describe the main window. 
    wcx.cbSize = sizeof(WNDCLASSEX);          // size of structure 
    wcx.style = NULL;
    wcx.cbClsExtra = NULL;                // no extra class memory 
    wcx.cbWndExtra = NULL;                // no extra window memory 
    wcx.hIcon = LoadIcon(NULL,
        IDI_APPLICATION);              // predefined app. icon 
    wcx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(NULL,
        IDC_ARROW);                    // predefined arrow 
    wcx.hbrBackground = (HBRUSH)COLOR_WINDOW;            // white background brush 
    wcx.lpszMenuName = L"GDENG2-Engine";    // name of menu resource. L
    wcx.lpszClassName = L"GDENG2-EngineClass";  // name of window class. NOTE: This name is very important for CreateWindowEx. This acts like a key to all registered windows so far.
    wcx.lpfnWndProc = WndProc;
    wcx.hInstance = NULL;
    // Register the window class. 
    if (!::RegisterClassEx(&wcx)) {
        std::cout << "Failed creating window \n";
        return false;
    }

    this->windowHandle = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, wcx.lpszClassName, L"MobiProg++", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1440, 900, NULL, NULL, NULL, NULL);
    //show window
    ::ShowWindow(this->windowHandle, SW_SHOW);
    ::UpdateWindow(this->windowHandle);

    return true;
}

bool Window::broadcast()
{

    this->onUpdate();
    MSG msg;
    if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Sleep(1); //to avoid super continuous frame update.
    return true;
}

bool Window::release()
{
  if (::DestroyWindow(this->windowHandle)) {
      this->onDestroy();
      return true;
  }
  else {
      return false;
  }
}

bool Window::isRunning()
{
    return this->runningFlag;
}

RECT Window::getClientWindowRect()
{
    RECT rc;
    ::GetClientRect(this->windowHandle, &rc);

    return rc;
}

HWND Window::getWindowHandle()
{
    return this->windowHandle;
}

void Window::onCreate()
{
    this->runningFlag = true;
    //std::cout << "Called window onCreate \n";
}

void Window::onUpdate()
{
    bool isNull = this->windowHandle != NULL;
    //std::cout << "Window handle is: " << std::boolalpha << isNull << "\n";
}

void Window::onDestroy()
{
    this->runningFlag = false;
}

void Window::onFocus()
{
}

void Window::onDefocus()
{
}
