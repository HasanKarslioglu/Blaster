
#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "HitScanWeapon.generated.h"

UCLASS()
class BLASTER_API AHitScanWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void Fire(const FVector& HitTarget) override;

protected:
	FVector TraceEndWithScatter(const FVector& TraceStart, const FVector& HitTarget);
	void WeaponTraceHit(const FVector& TraceStart, const FVector& HitTarget, FHitResult& OutHit);
	
	UPROPERTY(EditAnywhere)
	USoundCue* HitSound;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* ImpactParticle;
	UPROPERTY(EditAnywhere)
	float Damage = 20.f;
	
private:
	UPROPERTY(EditAnywhere)
	UParticleSystem* BeamParticle;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;
	
	UPROPERTY(EditAnywhere)
	USoundCue* FireSound;

	UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
	float DistanceToSphere = 800.f;

	UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
	float SphereRadius = 75.f;

	UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
	bool bUseScatter = false;
};





