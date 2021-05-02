bool jump = false;
bool air = false;
bool war = false;
bool once = false;


//Options
bool AlwaysDay = true;
bool SpiderMan = true;
bool Gravity = true;

void Misc(UINT64 TodCycle)
{
	if (AlwaysDay) {
		WriteProtected<float>(Driver_File, processID,TodCycle + 0x10, 14.00f);
	}

	//if (Vars::Misc::Sped)
	//	LocalPlayer.BasePlayer->Sped();



	if (Gravity)
		LocalPlayer.BasePlayer->SetGravity(100);





	//if (FakeAdmin)
		//LocalPlayer.BasePlayer->FakeAdmin(4);



		/*
	if (Vars::Misc::WalkOnWater) {
		if (GetAsyncKeyState(VK_MBUTTON)) {
			LocalPlayer.BasePlayer->WalkWater();

			jump = true;
		}
		else if (jump) {
			LocalPlayer.BasePlayer->WalkWater();
			jump = false;
		}
	}

	*/


}
