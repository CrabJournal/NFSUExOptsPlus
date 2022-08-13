#pragma once
#include "stdafx.h"
#include <d3d9.h>
#include "GameFrontEnd.h"
#include "UG1_UG2_common.h"

// TODO: 
// 1) find weals rotaion, gas, break, nos, gear and e-brake
// 2) traffic cars
// 3) find end of race (finish, crash, restart ect)
// 4) explore race starting init
// Next V
// 5) Replays in menu
// 6) Input in menu...

// DONE:
// 1, 2, 3, 4, 5

/* need: 
	1)
	(Options _fastcall cFrontendDatabase::GetOptions(CurrentRaceMode) )
	CurrentRaceMode, DefaultSeed, SkipFETrackNumber (Options +  0x8), NumberOfOpponents (Options + 0x0 = number of racing cars), isBackwardRaceTrack(Options + 0xC)
	LapsNumberToSet (Options +  0x10), (Options +  0x14) OponentsSkill, (Options +  0x18) Traffic, (Options +  0x1F) Catch Up

	2)
	0x6F9E4C

*/

struct mbRacerInfo;
struct Race;

struct CarCollisionBody;

struct RaceCoordinator;
struct World;

struct unkObj2;
struct unkObj3;
struct unkObj4;

enum RCState;
enum CarCameraTypes;


// size 0x18, no vtlb
struct eModel{
	void *unk1;
	void *unk2;
	DWORD mbID;
	void* unk3;
	void* unk4;
	DWORD unk5;								// +x014 / =0x34
};


// size 0x568
struct Race {
	DWORD unk0x0;				// +0x0 =4
	// +0xC float
	// +0x18 int
	
	// +0x30 RacerInfo array?? / Player Car*
	mbRacerInfo RacersInfo[4];	// +0x30, total size 0x4F0
	// +0x520 0x48 bytes left
	// +0x530 - int laps number
	// +0x53F Byte
	// +0x540 float unk0x540[3 or 4];
};

struct CameraSettings {
	CarCameraTypes type;
	float lag;
	float height;
	float lat_offset;
};


// mb Hud
// size 0x210
struct unkObj4 {
	void* unk0x0;			// allocated in memblock size 0x19000
	void* unk0x4;			// allocated in same mem block
	char* str;				// HUD_SingleRace.fng

};

// size 1) 0x6C - base (for player), 2) AI Driver size 0x500 vtbl 0x6C89F0
struct unkObj2 {
	void* Vtable;			// 2) 0x6C89F0 ()
	Car* car;				// +0x4
	unkObj3* unkob3;		// +0x8 obj size 0x250 from 0x46218B mb Driver
	// +0x3F8 - ptr slot
	// +0x428 - obj (not a pointer)
	// +0x4D8 - DWORD
	
};

// size 0xB0
struct RaceCoordinator {
	RCState state;			
	void* RCQueuedMessage;	// +0x4
	void* unk_ptr0x8;		// +0x8, ptr to itself
	void* unk_ptr0xC;		// +0xC, same value as unk_ptr0x8
	// int num of ?
};

// size 0x17A0 from 0x421FA4
struct World {
	void *mbNext;				// +0x0 / ptr to itself or to Car
	void *mbPrev;				// +0x4 / ptr to itself or to Car

	void *optr1;				// +0x8 / next node in list mb / ptr to itself
	void *optr1_2;				// +0xC / prev node in list mb / same ptr as prev field

	void *optr2;				// +0x10 / ptr to itself
	void *optr2_2;				// +0x14 / same ptr as prev field

	int CarsNumber;				// + 0x18

	int mbPlayersNumber;		// +0x1C
	int mbRacingCarsNumber;		// +0x20
	int mbRacingCarsNumber2;	// +0x24

	Car* Cars[16];				// + 0x28
	// +0x280 +0x280 Player pos
	// +0x2C0 vector3 ?
	// +0x2E0
	// +0x2F0 some obj ptr / size 0x1A0

	// +0x300 obj?
	// +0x940 same

	// +0x1410 0bj2?
	// +0x15D0 same
	// ...
};

// size 
struct TrackInfo{
	WORD SkipFENumber;
	
};

