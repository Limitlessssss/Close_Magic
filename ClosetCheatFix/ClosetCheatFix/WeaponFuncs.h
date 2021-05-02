void WeaponPatch1(WeaponData* Weapon)
{
	int Id = 0;
	if (Weapon) Id = Weapon->GetID();
	if (!Id) return;


	Weapon->SetRA();
	// Weapon->SetAutomatic();
	 //Weapon->ProjectileFired();




	return;

}
//float GetFov(BasePlayer* Entity, BoneList Bone) {
//	Vector2 ScreenPos;
//	if (!LocalPlayer.WorldToScreen(Entity->GetPosition(), ScreenPos)) return 1000.f;
//	return Math::Calc2D_Dist(Vector2(ScreenWidth / 2, ScreenHigh / 2), ScreenPos);
//}
//
//float GetBulletSpeed()
//{
//	switch (LocalPlayer.BasePlayer->GetActiveWeapon()->GetID())
//	{
//		case 1801994624: //smg
//			return 240.f;
//		case 1801741824: //bolt
//			return 656.25f;
//		case 1798229440: //l96
//			return 1125.f;
//		case 1802481984: //m39
//			return 469.f;
//		
//		case 1798228096: //revolver
//			return 300.f;
//		case 818877484: //p250
//			return 300.f;
//		case 1802077840: //waterpipe, 250-green ammo, 100-other
//			return 100.f;
//		case 1798227968: //double barrel, 250-green ammo, 100-other
//			return 100.f; 
//		case 1798226112: //lr300
//			return 375.f;
//		
//	}
//}
//
//Vector3 Prediction(const Vector3& LP_Pos, BasePlayer* Player, BoneList Bone)
//{
//	Vector3 BonePos = Player->GetPosition();
//	float Dist = Math::Calc3D_Dist(LP_Pos, BonePos);
//
//	if (Dist > 0.001f) {
//		float BulletTime = Dist / GetBulletSpeed();
//		Vector3 vel = Player->GetVelocity();
//		Vector3 PredictVel = vel * BulletTime * 0.75f;
//		BonePos += PredictVel; BonePos.y += (4.905f * BulletTime * BulletTime);
//	} return BonePos;
//}
//
//void Normalize(float& Yaw, float& Pitch) {
//	if (Pitch < -89) Pitch = -89;
//	else if (Pitch > 89) Pitch = 89;
//	if (Yaw < -360) Yaw += 360;
//	else if (Yaw > 360) Yaw -= 360;
//}
//
//void GoToTarget(BasePlayer* player)
//{
//	Vector3 Local = LocalPlayer.BasePlayer->GetPosition();
//	Vector3 PlayerPos = Prediction(Local, player, BoneList(BoneToAim));
//	Vector2 Offset = Math::CalcAngle(Local, PlayerPos) - LocalPlayer.BasePlayer->GetVA();
//	Normalize(Offset.y, Offset.x);
//	Vector2 AngleToAim = LocalPlayer.BasePlayer->GetVA() + Offset;
//
//	Normalize(AngleToAim.y, AngleToAim.x);
//	if (isnan(AngleToAim.x) || isnan(AngleToAim.y) || GetFov(player, BoneList(47)) > Fov)
//		return;
//	std::cout << "Gototarget " << "x: " << AngleToAim.x << " " << AngleToAim.y << " Distance: " << 0 << " Fov: " << GetFov(player, BoneList(47)) << std::endl;
//
//	LocalPlayer.BasePlayer->SetVA(AngleToAim);
//}
//
//
//void Aim(BasePlayer* AimEntity)
//{
//	if (Activate)
//	{
//
//		if (AimEntity && !LocalPlayer.BasePlayer->IsMenu()) {
//			if (GetAsyncKeyState, VK_RBUTTON)
//				GoToTarget(AimEntity);
//		}
//	}
//}

