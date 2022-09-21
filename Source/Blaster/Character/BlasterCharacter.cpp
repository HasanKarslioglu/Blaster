

#include "BlasterCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

//--------------------------CONSTRUCTOR--------------------------//
ABlasterCharacter::ABlasterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//---------------------CAMERA AND SPRING ARM---------------------//
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->TargetArmLength = 600.f;
	SpringArm->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

//--------------------------TICK--------------------------//
void ABlasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//--------------------------BEGIN PLAY--------------------------//
void ABlasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

//--------------------------INPUT COMPONENT--------------------------//
void ABlasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABlasterCharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABlasterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABlasterCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ABlasterCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ABlasterCharacter::LookUp);
}


//--------------------------MOVEMENT FUNCTIONS--------------------------//
void ABlasterCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}
void ABlasterCharacter::MoveRight(float Value)
{
	
	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
	AddMovementInput(Direction, Value);
}
void ABlasterCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}
void ABlasterCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}
void ABlasterCharacter::Jump()
{
	Super::Jump();
}
