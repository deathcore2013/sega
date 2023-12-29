#include <Windows.h>

#include <cstdio>

#define Bits_32

#include "Byte_Manager/Byte_Manager.hpp"

#include "Redirection_Manager/Redirection_Manager.hpp"

#include "Post_Entity_Packet_Received.hpp"

#include "Extended_Interface.hpp"

#pragma comment(lib, "WinMM.Lib")
#include "minhook/minhook.hpp"
#include <d3d9.h>
//#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
//#pragma comment(lib,"d3dx9.lib")
#include "Sounds.hpp"
#include "EvolutionIconsQunion.h"
#include "Montserrat-ExtraBold.h"
#include "Montserrat-Medium.h"
#include "Montserrat-Regular.h"
#include "Event_Listener.hpp"

#include "Write_Events.hpp"

#include "Shutdown.hpp"

#include "Interpolate.hpp"

#include "Update_Animation.hpp"

#include "Compute_Torso_Rotation.hpp"

#include "Compute_First_Command_To_Execute.hpp"

#include "Store_Prediction_Results.hpp"

#include "Setup_Move.hpp"

#include "Fall_Damage.hpp"
#include "Search.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cctype>




#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "EndScene.h"
#include "Finish_Move.hpp"

#include "Item_Post_Frame.hpp"

#include "Weapon_Spread.hpp"

#include <vector>

#include "Copy_User_Command.hpp"

#include "Send_Move.hpp"

#include "Draw_Crosshair.hpp"

#include "Precache.hpp"
extern EndSceneFn oEndScene;
extern ImFont* InterMedium;
extern ImFont* IconFont;
ImFont* InterMedium;
ImFont* IconFont;
bool b_MenuEnable = false;

DWORD players_list;
DWORD players_list_offset = 0x38;
DWORD players_offset = 0x04035C0;
DWORD player_size = 0x140;
DWORD hp_offset = 0x24;
DWORD side_offset = 0x20; //1 spectractor , 2 T side , 3 ct side
DWORD x_offset = 0x28;
DWORD y_offset = 0x2C;
DWORD z_offset = 0x30;
DWORD rotate_offset = 0x38;
DWORD my_coord_offset = 0x039D4F0;
DWORD my_coord_list;
DWORD my_coord_x = 0x64;
DWORD my_coord_y = 0x68;
DWORD my_coord_z = 0x6C;

static bool ESP = false;
static bool Chams = false;
static bool HealthESP = false;
static bool Tracers = false;

static float AimbotFOV = 120.f;
static float AimbotSens = 1.f;
static bool Aimbot = false;
static bool DrawFOV = false;

static bool ThirdPerson = false;
static bool BunnyHop = false;
static bool NoFlash = false;

class D3DDeviceWrapper
{
public:
	IDirect3DDevice9* pDevice;
};
D3DDeviceWrapper* D3XDevice()
{
	typedef D3DDeviceWrapper* (*EndSceneFn)();

	static auto hMod(((unsigned __int32)LoadLibraryW(L"shaderapidx9.dll")));
	static auto Offset = (EndSceneFn)((std::uintptr_t)hMod + 48192);

	return Offset();
}


