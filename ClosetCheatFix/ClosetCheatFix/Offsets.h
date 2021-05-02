#pragma once

#define oGameObjectManager 0x059FF10
#define oBaseNetworkable 0x31BF748
#define oBaseNetworkableSteam 0x31BF748

//class BasePlayer
#define oPlayerModel 0x4B0 //0x520  public PlayerModel playerModel; // 0x490
#define oPlayerFlags 0x638 //0x480  public BasePlayer.PlayerFlags playerFlags; // 0x480
#define oPlayerName 0x698 //0x4E8   protected string _displayName; // 0x4E8
#define oPlayerHealth 0x214 //0x1F4 private float _health; // 0x1F4
#define olastSentTickTime 0x60C //0x60C не требо
#define oClientTeam 0x580 // 0x5B0 public PlayerTeam clientTeam; // 0x5B0
#define oLifestate 0x20C // 0x1EC public BaseCombatEntity.LifeState lifestate; // 0x1EC
#define oSteamID 0x680 // 0x4D8 public ulong userID; // 0x4D8
#define oPlayerInput 0x4D0 // 0x4A8 public PlayerInput input; // 0x4A8
#define oPlayerInventory 0x648 //0x490 public PlayerInventory inventory; 
#define oActiveUID 0x5B0 // 0x5B0 private uint clActiveItem;
#define oFrozen 0x4B8 // 0x528 public bool Frozen; // 0x528
#define oPlayerMovement 0x4D8 // 0x4B0 public BaseMovement movement; // 0x4B0
#define oWaterBonus 0x4D8 // 0x50C public float clothingWaterSpeedBonus; // 0x50C
#define oNoSway 0x704 //0x510 public float clothingAccuracyBonus; // 0x510
#define oNoBlockAiming 0x6F8 //0x504 public bool clothingBlocksAiming; // 0x504
#define oSpeedReduction 0x6FC // 0x508 public float clothingMoveSpeedReduction; // 0x508



#define oGroundAngle 0xB4 // private float groundAngle;
#define oGroundAngleNew 0xB8  // private float groundAngleNew;
#define oFlyHack  0x13C     // private bool flying;

#define oGravity 0x74  //public float gravityMultiplier;
#define oMultiplierSwimming 0x78  // public float gravityMultiplierSwimming;

#define oHeld 0x98 //private EntityRef heldEntity

//BaseProjectile
#define oAuto 0x270 //public bool automatic;
#define oFastReload 0x2A8 //0x280 bool fractionalReload
#define oDistance 0x268 // public float distanceScale
#define oSuccessFraction 0x350  //public float successFraction;
#define oprojectileVelocityScale 0x26C //public float projectileVelocityScale
//RecoilProperties
#define oRecoilMinYaw 0x18 //public float recoilYawMin;
#define oRecoilMaxYaw 0x1C //public float recoilYawMax;
#define oRecoilMinPitch 0x20 //public float recoilPitchMin;
#define oRecoilMaxPitch 0x24 //public float recoilPitchMax;

#define oArrowBack 0x344 //private float arrowBack;
#define oTriggerReady 0x340 // protected bool attackReady;