enum CameraMoverTypes {
	// data from Player::ChangeCameraMover
	CamMovT_Drive = 1,	// size 0x3A0, vtbl 0x6C7FC8
	CamMovT_2 = 2,		// size  0x4C, vtbl 0x6C7D80
	CamMovT_Base = 3,	// size  0x2C, vtbl 0x6C7C50, like in CameraMover
	CamMovT_4 = 4,		// size  0xD0, vtbl 0x6C8018
	CamMovT_Bumper = 5,	// size 0x45C, vtbl 0x6C8018
	CamMovT_6 = 6,		// size  0x30, vtbl 0x6C7E10, mb CarCameraMover

	CamMovT_9 = 9,		// size 0x19C, vtbl 0x6C7EF0

	CamMovT_11 = 11,	// size 0x1A0, vtbl 0x6C7C98, Garage Camera mover

	CamMovT_13 = 13,	// size 0x368, vtbl 0x6C7B98, in prop 12
	CamMovT_14 = 14,	// size 0x450, vtbl 0x6C7B50, also 12

	CamMovT_15 = 15,	// size 0x470, vtbl 0x6C7D28, mb 7
	CamMovT_16 = 16,	// size 0x470, vtbl 0x6C7D28

	CamMovT_17 = 17,	// size  0x54, vtbl 0x6C7E58, mbRaceCameraMover
	CamMovT_18 = 18,	// size  0x2C, vtbl 0x6C7F80
	CamMovT_19 = 19,	// size  0x38, vtbl 0x6C7EA8
	CamMovT_20 = 20,	// size  0x58, vtbl 0x6C7DC8
	CamMovT_21 = 21,	// size  0xA0, vtbl 0x6C7CE0
	CamMovT_22 = 22,	// size 0x310, vtbl 0x6C7C08, mb before start
};

// size 0x2C, vtbl 0x6C7C50
struct CameraMover {
	virtual CameraMover* __thiscall Destroy(bool free);		// 0:  +0x0
	virtual void __thiscall Update();						// 1:  +0x4
	virtual void __thiscall Render(DWORD);					// 2:  +0x8
	virtual void __thiscall AddJoyHandlers();				// 3:  +0xC
	virtual void __thiscall RemoveJoyHandlers();			// 4:  +0x10
	virtual void __thiscall SetLookBack(bool);				// 5:  +0x14
	virtual void __thiscall SetLookbackSpeed(DWORD);		// 6:  +0x18

	virtual void __thiscall SetDisableLag(bool);			// 7:  +0x1C
	virtual void __thiscall SetPovType(int);				// 8:  +0x20
	virtual BOOL __thiscall OutsidePOV();					// 9:  +0x24
	virtual BYTE __thiscall BirdsEyePOV();					// 10: +0x28
	// Ug2 - GetPovType
	virtual float __thiscall MinDistToWall();				// 11: +0x2C

	virtual DWORD __thiscall GetLookbackAngle();			// 12: +0x30
	virtual void __thiscall ResetState();					// 13: +0x34
	virtual void __thiscall Enable();						// 14: +0x38
	virtual void __thiscall Disable();						// 15: +0x3C
	virtual Car* __thiscall GetCarToFollow();				// 16: +0x40
	virtual void* __thiscall GetTarget();					// 17: +0x44

	// void* Vtbl					// +0x0 
	void* next_mb_baseobj;			// +0x4
	void* prev;						// +0x8
	CameraMoverTypes type;			// +0xC
	DWORD unk0x10;					// +0x10
	DWORD isEnabled;				// +0x14

	void* unk0x18;					// +0x18 in .data =0x7404C0,
	void* unk0x1C;					// +0x1C in .data =0x78D270,
	Player* player;					// +0x20
	DWORD unk0x24[2];				// +0x24 =0
};

struct PlayerCameraMover : CameraMover {
	Car* car_to_follow;				// +0x2C
};

enum CarCameraTypes {
	CarCameraType_FAR = 0,
	CarCameraType_CLOSE = 1,
	CarCameraType_BUMPER = 2,
	CarCameraType_DRIVER = 3,
	CarCameraType_DRIFT = 4
};

