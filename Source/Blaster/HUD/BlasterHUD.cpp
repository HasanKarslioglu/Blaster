

#include "BlasterHUD.h"

#include "CharacterOverlay.h"
#include "BlasterDeadScreen.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"


void ABlasterHUD::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && CharacterOverlayClass)
	{
		CharacterOverlay = CreateWidget<UCharacterOverlay>(PlayerController, CharacterOverlayClass);
	}
}

void ABlasterHUD::addCharacterOverlay()
{
	if (CharacterOverlay)
	{
		CharacterOverlay->AddToViewport();
	}
	
}

void ABlasterHUD::DrawHUD()
{
	Super::DrawHUD();

	FVector2D ViewportSize;
	if (GEngine)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		const FVector2D ViewportCenter(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);

		float SpreadScaled = HudPackage.CrosshairSpread * CrosshairSpreadMax;
		
		if (HudPackage.CrosshairsCenter)
		{
			FVector2D Spread(0.f, 0.f); 
			DrawCrosshair(HudPackage.CrosshairsCenter, ViewportCenter, Spread , HudPackage.CrosshairsColor);
		}
		if (HudPackage.CrosshairsTop)
		{
			FVector2D Spread(0.f, SpreadScaled); 
			DrawCrosshair(HudPackage.CrosshairsTop, ViewportCenter, Spread ,HudPackage.CrosshairsColor);
		}
		if (HudPackage.CrosshairsBottom)
		{
			FVector2D Spread(0.f, -SpreadScaled); 
			DrawCrosshair(HudPackage.CrosshairsBottom, ViewportCenter, Spread, HudPackage.CrosshairsColor);
		}
		if (HudPackage.CrosshairsLeft)
		{
			FVector2D Spread(-SpreadScaled, 0.f); 
			DrawCrosshair(HudPackage.CrosshairsLeft, ViewportCenter, Spread, HudPackage.CrosshairsColor);
		}
		if (HudPackage.CrosshairsRight)
		{
			FVector2D Spread(SpreadScaled, 0.f); 
			DrawCrosshair(HudPackage.CrosshairsRight, ViewportCenter, Spread, HudPackage.CrosshairsColor);
		}
	}
}

void ABlasterHUD::DrawCrosshair(UTexture2D* Texture, FVector2D ViewportCenter, FVector2D Spread, FLinearColor CrosshairsColor)
{
	const float TextureWidth = Texture->GetSizeX();
	const float TextureHeight = Texture->GetSizeY();
	const FVector2D TextureDrawPoint(
		ViewportCenter.X - (TextureWidth / 2.f) + Spread.X,
		ViewportCenter.Y - (TextureHeight / 2.f + Spread.Y)
	);
	
	DrawTexture(
		Texture,
		TextureDrawPoint.X,
		TextureDrawPoint.Y,
		TextureWidth,
		TextureHeight,
		0.f,
		0.f,
		1.f,
		1.f,
		CrosshairsColor
	);
}


void ABlasterHUD::ShowDeadScreen()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && BlasterDeadScreenClass)
	{
		DeadScreenWidget = CreateWidget<UBlasterDeadScreen>(PlayerController, BlasterDeadScreenClass);
		DeadScreenWidget->AddToViewport();
	}
}

void ABlasterHUD::HideDeadScreen()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && BlasterDeadScreenClass)
	{
		DeadScreenWidget->RemoveFromParent();
	}
}
















