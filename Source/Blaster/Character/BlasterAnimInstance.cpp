
#include "BlasterAnimInstance.h"

#include "BlasterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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
}