// size 0x54, 0x6C7E58
struct mbRaceCameraMover : PlayerCameraMover {
	void* unkobj0x30;				// +0x30 size 0x30, no Vtbl, from 0x48B077
	void* unkobjs0x34;				// +0x34 size 0x90, no Vtbl, from 0x48B0B8, array of 3
	void* unkobjs0x38;				// +0x38 size 0x90, no Vtbl, from 0x48B0E8
	void* unkobjs0x3C;				// +0x3C same
	CarCameraTypes camtype;			// +0x40
	BYTE unk0x44[4];				// +0x44 
	DWORD unk0x48;					// +0x48 =BAADF00D
	DWORD unk0x4C;					// +0x4C Timer?
	void* unkobj0x50;				// +0x50 size 0x30, Vtbl 0x6C7D7, from 0x48B141
};

// no vtlb, size unknown
struct CarPartsDB {
	CarPartsDB** ds;				// +0x0 / ptr to CarPartsDB's ptr in .data
	CarPartsDB** ds2;				// +0x4 / same
	int unk0x8;						// +0x8
	void* mbDB;						// +0xC / size of a part must be 0x30
	int mbPartsNumber;				// +0x10
};

struct TheGarageManager {
	void *obj1;						// +0x0 obj size 0xC from 0x50432A, "MU_QuickRaceCarSelect.fng"
	void *obj1_2;					// +0x4
	void *FECarConfig;				// +0x8
	// 
};


// enums

enum InputCodesBitsOffsets {
	Gas = 1,
	Break_Rev = 2,
	SteeringLeft = 3,
	SteeringRighgt = 4,
	E_brake = 5,
	NOS = 6,
	ShiftUp = 7,
	ShiftDown = 8,
	SeeBehind = 9,
	SwitchCamera = 10,
	Esc = 12
};

enum RCState {
	RCS_End = 0,
	RCS_Pre_race = 2,
	RCS_Pre_race2 = 3,
	RCS_Race = 4,
	RCS_Pause = 7,
	RCS_Finish = 8
};

enum mbRCAction {
	RCA_Nothing = 0,
	RCA_Continie = 1,
	RCA_Restart = 2,
	RCA_Leave = 3
};

enum RCMessage {
	RCM_mbNewState = 1,
	RCM_mbOldState = 2,
	RCM_idk = 3,
	RCM_InitialStart = 4,
	RCM_mbPause = 5,
	RCM_mbAction = 6,
	RCM_RestartPostRace = 8,
	RCM_LeaveRacePostRace = 10
};

enum GameFlowState {
	GAMEFLOW_STATE_NONE = 0,
	GAMEFLOW_STATE_LOADING_FRONTEND,
	GAMEFLOW_STATE_UNLOADING_FRONTEND,
	GAMEFLOW_STATE_IN_FRONTEND,
	GAMEFLOW_STATE_LOADING_TRACK_COMMON,
	GAMEFLOW_STATE_LOADING_TRACK_SPECIFIC,
	GAMEFLOW_STATE_RACING,
	GAMEFLOW_STATE_UNLOADING_TRACK_SPECIFIC,
	GAMEFLOW_STATE_UNLOADING_TRACK_COMMON,
	GAMEFLOW_STATE_EXIT_DEMO_DISC
};

const float AngleConvert = 10430.378;

// VAs

// .data
DWORD* const Seed = (DWORD*)0x6F227C;
BOOL* const CameraFollowDefaultCar = (BOOL*)0x6FBF14;
int* const CameraFollowThisCarInstead = (int*)0x6FBF18; // by number of driver
float* const mbRPM_BlueZoneWides = (float*)0x6FFF60;

D3DPRESENT_PARAMETERS* const pPresentationParameters = (D3DPRESENT_PARAMETERS*)0x71A96C;

cFEng** const cFEng_pInstanse = (cFEng**)0x73578C;

// here starts US - EU difference, use defines instead
IDirect3D9** const _ppD3D9 = (IDirect3D9**)0x736368;
IDirect3DDevice9** const _ppD3D9Device = (IDirect3DDevice9**)0x73636C;
IDirect3DDevice9** const _ppD3D9Device_EU = (IDirect3DDevice9**)0x736364;
HWND* const _hWnd = (HWND*)0x736380;
bool* const _pIsLostFocus = (bool*)0x7363B6;

