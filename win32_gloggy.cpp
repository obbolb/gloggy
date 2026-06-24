#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // Check what message Windows is sending us
    switch (uMsg) {
        case WM_DESTROY:
            // When the user clicks the 'X', tell the message loop to quit
            PostQuitMessage(0);
            return 0;
    }

    // CRITICAL: Let Windows handle any message we didn't explicitly write code for
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    WNDCLASS window_class = {0};
    window_class.hInstance = hInstance;
    window_class.lpszClassName = "my window";
    window_class.lpfnWndProc = WindowProc;

    // Optional, but recommended: Give the window a default gray/white background
    // so it doesn't render invisibly or glitchy.
    window_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&window_class);

    HWND hwnd = CreateWindowEx(
        0,
        window_class.lpszClassName,
        "my window",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        0, NULL, hInstance, 0
    );

    OutputDebugString("yooo\n");

    // THE MESSAGE LOOP
    // This blocks the program from exiting and keeps the window alive.
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg); // Translates keystrokes into character messages
        DispatchMessage(&msg);  // Sends the message to your WindowProc function
    }

    return 0;
}
