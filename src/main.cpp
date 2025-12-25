#include <windows.h>

#include "Engine/Engine.h"
#include "Engine/rendering/RenderBackend.h"

using namespace EngineCore;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProcW(hwnd, msg, wParam, lParam);
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
    // ---- Window class ----
    WNDCLASSW wc{};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"EngineWindow";

    RegisterClassW(&wc);

    // ---- Create window ----
    HWND hwnd = CreateWindowExW(
        0,
        wc.lpszClassName,
        L"Engine DX11",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1280, 720,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    ShowWindow(hwnd, nCmdShow);

    // ---- Initialize engine + renderer ----
    Engine& engine = Engine::Get();
    engine.InitializeRenderer(
        RenderBackend::DirectX11,
        hwnd
    );

    // ---- Main loop ----
    MSG msg{};
    while (msg.message != WM_QUIT) {
        if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        } else {
            engine.Run();
            break; // Run() has its own loop
        }
    }

    return 0;
}
