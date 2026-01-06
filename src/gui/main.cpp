#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

// forward declare window proc
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
  // register window class
  const wchar_t CLASS_NAME[] = L"TicTacToe";

  // create and register class
  WNDCLASS wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  // create the window
  HWND hwnd = CreateWindowEx(0,                   // options window styles
                             CLASS_NAME,          // class name
                             L"Tic Tac Toe Game", // window name
                             WS_OVERLAPPEDWINDOW, // window style,
                             CW_USEDEFAULT, CW_USEDEFAULT, // x, y
                             CW_USEDEFAULT, CW_USEDEFAULT, // width, height
                             NULL,                         // parent window
                             NULL,                         // menu
                             hInstance,                    // instance handle
                             NULL // additional application data
  );

  // check that creation was successful
  if (hwnd == NULL) {
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);

  // message loop
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}

// window event callback
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // all painting happens here
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

    EndPaint(hwnd, &ps);
  }
    return 0;
  }

  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
