#define CONSOLE

#pragma warning(disable:4996)
#include <iostream>
#include <clocale>
#include "framework.h"
#include "iwannatest.h"
#include "InputData.h"
#include "EntityManager.h"
#include <vector>
typedef long long ll;
using namespace Gdiplus;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
GdiplusStartupInput gdiInput;
ULONG_PTR gdiplusToken;

HWND mainWindow;
Rect mainWindowRect;
Graphics* mainWindowGraphics;

Bitmap* mainWindowInnerBitmap;
Graphics* mainWindowInnerGraphics;
CachedBitmap* mainWindowCachedBitmap;

constexpr int mainWindowWidth = 32 * 25;
constexpr int mainWindowHeight = 32 * 19;

EntityManager entities;
InputData inputData;

unsigned long long nextFrameTime;
int fps = 50;
int frameInterval = 1000 / fps;
unsigned long long readySecond = 5;

Gdiplus::SolidBrush* whiteBrush;
Gdiplus::SolidBrush* blackBrush;

void enterFrame();
void drawFrame();
void allocateObject();
void destroyObject();

Rect toRect(RECT& rect) {
	return Rect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
}

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);



	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_IWANNATEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow)) {
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_IWANNATEST));

	MSG msg;

	while (1) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE | PM_NOYIELD)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG currentTick = GetTickCount64();
		ULONGLONG waitTime = 0;

		if (currentTick < nextFrameTime) {
			waitTime = nextFrameTime - currentTick;
		}
		
		if (waitTime <= readySecond) {
			// 시간이 조금 남은 경우, 무한사이클을 돌리면서 적절한 시간이 되었나 확인
			if (waitTime == 0) {
				if (nextFrameTime < currentTick) {
					nextFrameTime += frameInterval;
					enterFrame();
					drawFrame();
					// 프레임 계산이 지연되어 nextFrame의 시간이 너무 뒤쳐진 경우, 뒤쳐진 프레임 중에 최대 2프레임만 계산함
					if (nextFrameTime < currentTick - frameInterval - frameInterval) {
						nextFrameTime = currentTick - frameInterval - frameInterval;
					}
				}
			}
		} else {
			// 시간이 너무 많이 남은 경우 나중에 다시 확인해봄
			MsgWaitForMultipleObjects(0, NULL, FALSE, (DWORD)waitTime - (DWORD)readySecond, QS_ALLEVENTS);
			//drawFrame();
		}

	}

	return (int)msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_IWANNATEST));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_IWANNATEST);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}



BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {

	// 디버깅용ㅇㅇ요용ㅇ 콘솔
#ifdef CONSOLE
	AllocConsole();
	_tfreopen(_T("CONOUT$"), _T("w"), stdout);
	_tfreopen(_T("CONIN$"), _T("r"), stdin);
	_tfreopen(_T("CONERR$"), _T("w"), stderr);
	_tsetlocale(LC_ALL, _T(""));
#endif

	mainWindow = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, mainWindowWidth, mainWindowHeight, nullptr, nullptr, hInstance, nullptr);
	
	hInst = hInstance;

	if (!mainWindow) {
		return FALSE;
	}

	// 기존 가장자리 포함 800x608에서, 가장자리 제외하고 800x608로 바꿈
	RECT oldRect;
	GetClientRect(mainWindow, &oldRect);
	int borderWidth = mainWindowWidth - oldRect.right + oldRect.left;
	int borderHeight = mainWindowHeight - oldRect.bottom + oldRect.top;
	SetWindowPos(mainWindow, NULL, 0, 0, mainWindowWidth + borderWidth, mainWindowHeight + borderHeight, SWP_NOZORDER | SWP_NOMOVE);
	GetClientRect(mainWindow, &oldRect); // 바뀐 이후 다시
	mainWindowRect = toRect(oldRect);

	allocateObject();

	entities.init(mainWindowInnerGraphics, mainWindowCachedBitmap);
	Color backgroundColor(255, 255, 255, 255);
	entities.setPreference(backgroundColor);

	// 프레임 시간 초기화
	nextFrameTime = GetTickCount64() + frameInterval;
	
	ShowWindow(mainWindow, nCmdShow); // 보이게
	UpdateWindow(mainWindow); // 강제 WM_PAINT 실행

	// 레벨 초기화
	entities.createBlock(0.f, 0.f);

	entities.createBlock(332.f, 304.f);
	entities.createBlock(300.f, 304.f);
	entities.createBlock(268.f, 304.f);
	entities.createBlock(236.f, 304.f);
	entities.createBlock(204.f, 304.f);

	entities.createKid(270.f, 400.f);
	entities.createBlock(332.f, 368.f);
	entities.createBlock(364.f, 400.f);
	entities.createBlock(332.f, 432.f);
	entities.createBlock(332.f, 464.f);
	entities.createBlock(332.f, 496.f);

	return TRUE;
}

void allocateObject() {

	// GDI초기화
	GdiplusStartup(&gdiplusToken, &gdiInput, NULL);

	// 이미지 로드
	Kid::image = new Gdiplus::Image(L"sprites/kid.png");
	Kid::imageLeft = new Gdiplus::Image(L"sprites/kid.png");
	Kid::imageLeft->RotateFlip(Gdiplus::RotateNoneFlipX);
	Block::image = new Gdiplus::Image(L"sprites/block.png");
	
	// DC, memory DC 생성
	mainWindowGraphics = new Graphics(mainWindow);

	mainWindowInnerBitmap = new Bitmap(mainWindowRect.GetRight() - mainWindowRect.GetLeft(), mainWindowRect.GetBottom() - mainWindowRect.GetTop());
	mainWindowInnerGraphics = new Graphics(mainWindowInnerBitmap);
	mainWindowCachedBitmap = new CachedBitmap(mainWindowInnerBitmap, mainWindowGraphics);

	// brush
	whiteBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 255, 255));
	blackBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 0, 0, 0));

}

void destroyObject() {

	delete Kid::image;
	delete Kid::imageLeft;
	delete Block::image;
	Gdiplus::GdiplusShutdown(gdiplusToken);

	delete mainWindowGraphics;
	delete mainWindowInnerBitmap;
	delete mainWindowInnerGraphics;
	delete mainWindowCachedBitmap;

	delete whiteBrush;
	delete blackBrush;

}

void enterFrame() {

	entities.enterFrame(inputData);

}

void drawFrame() {

	entities.draw();

	InvalidateRect(mainWindow, NULL, FALSE);
	UpdateWindow(mainWindow);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		
		switch (wmId) {
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		Graphics g(hdc);
		g.DrawImage(mainWindowInnerBitmap, 0, 0);
		//g.DrawCachedBitmap(mainWindowCachedBitmap, 0, 0);

		EndPaint(hWnd, &ps);
		
	}
	break;
	case WM_DESTROY:
	{
		destroyObject();
		PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN:
	{
		inputData.setKeyDown((int)wParam);
	}
	break;
	case WM_KEYUP:
	{
		inputData.setKeyUp((int)wParam);
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
