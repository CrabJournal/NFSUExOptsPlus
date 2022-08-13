#pragma once

#include "stdio.h"
#include <windows.h>

// Global variables
// make 'em char* to not brake pointer arithmetic
#define _TheGameFlowManager (*(char**)0x403BC7)
#define _pgFEPackageManager 0x413C6D
#define _WindowedMode (*(char**)0x4086C5)
#define _hWnd (*(char**)0x4056C5)
#define _IsLostFocus (*(char**)0x41112D)
#define _ResX 0x701034
#define _ResY 0x701038
#define _UnlockEverythingThatCanBeLocked (*(char**)0x4AA9DF)
#define _FEDatabase (*(char**)0x42205F)
#define _BuildRegion (*(char**)0x40119D)
#define _ChyronSkin (*(char**)0x4D46BC)
#define _Tweak_GameSpeed 0x6B7994
#define _SkipMovies 0x73496C
#define _IsSoundEnabled 0x6F1DD8
#define _IsAudioStreamingEnabled 0x6F1DDC
#define _pPreRaceScreenManager (*(char**)0x49599C)
#define _pRaceCoordinator (*(char**)0x4057C1)
#define _bIsDriftRace (*(char**)0x41F608)
#define _bIsDragRace (*(char**)0x421A58)
#define _unk_78A344 (*(char**)0x422809)
#define _NumberOfPlayers (*(char**)0x422842)
#define _NumberOfOpponents (*(char**)0x42E9D0)
#define _PlayersByIndex (*(char**)0x408213)
#define _PlayersByNumber (*(char**)0x424F13)
#define _pCurrentRace (*(char**)0x4057DC)
#define _Camera_StopUpdating (*(char**)0x40A48D)
#define _pCurrentWorld (*(char**)0x40A2DF)

enum InputMode :DWORD {
	IM_menu = 1,
	IM_game = 2,
	//...
	IM_unk_mb_last = 8
};