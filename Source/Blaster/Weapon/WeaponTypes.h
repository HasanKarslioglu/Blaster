#pragma once

UENUM(BlueprintType)
enum class EWeaponTypes : uint8
{
	EWT_AssaultRifle UMETA(DisplayName = "Assault Rifle"),
	EWT_RocketLauncher UMETA(DisplayName = "Rocket Launcher"),
	EWT_Pistol UMETA(DisplayName = "Pistol"),

	
	EWT_MAX UMETA(DisplayName = "Default Max")
};