float* const _WorldTimeElapsed = (float*)0x73457C;
int* const _TrackNum = (int*)0x73616C; // total
DWORD* const _pPlayersByIndex = (DWORD*)0x7361BC;
World** const _pCurrentWorld = (World**)0x7361F8;
void** const _WorldTimer = (void**)0x73AD34;
float* const _RealTimeElapsed = (float*)0x73AD38;
void* const _FEDatabase = (void*)0x748F70;
int* const _UndergroundRaceDifficulty = (int*)0x75F240;
int* const _CurrentRaceMode = (int*)0x777CC8;
void* const _CollisionList = (void*)0x779C70;
GameFlowState* const _GameFlowState_EU = (GameFlowState*)0x77A910;
GameFlowState* const _GameFlowState = (GameFlowState*)0x77A920;
Race** const _pCurrentRace = (Race**)0x77B240;	// 0, not recommend to use / or not???
int* const _SkipFETrackNumber = (int*)0x78A2F0;
int* const _NumberOfOpponents = (int*)0x78A324;
DriverInfo** const _DriversInfo = (DriverInfo**)0x78A418;
int* const _NumberOfCars = (int*)0x78A41C;
// CurrentRaceMode, TrackInfo::TrackInfoTable, DefaultSeed


// .rdata
float* const Tweak_GameSpeed = (float*)0x6B7994;
DWORD* const pVirtualPhysicsFunc = (DWORD*)0x6B9670;
const float* const fNFS_one = (float*)0x6CC7BC;


// .text

// ptrs in .text
// whatever EU version or US
IDirect3D9*** const pppD3D9 = (IDirect3D9***)0x40883D;
IDirect3DDevice9*** const pppD3D9Device = (IDirect3DDevice9***)0x401522;
HWND** const phWnd = (HWND**)0x4056C5;
bool** const ppIsLostFocus = (bool**)0x41112D;
float** const pWorldTimeElapsed = (float**)0x41F802;
int** const pTrackNum = (int**)0x421F08;
DWORD** const ppPlayersByIndex = (DWORD**)0x408213;
World*** const ppCurrentWorld = (World***)0x40A2DF;
void*** const pWorldTimer = (void***)0x40F5A8;
float** const pRealTimeElapsed = (float**)0x40B256;
void** const pFEDatabase = (void**)0x42205F;
int** const pUndergroundRaceDifficulty = (int**)0x49EE00;
int** const pCurrentRaceMode = (int**)0x43B0BB;
void** const pCollisionList = (void**)00420311;
GameFlowState** const pGameFlowState_ = (GameFlowState**)0x403BC7;
Race*** const ppCurrentRace = (Race***)0x4212F6;
int** const pSkipFETrackNumber = (int**)0x421F33;
int** const pNumberOfOpponents = (int**)0x42E9D0;
DriverInfo*** const pDriversInfo = (DriverInfo***)0x422AAD;
int** const pNumberOfCars = (int**)0x422AA2;

#define ppD3D9 (*pppD3D9)
#define ppD3D9Device (*pppD3D9Device)
#define hWnd (*phWnd)
#define pIsLostFocus (*ppIsLostFocus)
#define WorldTimeElapsed (*pWorldTimeElapsed) /* EU = US, so can be _WorldTimeElapsed */
#define TrackNum (*pTrackNum)
#define pPlayersByIndex (*ppPlayersByIndex)
#define pCurrentWorld (*ppCurrentWorld)
#define WorldTimer (*pWorldTimer)
#define RealTimeElapsed (*pRealTimeElapsed)
#define FEDatabase (*pFEDatabase)
#define UndergroundRaceDifficulty (*pUndergroundRaceDifficulty)
#define CurrentRaceMode (*pCurrentRaceMode)
#define CollisionList (*pCollisionList)
#define GameFlowState_ (*pGameFlowState_)
#define pCurrentRace (*ppCurrentRace)
#define SkipFETrackNumber (*pSkipFETrackNumber)
#define NumberOfOpponents (*pNumberOfOpponents)
#define DriversInfo (*pDriversInfo)
#define NumberOfCars (*pNumberOfCars)



