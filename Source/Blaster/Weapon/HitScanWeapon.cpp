
#include "HitScanWeapon.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

void AHitScanWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* InstigatorController = OwnerPawn->GetController();
	
	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName("MuzzleFlash");
	if (MuzzleFlashSocket && InstigatorController)
	{
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
		FVector Start = SocketTransform.GetLocation();
		FVector End = Start + (HitTarget - Start) * 1.25f;
		
		FHitResult FireHit;
		UWorld* World = GetWorld();
		if (World)
		{
			World->LineTraceSingleByChannel(
				FireHit,
				Start,
				End,
				ECollisionChannel::ECC_Visibility
				);
			FVector BeamEnd = End;
			if (FireHit.bBlockingHit)
			{
				BeamEnd = FireHit.ImpactPoint;
				ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(FireHit.GetActor());
				if (BlasterCharacter && HasAuthority() && InstigatorController)
				{
					UGameplayStatics::ApplyDamage(
						BlasterCharacter,
						Damage,
						InstigatorController,
						this,
						UDamageType::StaticClass()
					);		
				}
				if (ImpactParticle)
				{
					UGameplayStatics::SpawnEmitterAtLocation(
						World,
						ImpactParticle,
						FireHit.ImpactPoint,
						FireHit.ImpactNormal.Rotation()
					);
				}
			}
			if (BeamParticle)
			{
				UParticleSystemComponent* Beam= UGameplayStatics::SpawnEmitterAtLocation(
					World,
					BeamParticle,
					SocketTransform
				);
				if (Beam)
				{
					Beam->SetVectorParameter(FName("Target"), BeamEnd);
				}
			}
		}
	}
}
