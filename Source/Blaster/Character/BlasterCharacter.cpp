#include "BlasterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"
#include "Blaster/Weapon/Weapon.h"
#include "Blaster/BlasterComponents/CombatComponent.h"
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

	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	Combat->SetIsReplicated(true);
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
	PlayerInputComponent->BindAction(TEXT("Equip"), IE_Pressed, this, &ABlasterCharacter::EquipButtonPressed);
}
void ABlasterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (Combat)
	{
		Combat->Character = this;

	}
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
//只能由服务器行动
void ABlasterCharacter::EquipButtonPressed()
{
	if (Combat)
	{
		if (HasAuthority())
		{
			Combat->EquipWeapon(OverLappingWeapon);
		}
		else {
			ServerEquipButtonPressed();
		}
		
	}
}

void ABlasterCharacter::OnRep_OverLappingWeapon(AWeapon* LastWeapon)
{
	if (OverLappingWeapon)
	{
		OverLappingWeapon->ShowPickUpWidget(true);
	}
	if (LastWeapon)
	{
		LastWeapon->ShowPickUpWidget(false);
	}
}
void ABlasterCharacter::ServerEquipButtonPressed_Implementation()
{
	if (Combat )
	{
		Combat->EquipWeapon(OverLappingWeapon);
	}
}
//处理服务器的触发
void ABlasterCharacter::SetOverLappingWeapon(AWeapon* Weapon)
{
	if (OverLappingWeapon)
	{
		OverLappingWeapon->ShowPickUpWidget(false);
	}
	OverLappingWeapon = Weapon;
	//只有本地玩家才会显示，服务器上没有人能看到，不需要显示
	if (IsLocallyControlled())
	{
		if (OverLappingWeapon)
		{
			OverLappingWeapon->ShowPickUpWidget(true);
		}
	}
}




