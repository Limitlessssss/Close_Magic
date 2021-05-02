#include <iostream>
#include <Windows.h>
#include "xor.hpp"
#include "Structs.h"
#include "Offsets.h"
#include "Communication.h"
#include "SDK.h"
#include <random>
#include <chrono>
#include <TlHelp32.h>
#include "MiscFuns.h"
#include "WeaponFuncs.h"
#include "AimFuncs.h"






bool SilentWalk = true;

UINT64 TodCycle = 0;

bool fov = true;
bool mfound = false;

HWND window = NULL;

long long firstentry = 0;


bool LP_isValid = false;

struct HandleDisposer
{
	using pointer = HANDLE;

	void operator()(HANDLE handle) const
	{
		if (handle != NULL || handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(handle);
			std::cout << "Driver Loaded And Handle Closed" << std::endl;

		}
		else {
			std::cout << "Driver Not Loaded" << std::endl;
		}
	}
};

using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;
struct GlowMode
{
	int8_t GeneralGlowMode, BorderGlowMode, BorderSize, TransparentLevel;
};


std::uint32_t get_process_id(std::string_view process_name)
{
	PROCESSENTRY32 processentry;
	const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL));

	if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
		return NULL;

	processentry.dwSize = sizeof(MODULEENTRY32);

	while (Process32Next(snapshot_handle.get(), &processentry) == TRUE)
	{
		if (process_name.compare(processentry.szExeFile) == NULL)
		{
			return processentry.th32ProcessID;
		}
	}
	return NULL;
}

std::string random_string(const int len) {
	const std::string alpha_numeric("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");

	std::default_random_engine generator{ std::random_device{}() };
	const std::uniform_int_distribution< std::string::size_type > distribution{ 0, alpha_numeric.size() - 1 };

	std::string str(len, 0);
	for (auto& it : str) {
		it = alpha_numeric[distribution(generator)];
	}

	return str;
}


BasePlayer* Fetch() {

	DWORD64 Id = LocalPlayer.BasePlayer->GetActiveWeapon()->GetID();
	if (!Id || Id == 1525520776 || Id == 200773292)
		return nullptr; //building plan, hammer
	UINT64 BaseNetworkable = read<uint64_t>(Driver_File, processID, GameAssembly + 0x31BF748);
	UINT64 EntityRealm = read<uint64_t>(Driver_File, processID, BaseNetworkable + 0xB8);
	UINT64 ClientEntities = read<uint64_t>(Driver_File, processID, EntityRealm);
	UINT64 ClientEntities_list = read<uint64_t>(Driver_File, processID, ClientEntities + 0x10);
	UINT64 ClientEntities_values = read<uint64_t>(Driver_File, processID, ClientEntities_list + 0x28);
	int EntityCount = read<int>(Driver_File, processID, ClientEntities_values + 0x10);
	//cout << "Entites " << EntityCount << endl;
	if (!EntityCount)
		return nullptr;
	UINT64 EntityBuffer = read<uint64_t>(Driver_File, processID, ClientEntities_values + 0x18);

	for (int i = EntityCount - 1; i >= EntityCount / 4; i--)
	{
		UINT64 Entity = read<uint64_t>(Driver_File, processID, EntityBuffer + 0x20 + (i * 0x8));
		UINT64 Object = read<uint64_t>(Driver_File, processID, Entity + 0x10);
		UINT64 ObjectClass = read<UINT64>(Driver_File, processID,Object + 0x30);
		if (ObjectClass <= 100000) continue;
		pUncStr name = read<pUncStr>(Driver_File, processID,ObjectClass + 0x60);
		if (!name) continue;
		char* buff = name->stub;


		BasePlayer* Player = (BasePlayer*)read<uint64_t>(Driver_File, processID, Object + 0x28);
		if (!Player->IsValid())
			continue; //4 

		if (VisibleCheck) {
			if (!Player->IsVisible())
				continue;
		} //2 

		if (IgnoreTeam) {
			UINT64 EntitySID = Player->GetSteamID();
			int size = LocalPlayer.BasePlayer->GetTeamSize(); //3
			for (int j = 0; j < size; j++) {
				UINT64 SlotSID = LocalPlayer.BasePlayer->IsTeamMate(j);       //5
				if (SlotSID == EntitySID)
					continue;
			}
		}



	}
	return nullptr;
}