unsigned int get_virtual(void* class_, unsigned int index) { return (unsigned int)(*(int**)class_)[index]; }
bool initializeminhook() {

	if (MH_Initialize() != MH_OK)
	{
		return FALSE;
	}

	auto endscene = reinterpret_cast<void*>(get_virtual(D3XDevice()->pDevice, 42));

	if (MH_CreateHook(endscene, &hkEndScene, reinterpret_cast<void**>(&oEndScene)) != MH_OK)
	{
		return FALSE;
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
	{
		return FALSE;
	}

	return TRUE;
}
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
EndSceneFn oEndScene;
#define GUI_KEY_DOWN( KeyNum ) ( GetAsyncKeyState(KeyNum) & 0x1 )
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
bool PressedKeys[256]{ false };
WNDPROC pOldWindowProc = nullptr;
HWND hWindow = nullptr;

bool init = false;
bool initImgui = false;
void water()
{
	ImGui::PushFont(InterMedium);
	auto draw = ImGui::GetOverlayDrawList();
	auto size = ImGui::CalcTextSize("DEATHCORE RUSSIAN CHEATS");
	draw->AddRectFilledMultiColor(ImVec2(0, 10), ImVec2(size.x + 45, 18 + 10), ImColor(33, 33, 33, 125), ImColor(255, 255, 0, 5), ImColor(33, 33, 33, 5), ImColor(33, 33, 33, 125));
	draw->AddText(ImVec2(5, 9 - size.y / 2 + 10), ImColor(250, 120, 20), "DEATHCORE ");
	draw->AddText(ImVec2(100, 9 - size.y / 2 + 10), ImColor(0, 120, 20), "RUSSIAN ");
	draw->AddText(ImVec2(170, 9 - size.y / 2 + 10), ImColor(220, 0, 255), "CHEATS");
	ImGui::PopFont();
}
void spacing()
{
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::SameLine(8);
}
bool Configuration::Aimbot::aimbotEnabled;
bool Configuration::Aimbot::autoFire;
bool Configuration::Aimbot::silentAim;
bool Configuration::Aimbot::noRecoil;
int Configuration::Aimbot::aimBone;
bool Configuration::Aimbot::autoAim;

bool Configuration::Visuals::Player::Box;
bool Configuration::Visuals::Player::Name;
bool Configuration::Visuals::Player::Health;

bool Configuration::Others::Interpolation;
bool Configuration::Others::Animations;
bool Configuration::Others::asus;
bool Configuration::Misc::Movement::autoBunnyhop;
bool Configuration::Misc::Movement::autoStrafe;

ImFont* Font;
int currentTab = 0;

static int tab;


void doTabs()
{
	ImGui::PushFont(InterMedium);

	{
		
		if (ImGui::Button("Aimbot", ImVec2(60, 30)))
			currentTab = 0;

		if (ImGui::Button("Visuals", ImVec2(60, 30)))
			currentTab = 1;

		if (ImGui::Button("Misc", ImVec2(60, 30)))
			currentTab = 2;
		ImGui::PopFont();
	}

}

void cMenu() {
	ImGui::SetNextWindowSize(ImVec2(450, 350));
	ImGui::PushFont(InterMedium);
	if (!b_MenuEnable)
		return;

	if (ImGui::Begin("   css v34 Segregation Imgui by deathcore2013", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders  | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar)) {
		doTabs();
		
		ImGui::SetCursorPos(ImVec2(75, 26));

		if (ImGui::BeginChild("װנטלום ע‏פÿך לום‏ xD", ImVec2(360, 310))) 
		{
			switch (currentTab) {
			case 0: {
				const char* iSpread[] =
				{

					" 345345",
					" hgfhhgdh",
					" 34654y4hg"
				};
				const char* iSpread2[] =
				{

					" test",
					" sgvdsttrt4",
					" geg454"
				};
				
				
				spacing();
				ImGui::Checkbox("Interpolation", &Configuration::Others::Interpolation);
				spacing();
				ImGui::Checkbox("Animations", &Configuration::Others::Animations);
				spacing();
				ImGui::Checkbox("5454535345", (bool*)&Interface_Commentator.Floating_Point);
				spacing();
				ImGui::Checkbox("Enable Fakelag", (bool*)&Interface_Alternative.Integer);
				spacing();
				ImGui::SliderInt("min", &Interface_Minimum_Choked_Commands.Integer, 0, 22, "%.0f");
				spacing();
				ImGui::SliderInt("max", &Interface_Maximum_Choked_Commands.Integer, 0, 22, "%.0f");
				//ImGui::Checkbox("564565", (bool*)&Waiting_For_Update_Animaton);
				//ImGui::SliderInt("Interface_Bruteforce_Tolerance", &Interface_Bruteforce_Tolerance.Integer, 0, 22, "%.0f");
				//ImGui::SliderInt("bruteforce angles", &Interface_Bruteforce_Angles.Integer, 0, 22, "%.0f");
				//ImGui::SliderInt("alternative", &Interface_Alternative.Integer, 0, 22, "%.0f");
				ImGui::SliderFloat("angle x", &Interface_Angle_X.Floating_Point, 0, 180, "%.0f");
				ImGui::SliderFloat("Interface_First_Choked_Angle_Y", &Interface_First_Choked_Angle_Y.Floating_Point, 0, 180, "%.0f");
				//ImGui::SliderFloat("Interface_Second_Choked_Angle_Y", &Interface_Second_Choked_Angle_Y.Floating_Point, 0, 180, "%.0f");
				//ImGui::SliderFloat("Interface_Angle_Y", &Interface_Angle_Y.Floating_Point, 0, 360, "%.0f");
				//ImGui::SliderFloat("Interface_Uber_Alles_Scale", &Interface_Uber_Alles_Scale.Floating_Point, 0, 360, "%.0f");
				//ImGui::SliderFloat("Interface_Uber_Alles_Speed", &Interface_Uber_Alles_Speed.Floating_Point, 0, 360, "%.0f");
				
				
			} break;
			case 1: {
				
				ImGui::Checkbox("ESP", &ESP);
				ImGui::Checkbox("Tracers", &Tracers);
				ImGui::Checkbox("Health", &HealthESP);
				ImGui::Checkbox("Chams", &Chams);

			}break;
			case 2: {
				
				ImGui::Checkbox("Auto Bunnyhop", &Configuration::Misc::Movement::autoBunnyhop);


			}break;
			}
			ImGui::PopFont();
		}ImGui::EndChild();

	}ImGui::End();
}
HRESULT STDMETHODCALLTYPE hkEndScene(IDirect3DDevice9* vDevice)
{


	if (!initImgui)
	{

		ImGui::CreateContext();
		ImGui_ImplDX9_Init(hWindow, vDevice);


		ImFontConfig font_config;
		font_config.OversampleH = 1; //or 2 is the same
		font_config.OversampleV = 1;
		font_config.PixelSnapH = 1;

		static const ImWchar ranges[] =
		{
			0x0020, 0x00FF, // Basic Latin + Latin Supplement
			0x0400, 0x044F, // Cyrillic
			0,
		};
		ImGuiIO& io = ImGui::GetIO();
		ImFontConfig icons_config;
		IconFont = io.Fonts->AddFontFromMemoryTTF(Icons, sizeof(Icons), 22, NULL, io.Fonts->GetGlyphRangesCyrillic());

		InterMedium = io.Fonts->AddFontFromMemoryTTF(Intermedium, sizeof(Intermedium), 17, NULL, io.Fonts->GetGlyphRangesCyrillic());

		ImGuiStyle& style = ImGui::GetStyle();


		//style.FramePadding = ImVec2(2, 2);
		style.FrameRounding = 0.0f;
		//style.ItemInnerSpacing = ImVec2(10, 10);
		style.TouchExtraPadding = ImVec2(10, 10);
		style.WindowBorderSize = 5.0f;


		style.WindowPadding = ImVec2(10, 10);
		style.WindowRounding = 0.0f;
		style.FrameBorderSize = 1.0f;
		style.ItemSpacing = ImVec2(5, 5);
		style.IndentSpacing = 0.0f;
		style.ScrollbarSize = 0.0f;
		style.ScrollbarRounding = 0.0f;
		style.GrabMinSize = 5.0f;
		style.GrabRounding = 0.0f;

		style.Alpha = 1.0f;

		style.ItemInnerSpacing = ImVec2(6, 4);
		style.FramePadding = ImVec2(1, 2);




		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.895f); //fon
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);//fon2
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0, 0, 0, 255);
		style.Colors[ImGuiCol_Border] = ImVec4(0.978f, 0.967f, 0.978f, 0.500f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(255, 255, 255, 255);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.994f, 0.000f, 0.857f, 0.540f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.160f, 0.160f, 0.160f, 0.315f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.40f, 0.46f, 0.75f, 0.45f);
		style.Colors[ImGuiWindowFlags_ShowBorders] = ImVec4(0.099f, 0.315f, 0.000f, 0.000f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.917f, 0.000f, 0.578f, 1.000f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.801f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(255, 0, 255, 1);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.139f, 0.508f, 0.000f, 1.000f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.139f, 0.508f, 0.000f, 1.000f);

		initImgui = true;
	}	
	if (GetAsyncKeyState(VK_INSERT) & 1) {
		b_MenuEnable = !b_MenuEnable;
	}
	ImGui::GetIO().MouseDrawCursor = b_MenuEnable;
	ImGui_ImplDX9_NewFrame();
	water();
	if (b_MenuEnable)
	{

		cMenu();
	}
	ImGui::Render();
	return oEndScene(vDevice);
}
LRESULT STDMETHODCALLTYPE hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		PressedKeys[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		PressedKeys[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		PressedKeys[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		PressedKeys[VK_RBUTTON] = false;
		break;
	case WM_MBUTTONDOWN:
		PressedKeys[VK_MBUTTON] = true;
		break;
	case WM_MBUTTONUP:
		PressedKeys[VK_MBUTTON] = false;
		break;
	case WM_XBUTTONDOWN:
	{
		UINT button = GET_XBUTTON_WPARAM(wParam);
		if (button == XBUTTON1)
		{
			PressedKeys[VK_XBUTTON1] = true;
		}
		else if (button == XBUTTON2)
		{
			PressedKeys[VK_XBUTTON2] = true;
		}
		break;
	}
	case WM_XBUTTONUP:
	{
		UINT button = GET_XBUTTON_WPARAM(wParam);
		if (button == XBUTTON1)
		{
			PressedKeys[VK_XBUTTON1] = false;
		}
		else if (button == XBUTTON2)
		{
			PressedKeys[VK_XBUTTON2] = false;
		}
		break;
	}
	case WM_KEYDOWN:
		PressedKeys[wParam] = true;
		break;
	case WM_KEYUP:
		PressedKeys[wParam] = false;
		break;
	default: break;
	}
	static bool is_down = false;
	static bool is_clicked = false;
	static bool check_closed = false;

	if (GUI_KEY_DOWN(VK_END))
	{
		is_clicked = false;
		is_down = true;
	}
	else if (!GUI_KEY_DOWN(VK_END) && is_down)
	{
		is_clicked = true;
		is_down = false;
	}
	else
	{
		is_clicked = false;
		is_down = false;
	}

	if (!b_MenuEnable && !is_clicked && check_closed)
	{
		check_closed = false;
	}

	if (is_clicked)
	{
		b_MenuEnable = !b_MenuEnable;

		if (!check_closed)
			check_closed = true;
	}

	if (b_MenuEnable && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(pOldWindowProc, hWnd, uMsg, wParam, lParam);
}
__int32 __stdcall DllMain(void* This_Module_Location, unsigned __int32 Call_Reason, void* Reserved)
{
	if (Call_Reason == DLL_PROCESS_DETACH)
	{
		__fastfail(EXIT_SUCCESS);
	}
	else
	{
		if (Call_Reason == DLL_PROCESS_ATTACH)
		{
			Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)LoadLibraryW(L"vaudio_speex.dll") + 9360), 1, 195);
			hWindow = FindWindowA("Valve001", nullptr);
			pOldWindowProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hWindow, GWLP_WNDPROC, LONG_PTR(hkWndProc)));
			unsigned __int8 kinkston[6] = { 0xb0,0x00,0xc2,0x04,0x00 };
			Byte_Manager::Copy_Bytes(1, (void*)537964272, sizeof(kinkston), kinkston);
			AllocConsole();
			initializeminhook();
			SetConsoleTitleW(L"Segregation");

			_wfreopen(L"CONOUT$", L"w", stdout);

			SetConsoleOutputCP(65001);

			HANDLE Standard_Output_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

			CONSOLE_FONT_INFOEX Console_Font_Information;

			Console_Font_Information.cbSize = sizeof(CONSOLE_FONT_INFOEX);

			Console_Font_Information.nFont = 0;

			Console_Font_Information.dwFontSize.X = 0;

			Console_Font_Information.dwFontSize.Y = 12;

			Console_Font_Information.FontFamily = FF_DONTCARE;

			Console_Font_Information.FontWeight = FW_NORMAL;

			wcscpy(Console_Font_Information.FaceName, L"Terminal");

			SetCurrentConsoleFontEx(Standard_Output_Handle, 0, &Console_Font_Information);

			CONSOLE_CURSOR_INFO Console_Cursor_Information;

			Console_Cursor_Information.bVisible = 0;

			Console_Cursor_Information.dwSize = sizeof(Console_Cursor_Information);

			SetConsoleTextAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED);

			SetConsoleCursorInfo(Standard_Output_Handle, &Console_Cursor_Information);

			CONSOLE_SCREEN_BUFFER_INFO Console_Screen_Buffer_Information;

			GetConsoleScreenBufferInfo(Standard_Output_Handle, &Console_Screen_Buffer_Information);

			COORD Top_Left =
			{
				0,

				0
			};

			DWORD Characters_Written_Count;

			FillConsoleOutputAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED, Console_Screen_Buffer_Information.dwSize.X * Console_Screen_Buffer_Information.dwSize.Y, Top_Left, &Characters_Written_Count);

			_putws(L"[ + ] Delimit Interface");
			{
				unsigned __int8 Cheat_Flag_Bytes[4] =
				{
					254,

					65,

					44,

					195
				};

				Byte_Manager::Copy_Bytes(1, (void*)538391351, sizeof(Cheat_Flag_Bytes), Cheat_Flag_Bytes);

				*(__int8*)542242676 = 1;

				Byte_Manager::Set_Bytes(1, (void*)537349277, 1, 235);
			}

			_putws(L"[ + ] Extend Interface");
			{
				Implement_Extended_Interface();
			}
			
			_putws(L"[ + ] Events");
			{
				Redirection_Manager::Redirect_Function(Original_Post_Entity_Packet_Received_Caller_Location, 0, (void*)605203088, 1, (void*)Redirected_Post_Entity_Packet_Received);

				Byte_Manager::Set_Bytes(1, (void*)537149578, 1, 235);

				void* Event_Listener = (void*)malloc(sizeof(void*));

				void* Event_Listener_Table = malloc(sizeof(void*) * 2);

				*(void**)((unsigned __int32)Event_Listener_Table + 4) = (void*)Event_Processor;

				*(void**)Event_Listener = Event_Listener_Table;

				using Add_Listener_Type = __int8(__thiscall*)(void* Event_Manager, void* Listener, char* Event, void* Unknown_Parameter);

				Add_Listener_Type(537586416)((void*)540812808, Event_Listener, (char*)"player_hurt", nullptr);

				Add_Listener_Type(537586416)((void*)540812808, Event_Listener, (char*)"player_death", nullptr);

				Add_Listener_Type(537586416)((void*)540812808, Event_Listener, (char*)"bullet_impact", nullptr);

				Redirection_Manager::Redirect_Function(Original_Write_Events_Caller_Location, 2, (void*)537582208, 1, (void*)Redirected_Write_Events);

				//Redirection_Manager::Redirect_Function(Original_Shutdown_Caller_Location, 0, (void*)537926128, 1, (void*)Redirected_Shutdown); // פנטלום ע‏פÿך xD
			}
		
			if (Configuration::Others::Interpolation) // 
			_putws(L"[ + ] Interpolation");
			{
				Redirection_Manager::Redirect_Function(Original_Interpolate_Caller_Location, 0, (void*)604201536, 1, (void*)Redirected_Interpolate);
			}
			if (Configuration::Others::Animations)
			_putws(L"[ + ] Animations");
			{
				Redirection_Manager::Redirect_Function(Original_Update_Animation_Caller_Location, 4, (void*)605800256, 1, (void*)Redirected_Update_Animation);

				Byte_Manager::Set_Bytes(1, (void*)605800287, 1, 235);

				Byte_Manager::Set_Bytes(1, (void*)604287917, 2, 144);

				Redirection_Manager::Redirect_Function(Original_Compute_Torso_Rotation_Caller_Location, 1, (void*)604022496, 1, (void*)Redirected_Compute_Torso_Rotation);

				unsigned __int8 Maintain_Sequence_Transitions_Bytes[3] =
				{
					194,

					24,

					0
				};

				Byte_Manager::Copy_Bytes(1, (void*)604206416, sizeof(Maintain_Sequence_Transitions_Bytes), Maintain_Sequence_Transitions_Bytes);
			}

			_putws(L"[ + ] Prediction");
			{
				Byte_Manager::Set_Bytes(1, (void*)537158868, 5, 144);

				Byte_Manager::Set_Bytes(1, (void*)605209595, 1, 235);

				Redirection_Manager::Redirect_Function(Original_Compute_First_Command_To_Execute_Caller_Location, 2, (void*)605206464, 1, (void*)Redirected_Compute_First_Command_To_Execute);

				Redirection_Manager::Redirect_Function(Original_Store_Prediction_Results_Caller_Location, 0, (void*)605209056, 1, (void*)Redirected_Store_Prediction_Results);

				Redirection_Manager::Redirect_Function(Original_Setup_Move_Caller_Location, 0, (void*)605206752, 1, (void*)Redirected_Setup_Move);

				Redirection_Manager::Redirect_Function(1, (void*)605024544, (void*)Redirected_Fall_Damage);

				Redirection_Manager::Redirect_Function(Original_Finish_Move_Caller_Location, 1, (void*)605207376, 1, (void*)Redirected_Finish_Move);

				Redirection_Manager::Redirect_Function(Original_Item_Post_Frame_Caller_Location, 0, (void*)604081184, 1, (void*)Redirected_Item_Post_Frame);

				Byte_Manager::Set_Bytes(1, (void*)605954536, 9, 144);

				Redirection_Manager::Redirect_Function(Original_Weapon_Spread_Caller_Location, 1, (void*)605949248, 1, (void*)Redirected_Weapon_Spread);
			}

			_putws(L"[ + ] Input");
			{
				Byte_Manager::Set_Bytes(1, (void*)604993824, 3, 144);

				Redirection_Manager::Redirect_Function(Original_Copy_User_Command_Caller_Location, 0, (void*)604850464, 1, (void*)Redirected_Copy_User_Command);
			}

			_putws(L"[ + ] Network");
			{
				Redirection_Manager::Redirect_Function(1, (void*)537142224, (void*)Redirected_Send_Move);
			}

			_putws(L"[ + ] View Effects");
			{
				Byte_Manager::Set_Bytes(1, (void*)604082898, 34, 144);
			}

			
			
			_putws(L"[ + ] Materials");
			{
				//if (Configuration::Others::asus)
				Redirection_Manager::Redirect_Function(Original_Precache_Caller_Location, 5, (void*)((unsigned __int32)GetModuleHandleW(L"MaterialSystem.dll") + 21984), 1, (void*)Redirected_Precache);

				Byte_Manager::Set_Bytes(1, (void*)605462216, 2, 144);

				Byte_Manager::Set_Bytes(1, (void*)605515289, 1, 235);

				unsigned __int8 Smoke_Bytes[3] =
				{
					194,

					8,

					0
				};

				Byte_Manager::Copy_Bytes(1, (void*)605610608, sizeof(Smoke_Bytes), Smoke_Bytes);

				Byte_Manager::Set_Bytes(1, (void*)605809168, 1, 195);
			}
		}
	}

	return 1;
}