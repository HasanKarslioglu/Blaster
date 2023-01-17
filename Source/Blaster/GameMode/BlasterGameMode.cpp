 
#include "BlasterGameMode.h"

#include "LandscapeRender.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void ABlasterGameMode::PlayerEliminated(ABlasterCharacter* ElimmedCharacter, ABlasterPlayerController* VictimController,
                                        ABlasterPlayerController* AttackerController)
{
	if (ElimmedCharacter)
	{
		ElimmedCharacter->Elim();
	}
}

void ABlasterGameMode::RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController)
{
	if (ElimmedCharacter)
	{
		ElimmedCharacter->Reset();
		ElimmedCharacter->Destroy();
	}
	if (ElimmedController)
	{
		TArray<AActor*> StartSpots;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(),StartSpots);
		int32 SelectedSpot = FMath::RandRange(0, StartSpots.Num() -1); 
		RestartPlayerAtPlayerStart(ElimmedController, StartSpots[SelectedSpot]);
	}
}
