#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <iostream>
#include <winnls.h>

//function headers
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);    //Window procedure function
void onResize(HWND hwnd, UINT flag, int width, int height);                         //executed when window is resized

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                           // Optional window styles.
        CLASS_NAME,                  // Window class
        L"Learn to Program Windows", // Window text
        WS_OVERLAPPEDWINDOW,         // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,      // Parent window
        NULL,      // Menu
        hInstance, // Instance handle
        NULL       // Additional application data
    );

    //Cancel the window procedure if it isnt assigned to a process number.
    if (hwnd == NULL)
    {
        return 0;
    }

    //Show the window
    ShowWindow(hwnd, nCmdShow);

    

    // Run the message loop.
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }

        case WM_INPUTLANGCHANGE:
        {
            std::cout << lParam << std::endl;
            std::cout << "Input Changed" << std::endl;
            break;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
            break;
        }

        case WM_SIZE:
        {
            int width = LOWORD(lParam);  // Macro to get the low-order word.
            int height = HIWORD(lParam); // Macro to get the high-order word.

            // Respond to the message:
            onResize(hwnd, (UINT)wParam, width, height);
            break;
        }
        
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void onResize(HWND hwnd, UINT flag, int width, int height)
{   
    if(flag == 0 && width == 0 && height == 0) return;
    std::cout << "================================================================" << std::endl;
    switch(flag)
    {
        case 0: // If the window is resized run the code below
            {
                std::cout << "Window has been resized" << std::endl;
                break;
            }
        case 1: // If the window is minimized run the code below.
            {
                std::cout << "Window has been minimized" << std::endl;
                break;
            }
        case 2: // If the window is maximized run the code below
            {
                std::cout << "Window has been maximized" << std::endl;
                break;
            }
    }
    std::cout << "================================================================" << std::endl;
    std::cout << "New size" << std::endl;
    std::cout << "width: " << width << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << "================================================================" << std::endl;
}