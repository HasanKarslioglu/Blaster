
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
	void SetHUDWeaponAmmo(int32 Ammo);
	void SetHUDCarriedAmmo(int32 Ammo);
	void SetHUDMatchCountdown(float CountdownTime);
	
	virtual void Tick(float DeltaSeconds) override;
	virtual float GetServerTime();
	virtual void ReceivedPlayer() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	virtual void OnPossess(APawn* InPawn) override;
	void OnMatchStateSet(FName State);
protected:
	virtual void BeginPlay() override;
	void CheckTimeSync(float DeltaSeconds);
	void SetHUDTime();
	void PollInit();

	//Sync time between server and clients
	UFUNCTION(Server, Reliable)
	void ServerRequestServerTime(float TimeOfClientRequest);
	UFUNCTION(Client, Reliable)
	void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);
	//Difference between Client and Server
	float ClientServerDelta = 0.f;
	UPROPERTY(EditAnywhere, Category = Time)
	float TimeSyncFrequency = 5.f;
	
	float TimeSyncRunningTime = 0.f;

private:
	UPROPERTY()
	class ABlasterHUD* BlasterHUD;

	float MatchTime = 120.f;
	uint32 CountdownInt = 0;

	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
	FName MatchState;
	UFUNCTION()
	void OnRep_MatchState();

	UPROPERTY()
	class UCharacterOverlay* CharacterOverlay;
	
	bool bInitializeCharacterOverlay = false;
	float HUDHealth;
	float HUDMaxHealth;
	float HUDScore;
	int32 HUDDefeats;
};
