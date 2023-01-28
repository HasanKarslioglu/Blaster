#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BlasterHUD.generated.h"

USTRUCT(BlueprintType)
struct FHUDPackage
{
	GENERATED_BODY();
public:
	UTexture2D* CrosshairsCenter;
	UTexture2D* CrosshairsLeft;
	UTexture2D* CrosshairsRight;
	UTexture2D* CrosshairsTop;
	UTexture2D* CrosshairsBottom;
	float CrosshairSpread;
	FLinearColor CrosshairsColor;
};

UCLASS()
class BLASTER_API ABlasterHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	TSubclassOf<UUserWidget> CharacterOverlayClass;
	UPROPERTY()
	class UCharacterOverlay* CharacterOverlay;
	
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	TSubclassOf<UUserWidget> BlasterDeadScreenClass;
	UPROPERTY()
	class UBlasterDeadScreen* DeadScreenWidget;
	void ShowDeadScreen();
	void HideDeadScreen();
	
protected:

	virtual void BeginPlay() override;
	void addCharacterOverlay();
	
private:
	FHUDPackage HudPackage;
	
	void DrawCrosshair(UTexture2D* Texture, FVector2D ViewportCenter, FVector2D Spread, FLinearColor CrosshairsColor);
	UPROPERTY(EditAnywhere)
	float CrosshairSpreadMax = 12.f;

public:
	FORCEINLINE void SetHUDPackage(const FHUDPackage& Package) {HudPackage = Package;};
};

