#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Blaster/Character/BlasterCharacter.h"
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	SetRootComponent(WeaponMesh);
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereWeaponCollision"));
	WeaponCollision->SetupAttachment(RootComponent);
	WeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PickWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickWidget"));
	PickWidget->SetupAttachment(RootComponent);

	
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnSphereOverlap);
	if (PickWidget)
	{
		PickWidget->SetVisibility(false);
	}
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABlasterCharacter* Character = Cast<ABlasterCharacter>(OtherActor);
	if (Character && PickWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Physic]Overlap"));
		PickWidget->SetVisibility(true);
	}
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

