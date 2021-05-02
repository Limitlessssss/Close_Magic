

bool LongHand = false;
void WeaponPatch()
{
	USHORT Hash = 0;
	WeaponData* Weapon = LocalPlayer.BasePlayer->GetActiveWeapon();
	//std::cout << "Weapon: " << Weapon << std::endl;
	if (Weapon) Hash = Weapon->GetNameHash();
	//std::cout << "Weapon: " << Hash << std::endl;
	switch (Hash)
	{
		//nullptr
	case 0: return;

		//Weapon
	case 0x5A9F:
		Weapon->SuperBow();
	//	Weapon->FatBullet();
	//	Weapon->Compund();
		break;

	case 0x6B1:
	case 0x74F5:
	case 0x67DA:
	case 0x3146:
	case 0x79C4:
	case 0x573C:
	case 0xB32A:
	case 0xC196:
	//	Weapon->SetAutomatic();
	//	Weapon->FatBullet();
	//	Weapon->Compund();
	case 0x7983:
	case 0xE5EA:
	case 0x77E9:
	case 0xE97D:
	case 0xC2DD:
	case 0x52F7:
	case 0xFDC3:
	case 0x62E5:
	case 0x6A09:
	case 0x3511:
	case 0xCFA1:
	case 0xF87E:
	//	Weapon->AntiSpread();
	//	Weapon->NoRecoil();
	//	Weapon->FatBullet();
	//	Weapon->Compund();

	case 0xB0A0:
	case 0x435E:
	{

		if (Hash == 0x435E)
		{
		//	Weapon->FatBullet();
			Weapon->SuperEoka();
		//	Weapon->Compund();
		}
	} break;



	case 0xF3B9:
	//	Weapon->Compund();
		break;
	case 0xCBD8:
	case 0xAB85:
	case 0xFB2B:
	case 0x6104:
	case 0xC859:
	case 0x96D3:
	case 0x7340:
	case 0xC68B:
	case 0x2F12:
	case 0x65B4:
	case 0x1F2D:
	case 0x2658:
	case 0xAC02:
	case 0x282A:
	case 0x8151:
	case 0xFACE:
	case 0x7296:
	case 0x4B0A:
	case 0xCD:
	case 0x2333:
		//if (LongHand) {
		//	Weapon->FatHand();
	//		Weapon->LongHand();
		//	Weapon->RunOnHit();
	//		Weapon->Compund();
			break;
	}
}