// after call opcode
void* const call_World_DoTimestep = (void*)0x44796A;
void* const call_RaceStarter_StartRace = (void*)0x4B80EE;
void* const call_InitFERaceEvent = (void*)0x4C5E38;
void* const call_InitFERaceEvent2 = (void*)0x4B383F;
void* const call_RCSendMessage_InRCChangeState = (void*)0x421AF5;
void* const call_FEngUpdate = (void*)0x4479A6;
void* const call_nh_malloc = (void*)0x671225;

void* const call_IDirect3DDevice9_EndScene = (void*)0x40A6CF;
void* const before_call_IDirect3DDevice9_Reset = (void*)0x40A52F;



// = = = = = = = = =
#define __usercall
#define __userpurge
typedef void(* void_void)();
const void_void const RaceStarter_StartRace = (void_void)0x4B5C00;
const void_void const FEngUpdate = (void_void)0x4F6170;

typedef RaceOptions*(_fastcall* T_cFrontendDatabase_GetOptions)(void* _FEDatabase_, int RaceType);
const T_cFrontendDatabase_GetOptions const cFrontendDatabase_GetOptions = (T_cFrontendDatabase_GetOptions)0x4AB510;

typedef void(__stdcall* T_World_DoTimestep)(World* world, float timeElapsed);
const T_World_DoTimestep const World_DoTimestep = (T_World_DoTimestep)0x420B40;

typedef void(__userpurge* T_RCSendMessage)(RaceCoordinator* ESI_this, int RCMessage, int);
const T_RCSendMessage const RaceCoordinator_RCSendMessage = (T_RCSendMessage)0x421BC0;

typedef char*(_fastcall* T_SearchForString)(DWORD, unsigned int code);
const T_SearchForString const SearchForString = (T_SearchForString)0x59FB80;

typedef int(__usercall* T_sPrintf)(char* EAX_FEString, const char* format, ...);
const T_sPrintf const FEngPrintf = (T_sPrintf)0x4F68A0;

typedef void(__usercall* T_Car_SetMovementMode)(Car* ESI_this, CarMovmentMode ECX_MovementMode);
const T_Car_SetMovementMode const Car_SetMovementMode = (T_Car_SetMovementMode)0x426110;

typedef void(__userpurge* T_Car_UpdateState)(WORD AX_angle, Car* _this, float* Matrix4x4, vector3*, void* unk_obj);
const T_Car_UpdateState const Car_UpdateState = (T_Car_UpdateState)0x4273D0;

__usercall void* const CarState_CalcNos = (void*)0x465530; // (esi - this)
__usercall void* const FECarierManager_InitFERaceEvent = (void*)0x5A0CE0; // (esi - this, edi - CarierRaceNumber)
__usercall void* const RaceStarter_StartUndergroundModeRaceR = (void*)0x4B5DF0; // (ebx - FERaceEvent*)
// = = = = = = = = =


// CRT
typedef void*(_cdecl *T_nh_malloc)(size_t size, int flags);
typedef char*(_cdecl *T_str1)(char* str1, const char* str2);
const T_str1 const NFS_strcat = (T_str1)0x67E1E0;
const T_str1 const NFS_strcpy = (T_str1)0x67E1D0;
typedef void(_cdecl *T_memcpy)(void* dst, const void* src, size_t size);
const T_memcpy const NFS_memcpy = (T_memcpy)0x672630;
typedef void*(_cdecl *T_malloc)(size_t size);
const T_malloc const NFS_malloc = (T_malloc)0x67121A;
typedef void(_cdecl *T_free)(void* ptr);
const T_free const NFS_free = (T_free)0x671102;
typedef void*(_cdecl *T_realloc)(void* old_ptr, size_t new_size);
const T_realloc const NFS_realloc = (T_realloc)0x675C84;

typedef int(_cdecl *T_vsprintf)(char* buf, const char* format, va_list);
const T_vsprintf const NFS_vsprintf = (T_vsprintf)0x671077;


// SkipFETrackNumber, isBackwardRaceTrack, NumberOfCars
// 0x45C3C7 - exception, after calling