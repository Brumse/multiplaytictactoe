#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

#include <d2d1.h>
#include <cassert>

/**
 * @brief null handling release function
 */
template <class T> void SafeRelease(T **ppT) {
  if (*ppT) {
    (*ppT)->Release();
    *ppT = NULL;
  }
}

// globals
ID2D1Factory *pFactory;
ID2D1HwndRenderTarget *pRenderTarget;
ID2D1SolidColorBrush *pBrush;
D2D1_ELLIPSE ellipse;

// forward declare window proc
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void calculateLayout(){
      
  assert(pRenderTarget != NULL && "pRenderTarget must exist");

  D2D1_SIZE_F size = pRenderTarget->GetSize();
  const float x = size.width / 2;
  const float y = size.height / 2;
  const float radius = min(x, y);
  ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), // center
                                radius,              // radius x
                                radius               // radius y
);
}
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
  // define globals
  pFactory = NULL;
  pRenderTarget = NULL;
  pBrush = NULL;

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
  case WM_CREATE:
    if (FAILED(
            D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory))) {
      return -1;
    }
    return 0;
  case WM_DESTROY:
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBrush);
    SafeRelease(&pFactory);

    PostQuitMessage(0);
    return 0;

  case WM_PAINT: {
    HRESULT hr = S_OK; // initialize return code

    // create the render target if needed
    if (pRenderTarget == NULL) {
      RECT rc;
      GetClientRect(hwnd, &rc);

      D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

      hr = pFactory->CreateHwndRenderTarget(
          D2D1::RenderTargetProperties(),        // target props
          D2D1::HwndRenderTargetProperties(hwnd, // hwnd
                                           size  // size
                                           ),    // hwnd render target props
          &pRenderTarget                         // render target
      );

      if (SUCCEEDED(hr)) {
        const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0);
        hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);

        // calculate the layout
        if (SUCCEEDED(hr)) {
          if (pRenderTarget != NULL) {
            calculateLayout();

          }
        }
      }
    }

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    pRenderTarget->BeginDraw();

    pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
    pRenderTarget->FillEllipse(ellipse, pBrush);

    hr = pRenderTarget->EndDraw();
    if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET) {
      SafeRelease(&pRenderTarget);
      SafeRelease(&pBrush);
    }

    EndPaint(hwnd, &ps);
  }
    return 0;
  case WM_SIZE:
    if (pRenderTarget != NULL) {
      RECT rc;
      GetClientRect(hwnd, &rc);

      // resize the render target
      D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
      pRenderTarget->Resize(size);

      calculateLayout();
      InvalidateRect(hwnd, // hwnd
                     NULL, // rect
                     FALSE // erase
      );
    }
    return 0;
  }

  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
