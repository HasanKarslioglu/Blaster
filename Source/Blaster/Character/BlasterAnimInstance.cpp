
#include "BlasterAnimInstance.h"

#include "BlasterCharacter.h"
#include "Blaster/Weapon/Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blaster/BlasterTypes/CombatTypes.h"

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
	EquippedWeapon = BlasterCharacterRef->GetEquippedWeapon();
	bIsCrouched = BlasterCharacterRef->bIsCrouched;
	bAiming = BlasterCharacterRef->IsAiming();
	TurningInPlace = BlasterCharacterRef->GetTurningInPlace();
	bRotateRootBone = BlasterCharacterRef->ShouldRotateRootBone();
	bElimmed = BlasterCharacterRef->IsElimmed();
	
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

	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && BlasterCharacterRef->GetMesh())
	{
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), ERelativeTransformSpace::RTS_World);
		FVector OutPosition;
		FRotator OutRotation;
		BlasterCharacterRef->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));

		if (BlasterCharacterRef->IsLocallyControlled())
		{
			bLocalyControlled = true;
			FTransform RightHandTransform = BlasterCharacterRef->GetMesh()->GetSocketTransform(FName("hand_r"), ERelativeTransformSpace::RTS_World);
			FRotator TargetRightHandRotation = UKismetMathLibrary::FindLookAtRotation(RightHandTransform.GetLocation(), RightHandTransform.GetLocation() + (RightHandTransform.GetLocation() - BlasterCharacterRef->GetHitTarget()));
			RightHandRotation = FMath::RInterpTo(RightHandRotation, TargetRightHandRotation, DeltaSeconds, 20.f);
		}
	}
	
	bUseFABRIK = BlasterCharacterRef->GetCombatState() != ECombatState::ECT_Reloading;
	bUseAimOffsets = BlasterCharacterRef->GetCombatState() != ECombatState::ECT_Reloading;
	bTransformRightHand = BlasterCharacterRef->GetCombatState() != ECombatState::ECT_Reloading;
}











