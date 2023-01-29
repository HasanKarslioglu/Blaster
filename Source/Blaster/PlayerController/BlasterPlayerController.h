
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController.generated.h"


UCLASS()
class BLASTER_API ABlasterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDScore(float Score);
	void SetHUDDefeats(int32 Defeats);
	void SetHUDKilledBy(FString KillerName);
	
	virtual void OnPossess(APawn* InPawn) override;	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	class ABlasterHUD* BlasterHUD;
};
