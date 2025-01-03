#include <windows.h>

#include "Generator.hpp"
#include "resource.h"

#define MAX_TEXT_LENGTH 4

#define BUTTON_GENERATE_ID 1
#define BUTTON_EXIT_ID     2

#define EDIT_INSTALL_CODE_ID   13
#define EDIT_ACTIVATE_CODE_ID 14

#define BORDER_OFFSET 10

#define DEFAULT_CONTROL_HEIGHT 20
#define DEFAULT_CONTROL_WIDTH DEFAULT_BUTTON_WIDTH * 2 + BORDER_OFFSET

#define DEFAULT_BUTTON_WIDTH 120

#define BORDER_VERTICAL_OFFSET(itemNumber) (BORDER_OFFSET + DEFAULT_CONTROL_HEIGHT) * (itemNumber)

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_CREATE: {
            // Create text controls.
            CreateWindow(
                L"STATIC",
                L"Код установки:",
                WS_CHILD | WS_VISIBLE,
                BORDER_OFFSET,
                BORDER_VERTICAL_OFFSET(0),
                DEFAULT_CONTROL_WIDTH,
                DEFAULT_CONTROL_HEIGHT,
                hwnd,
                NULL,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL);

            HWND hwndEditInstall = CreateWindow(
                L"EDIT",
                L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                BORDER_OFFSET,
                BORDER_VERTICAL_OFFSET(1),
                DEFAULT_CONTROL_WIDTH,
                DEFAULT_CONTROL_HEIGHT,
                hwnd,
                (HMENU)EDIT_INSTALL_CODE_ID,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL);

            SendMessage(hwndEditInstall, EM_SETLIMITTEXT, MAX_TEXT_LENGTH, NULL);

            CreateWindow(
                L"STATIC",
                L"Код активации:",
                WS_CHILD | WS_VISIBLE,
                BORDER_OFFSET,
                BORDER_VERTICAL_OFFSET(2),
                DEFAULT_CONTROL_WIDTH,
                DEFAULT_CONTROL_HEIGHT,
                hwnd,
                NULL,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL);

            CreateWindow(
                L"EDIT",
                L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
                BORDER_OFFSET,
                BORDER_VERTICAL_OFFSET(3),
                DEFAULT_CONTROL_WIDTH,
                DEFAULT_CONTROL_HEIGHT,
                hwnd,
                (HMENU)EDIT_ACTIVATE_CODE_ID,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL);

            // Create the buttons.
            CreateWindow(
                L"BUTTON",
                L"Генерировать",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                BORDER_OFFSET,
                BORDER_VERTICAL_OFFSET(4),
                DEFAULT_BUTTON_WIDTH,
                DEFAULT_CONTROL_HEIGHT + 5,
                hwnd,
                (HMENU)BUTTON_GENERATE_ID,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL);

            CreateWindow(
                L"BUTTON",
                L"Выход",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                BORDER_OFFSET * 2 + DEFAULT_BUTTON_WIDTH,
                BORDER_VERTICAL_OFFSET(4),
                DEFAULT_BUTTON_WIDTH,
                DEFAULT_CONTROL_HEIGHT + 5,
                hwnd,
                (HMENU)BUTTON_EXIT_ID,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL);
            return EXIT_SUCCESS;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == BUTTON_GENERATE_ID) {
                HWND hwndEditInstall  = GetDlgItem(hwnd, EDIT_INSTALL_CODE_ID);
                HWND hwndEditActivate = GetDlgItem(hwnd, EDIT_ACTIVATE_CODE_ID);

                try {
                    wchar_t installCode[MAX_TEXT_LENGTH + 1];
                    GetWindowTextW(hwndEditInstall, installCode, MAX_TEXT_LENGTH + 1);

                    Generator generator;
                    std::wstring activateCode = generator.GenerateActivateCode(installCode);
                    SetWindowTextW(hwndEditActivate, activateCode.data());
                }
                catch (const std::exception&) {
                    SetWindowTextW(hwndEditActivate, L"Ошибка генерации!");
                }
            }
            if (LOWORD(wParam) == BUTTON_EXIT_ID) {
                PostMessage(hwnd, WM_CLOSE, 0, 0);
            }
            return EXIT_SUCCESS;
        }
        case WM_DESTROY: {
            PostQuitMessage(EXIT_SUCCESS);
            return EXIT_SUCCESS;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
            EndPaint(hwnd, &ps);
            return EXIT_SUCCESS;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

    RegisterClass(&wc);

    // Create the window.
    HWND hwnd = CreateWindowEx(
        NULL,
        CLASS_NAME,
        L"Qt2 KeyGen",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,

        // Size and position
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        BORDER_OFFSET * 5 + DEFAULT_BUTTON_WIDTH * 2,
        BORDER_VERTICAL_OFFSET(6) + BORDER_OFFSET + 5,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
        return EXIT_SUCCESS;

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return EXIT_SUCCESS;
}