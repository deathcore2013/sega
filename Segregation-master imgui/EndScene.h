#pragma once
#include "imgui/imgui.h"
#include <d3d9.h>
//#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
//#pragma comment(lib,"d3dx9.lib")
#include <vector>
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"




#pragma once

#include <string>
#include <memory>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>

extern WNDPROC pOldWindowProc;
extern HWND hWindow;

typedef HRESULT(STDMETHODCALLTYPE* EndSceneFn)(IDirect3DDevice9*);
HRESULT STDMETHODCALLTYPE hkEndScene(IDirect3DDevice9* vDevice);
LRESULT STDMETHODCALLTYPE hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
