
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blaster/BlasterTypes/TurningInPlace.h"
#include "BlasterCharacter.generated.h"

UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABlasterCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	void PlayFireMontage(bool bAiming);
	
protected:
	virtual void BeginPlay() override;
	virtual void Jump() override;

	
	//--------------------------MOVEMENT FUNCTIONS--------------------------//
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	
	//--------------------------FIRE AND CROUCH BUTTON PRESSED AND RELEASED--------------------------//
	void EquipButtonPressed();
	void CrouchButtonPressed();
	void AimButtonPressed();
	void AimButtonReleased();
	void FireButtonPressed();
	void FireButtonReleased();
	
	void AimOffset(float DeltaTime);

private:

	
	//--------------------------MESH AND CAMERA--------------------------//
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* OverHeadWidget;
	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	class AWeapon* OverlappingWeapon;

	//It is called automatically when the variables gets replicated. 
	//And it's just one way information transfer Server->clients 
	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);	

	UPROPERTY(VisibleAnywhere)
	class UCombatComponent* Combat;
	
	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();


	//--------------------------TURNING IN PLACE--------------------------//
	float AO_Yaw;
	float AO_Pitch;
	float InterpAO_Yaw;
	FRotator StartingAimRotation;
	ETurningInPlace TurningInPlace;
	void TurnInPlace(float DeltaTime);

	
	//--------------------------FIRE WEAPON--------------------------//
	UPROPERTY(EditAnywhere, Category = Combat)
	class UAnimMontage* FireWeaponMontage;

	
	//--------------------------SETTERS ANG GETTERS--------------------------//
public:
	void SetOverlappingWeapon(AWeapon* Weapon);
	bool IsEquippedWeapon();
	bool IsAiming();
	
	FORCEINLINE	float GetAO_Yaw() const {return AO_Yaw;};
	FORCEINLINE	float GetAO_Pitch() const {return AO_Pitch;};

	AWeapon* GetEquippedWeapon();
	
	FORCEINLINE ETurningInPlace GetTurningInPlace() const {return TurningInPlace;}
	FORCEINLINE UCameraComponent* GetFollowCamera() const {return FollowCamera;};
	FVector GetHitTarget() const;
};
