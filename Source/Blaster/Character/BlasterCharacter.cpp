#include "BlasterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"
#include "Blaster/Weapon/Weapon.h"
ABlasterCharacter::ABlasterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArm,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//设置头上的UI
	OverHeadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHeadWidgetComponent"));
	OverHeadWidgetComponent->SetupAttachment(RootComponent);
}

void ABlasterCharacter::BeginPlay()
{ 
	Super::BeginPlay();
}
void ABlasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABlasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"),this,&ABlasterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &ABlasterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABlasterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &ABlasterCharacter::LookUpAtRate);
}

void ABlasterCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//添加条件，只有真正触发的玩家才会获得提示
	DOREPLIFETIME_CONDITION(ABlasterCharacter, OverLappingWeapon,COND_OwnerOnly);
}

void ABlasterCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value !=.0f)
	{
		const FRotator YawRotation(0.0f, Controller->GetControlRotation().Yaw,0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);

	}
}

void ABlasterCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != .0f)
	{
		const FRotator YawRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ABlasterCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate);
}

void ABlasterCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate);
}

void ABlasterCharacter::OnRep_OverLappingWeapon()
{
	if (OverLappingWeapon)
	{
		OverLappingWeapon->ShowPickUpWidget(true);
	}
}

void ABlasterCharacter::SetOverLappingWeapon(AWeapon* Weapon)
{

}