void EntityZaLoop()
{

	long long i = 0;
	UINT64  ObjectManager = read<UINT64>(Driver_File, processID, UnityPlayer + 0x17D69F8);
	UINT64  Object = read<UINT64>(Driver_File, processID, ObjectManager + 0x8);
	std::cout << "ObjMgr " << ObjectManager << std::endl;
	std::cout << "Obj " << Object << std::endl;


	std::cout << "Loading..." << std::endl;


	for (Object; (Object && (Object != read<UINT64>(Driver_File, processID, ObjectManager))); Object = read<UINT64>(Driver_File, processID, Object + 0x8))
	{

		//std::cout << "Ent" << endl;
		UINT64 GameObject = read<UINT64>(Driver_File, processID, Object + 0x10);
		WORD Tag = read<WORD>(Driver_File, processID, GameObject + 0x54);
		UINT64 ObjectClass = read<UINT64>(Driver_File, processID,Object + 0x30);

	


		if (Tag == 6)
		{
			UINT64 ObjClass = read<UINT64>(Driver_File, processID, GameObject + 0x30);
			UINT64 Entity = read<UINT64>(Driver_File, processID, ObjClass + 0x18);

			BasePlayer* Player = (BasePlayer*)read<UINT64>(Driver_File, processID, Entity + 0x28);
			if (!Player->IsValid())continue;





			std::cout << "BASEPLAYER FOUND" << std::endl;
			std::cout << "ID: " << Player->GetSteamID() << std::endl;



			if (read<UINT64>(Driver_File, processID, (read<UINT64>(Driver_File, processID, GameObject + 0x60)) == 0x616C506C61636F4C))
			{

				LP_isValid = true;
				LocalPlayer.BasePlayer = Player;
				firstentry = Object;
				if (TodCycle && LocalPlayer.pViewMatrix)
					return;

			}
		}

		else if (Tag == 5) {
			UINT64 ObjClass = read<UINT64>(Driver_File, processID, GameObject + 0x30);
			UINT64	Entity = read<UINT64>(Driver_File, processID, ObjClass + 0x18);
			LocalPlayer.pViewMatrix = (Matrix4x4*)(Entity + 0x2E4);
		}

		else if (Tag == 20011) {
			UINT64 ObjClass = read<UINT64>(Driver_File, processID, GameObject + 0x30);
			UINT64 Entity = read<UINT64>(Driver_File, processID, ObjClass + 0x18);
			UINT64 Dome = read<UINT64>(Driver_File, processID, Entity + 0x28);
			TodCycle = read<UINT64>(Driver_File, processID, Dome + 0x38);
		}



	NextEnt:
		continue;
	}
	if (!TodCycle || !LP_isValid || LocalPlayer.BasePlayer->IsMenu()) {

		std::cout << "Cant find player/sky/youre in menu..." << TodCycle << " " << LP_isValid << " " << LocalPlayer.BasePlayer->IsMenu() << std::endl;
		std::cin.get();
		exit(1);
	}
}
	



void MainLoop() {

	std::cout << "Loaded!\n";
	int last = -1;
	while (true) {
		Misc(TodCycle);
	//	Fetch();
		//WeaponPatch();
		if (fov)
		{
			auto klass = read<uint64_t>(Driver_File, processID, GameAssembly + 52159616);
			auto static_fields = read<uint64_t>(Driver_File, processID, klass + 0xB8);
			WriteProtected<float>(Driver_File, processID, static_fields + 0x18, 130.f);; //120
		}
		if (fov == false) {
			auto klass = read<uint64_t>(Driver_File, processID, GameAssembly + 52159616);
			auto static_fields = read<uint64_t>(Driver_File, processID, klass + 0xB8);
			WriteProtected<float>(Driver_File, processID, static_fields + 0x18, 90.f);
		}

	}
}








int main()
{
	SetConsoleTitle(random_string(24).c_str());

	std::cout << "Welcome To Daddy ;)\n";
	DWORD dLastError = GetLastError();
	LPCTSTR strErrorMessage = NULL;

	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		dLastError,
		0,
		(LPSTR)&strErrorMessage,
		0,
		NULL);


	Driver_File = CreateFileW(L"\\\\.\\doesshelikemetho", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	while (Driver_File == INVALID_HANDLE_VALUE)
	{
		Driver_File = CreateFileW(L"\\\\.\\doesshelikemetho", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		printf("Load the driver.\nError: ");
		printf(strErrorMessage);
		Sleep(1000);
		system("CLS");
	}

	if (window == 0)
	{
		window = FindWindowA(_xor_("UnityWndClass").c_str(), (_xor_("Rust").c_str()));
		std::cout << (_xor_("[+] Found Apex!!").c_str()) << std::endl;
	}
	else
	{
		std::cout << (_xor_("[+] Process Not Found ").c_str()) << std::endl;
	}

	GetWindowThreadProcessId(window, &processID);

	RECT rect;
	if (GetWindowRect(window, &rect))
	{
		Configs::screenWeight = rect.right - rect.left;
		Configs::screenHeight = rect.bottom - rect.top;
	}


	info_t Input_Output_Data;
	Input_Output_Data.pid = processID;
	unsigned long int Readed_Bytes_Amount;

	DeviceIoControl(Driver_File, ctl_base, &Input_Output_Data, sizeof Input_Output_Data, &Input_Output_Data, sizeof Input_Output_Data, &Readed_Bytes_Amount, nullptr);
	base_address = (unsigned long long int)Input_Output_Data.data;


	processID = get_process_id(_xor_("RustClient.exe").c_str());

	std::cout << (_xor_("ProcessId --> ").c_str()) << processID << std::endl;
	std::cout << (_xor_("Base Adress --> ").c_str()) << base_address << std::endl;


	get_modulebaseUP(Driver_File, processID, &UnityPlayer); //if one fails module fails //Module UnityPlayer
	if (UnityPlayer == NULL)
	{
		std::cout << "[-]Failed" << std::endl;
	}
	else
	{
		// std::cout << "Sucess" << std::endl;
		std::cout << "[+]UnityPlayer Addr--> " << std::hex << UnityPlayer << std::endl;
	}


	get_modulebaseGA(Driver_File, processID, &GameAssembly); // module GameAssembly
	if (GameAssembly == NULL)
	{
		std::cout << "[-]Failed" << std::endl;
	}
	else
	{
		//std::cout << "Sucess" << std::endl;
		std::cout << "[+]GameAssembly Addr--> " << std::hex << GameAssembly << std::endl;
	}


	EntityZaLoop();

	MainLoop();


	//getchar();
}




