

#include "Casing.h"

#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


ACasing::ACasing()
{
	PrimaryActorTick.bCanEverTick = false;

	CasingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Casing StaticMesh"));
	SetRootComponent(CasingMesh);
	CasingMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	CasingMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	CasingMesh->SetSimulatePhysics(true);
	CasingMesh->SetEnableGravity(true);
	CasingMesh->SetNotifyRigidBodyCollision(true);
	ShellEjectionImpulse = 28.f;
}

void ACasing::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(FMath::RandRange(2.75f,4.f));



	FVector CasingMeshImpulseVector = GetActorForwardVector();
	//Just added random rotation on X direction
	CasingMeshImpulseVector.Z += FMath::RandRange(-0.3f, 0.3f);
	CasingMesh->AddImpulse(CasingMeshImpulseVector * ShellEjectionImpulse);


	
	CasingMesh->OnComponentHit.AddDynamic(this, &ACasing::OnHit);
}

void ACasing::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (ShellSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ShellSound, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, ShellSound, GetActorLocation());
	}
	CasingMesh->SetNotifyRigidBodyCollision(false);
}

 