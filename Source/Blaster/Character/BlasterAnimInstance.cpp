
#include "BlasterAnimInstance.h"

#include "BlasterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBlasterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BlasterCharacterRef = Cast<ABlasterCharacter>(TryGetPawnOwner());
}

void UBlasterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (BlasterCharacterRef == nullptr)
	{
		BlasterCharacterRef = Cast<ABlasterCharacter>(TryGetPawnOwner());;
	}
	if (BlasterCharacterRef == nullptr) return;
	
	FVector Velocity = BlasterCharacterRef->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = BlasterCharacterRef->GetCharacterMovement()->IsFalling();
	bIsAccelerating = BlasterCharacterRef->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false;
	bWeaponEquipped = BlasterCharacterRef->IsEquippedWeapon();
	bIsCrouched = BlasterCharacterRef->bIsCrouched;
	bAiming = BlasterCharacterRef->IsAiming();
	
	FRotator AimRotation = BlasterCharacterRef->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(BlasterCharacterRef->GetVelocity());
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaSeconds, 9.f);

	YawOffset = DeltaRotation.Yaw;
	
	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = BlasterCharacterRef->GetActorRotation();
	
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaSeconds;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaSeconds, 5.f);
	Lean = FMath::Clamp( Interp, -90.f, 90.f);
	
	AO_Yaw = BlasterCharacterRef->GetAO_Yaw();
	AO_Pitch = BlasterCharacterRef->GetAO_Pitch();
}











