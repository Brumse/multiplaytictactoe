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
ID2D1SolidColorBrush *pBrushOutline;

// forward declare window proc
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void calculateLayout(){
      
  assert(pRenderTarget != NULL && "pRenderTarget must exist");
  
  D2D1_SIZE_F size = pRenderTarget->GetSize();
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
  // define globals
  pFactory = NULL;
  pRenderTarget = NULL;
  pBrush = NULL;
  pBrushOutline = NULL;

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
    SafeRelease(&pBrushOutline);
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
        const D2D1_COLOR_F color = D2D1::ColorF(0x000000);
        hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);

        const D2D1_COLOR_F colorOutline = D2D1::ColorF(0xFFFFFF);
        hr = pRenderTarget->CreateSolidColorBrush(colorOutline, &pBrushOutline);

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

    pRenderTarget->Clear(D2D1::ColorF(0x221F21));
    float padding = 10.f;
    float radius = 5.f;
    float w = 100.f;
    float h = 100.f;
    float headerY = 50.f;
    float brushSize = 2.f;

    for(int i = 0;i < 3;i++){
      for(int j = 0;j < 3;j++){
        float left = (i + 1)*padding + i*w;
        float top = headerY + (j + 1)*padding + j*h;
        float right = left + w;
        float bottom = top + h;
        D2D1_ROUNDED_RECT roundedRect = D2D1::RoundedRect(D2D1::RectF(left,top,right,bottom),radius,radius);
        
        pRenderTarget->FillRoundedRectangle(roundedRect, pBrush);
        pRenderTarget->DrawRoundedRectangle(roundedRect, pBrushOutline, brushSize, NULL);
      }
    }
    


    hr = pRenderTarget->EndDraw();
    if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET) {
      SafeRelease(&pRenderTarget);
      SafeRelease(&pBrush);
      SafeRelease(&pBrushOutline);
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
