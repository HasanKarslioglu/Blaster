#pragma once

#define TRACE_LENGHT 50000.f

UENUM(BlueprintType)
enum class EWeaponTypes : uint8
{
	EWT_AssaultRifle UMETA(DisplayName = "Assault Rifle"),
	EWT_RocketLauncher UMETA(DisplayName = "Rocket Launcher"),
	EWT_Pistol UMETA(DisplayName = "Pistol"),
	EWT_SubmachineGun UMETA(DisplayName = "Submachine Gun"),
	EWT_Shotgun UMETA(DisplayName = "Shotgun"),
	EWT_SniperRiffle UMETA(DisplayName = "Sniper Riffle"),

	
	EWT_MAX UMETA(DisplayName = "Default Max")
};