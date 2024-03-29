#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include "..\includes\IniReader.h"

bool once3, IsOnFocus, AutoDrive;
DWORD TheGameFlowManager;
HWND windowHandle;
int m_count = 0;
int t_count = 0;

void Thing()
{
	UpdateCameraMovers(); // Hijacked call from main loop

	_asm pushad;

	TheGameFlowManager = *(DWORD*)_TheGameFlowManager; // 3 = FE, 4&5 = Loading screen, 6 = Gameplay
	windowHandle = *(HWND*)_hWnd;
	IsOnFocus = !(*(bool*)_IsLostFocus);

	// Windowed Mode Related Fixes (Center and Resize)
	if (WindowedMode && windowHandle && !once3)
	{
		RECT o_cRect, n_cRect, n_wRect;
		GetClientRect(windowHandle, &o_cRect);
		
		DWORD wStyle = GetWindowLongPtr(windowHandle, GWL_STYLE);

		switch (WindowedMode)
		{
			case 1: wStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU); break;
			case 2: default: wStyle |= (WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_OVERLAPPEDWINDOW); break;
		}

		SetWindowLongPtr(windowHandle, GWL_STYLE, wStyle);

		// make window change style
		SetWindowPos(windowHandle, NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);

		//GetWindowRect(windowHandle, &n_wRect);
		GetClientRect(windowHandle, &n_cRect);
		int n_wWidth = *(int*)_ResX;
		int n_wHeight = *(int*)_ResY;
		int dif_wWidth = o_cRect.right - n_cRect.right;
		int dif_wHeight = o_cRect.bottom - n_cRect.bottom;
		int newWidth = n_wWidth + dif_wWidth;
		int newHeight = n_wHeight + dif_wHeight;

		HWND hDesktop = GetDesktopWindow();
		RECT desktop;
		GetWindowRect(hDesktop, &desktop);

		int newXPos = ((desktop.right - desktop.left) - newWidth) / 2;
		int newYPos = ((desktop.bottom - desktop.top) - newHeight) / 2;

		SetWindowPos(windowHandle, NULL, newXPos, newYPos, newWidth, newHeight, SWP_NOZORDER | SWP_NOACTIVATE);
		
		once3 = 1;
	}

	// Lock EA Trax Skin
	if (EATraxSkin != -1)
	{
		injector::WriteMemory<int>(_ChyronSkin, EATraxSkin, true);
	}

	// Any Track in Any Mode
	if ((GetAsyncKeyState(hotkeyAnyTrackInAnyMode) & 1)) 
	{
		CIniReader iniReader("NFSUExtraOptionsSettings.ini");
		AnyTrackInAnyMode = !AnyTrackInAnyMode;
		iniReader.WriteInteger("Menu", "AnyTrackInAnyRaceMode", AnyTrackInAnyMode);

		if (AnyTrackInAnyMode)
		{
			injector::MakeNOP(0x4BA16C, 2, true);
			injector::MakeNOP(0x4BA202, 2, true);
		}

		else
		{
			injector::WriteMemory<WORD>(0x4BA16C, 0x1D74, true);
			injector::WriteMemory<WORD>(0x4BA202, 0x2C74, true);
		}
	}

	// Drunk Driver
	if ((GetAsyncKeyState(hotkeyAutoDrive) & 1) && (TheGameFlowManager == 6) && IsOnFocus)
	{
		AutoDrive = !AutoDrive;

		DWORD PlayerThing = *(DWORD*)_PlayersByIndex;


		if (PlayerThing)
		{
			if (AutoDrive)
			{
				//SaveNode();
				Player_AutoPilotOn((DWORD*)PlayerThing);
			}
			else
			{
				MakeUserCall(Player_AutoPilotOff, 1, edi, PlayerThing);
				MakeUserCall(SetInputMode, 2, eax, *(void**)_PlayersByIndex, esp, InputMode::IM_game);
			}
		}
	}

	// Freeze Camera
	if ((GetAsyncKeyState(hotkeyFreezeCamera) & 1) && IsOnFocus)
	{
		static void** const pCubicCameraMover_Update = (void**)0x6C7E5C;
		static void* SwapAddr = (void*)0x40A880; // ret

		void* t = *pCubicCameraMover_Update;
		injector::WriteMemory<void*>(pCubicCameraMover_Update, SwapAddr, true);
		SwapAddr = t;
	}

	// Unlock All Things
	if ((GetAsyncKeyState(hotkeyUnlockAllThings) & 1))
	{
		UnlockAllThings = !UnlockAllThings;
		CIniReader iniReader("NFSUExtraOptionsSettings.ini");
		iniReader.WriteInteger("Gameplay", "UnlockAllThings", UnlockAllThings);

		injector::WriteMemory<unsigned char>(_UnlockEverythingThatCanBeLocked, UnlockAllThings, true);
	}
	
	if ((GetAsyncKeyState(hotkeyNoGravity) & 1) && (TheGameFlowManager == 6) && IsOnFocus)
	{
		NoGravity = !NoGravity;
		if (NoGravity)
		{
			injector::MakeNOP(0x46AB56, 3, true);
		}
		else
		{
			injector::WriteMemory<DWORD>(0x46AB56, 0x5F0450FF, true);
		}
	}

	if ((GetAsyncKeyState(hotkeyJump) & 1) && (TheGameFlowManager == 6) && IsOnFocus)
	{
		// *(*(*(*(*(float*****)_pCurrentWorld + 10) + 13) + 5) + 29) += JumpSpeed; // add to speed.z
		((float*****)_pCurrentWorld)[0][10][13][5][29] += JumpSpeed;
	}

	if (mpsInsteadOfMiPH)
	{
		char *MPH = GetString(0, 0x8569AB44);
		injector::WriteMemory<DWORD>(0x6CC9F0, 0x3f800000, true);
		injector::WriteMemory<DWORD>(0x6CC8B0, 0x41d80000, true);
		
		*(DWORD*)MPH = '\0s/m';
		mpsInsteadOfMiPH = false;
	}

	_asm popad;
}