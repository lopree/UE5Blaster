#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Initial UMETA(DisplayName = "Initial State"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_Dropped UMETA(DisplayName = "Dropped"),
	EWS_Max UMETA(DisplayName = "DefaultMax")
};
UCLASS()
class BLASTER_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	UFUNCTION()
	virtual void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
private:
	UPROPERTY(VisibleAnywhere, Category = "WeaponProperty")
	USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(VisibleAnywhere, Category = "WeaponProperty")
	class USphereComponent* WeaponCollision;
	UPROPERTY(ReplicatedUsing = OnRep_WeaponState,VisibleAnywhere, Category = "WeaponProperty")
	EWeaponState WeaponState;
	UFUNCTION()
	void OnRep_WeaponState();
	UPROPERTY(VisibleAnywhere, Category = "WeaponProperty")
	class UWidgetComponent* PickWidget;
public:
	virtual void Tick(float DeltaTime) override;
	//是否显示捡取提示
	void ShowPickUpWidget(bool bShowWidget);
	//设置武器状态
	void SetWeaponState(EWeaponState State);
	//取消碰撞区域的碰撞
	FORCEINLINE USphereComponent* GetAreaSphere() const { return WeaponCollision; }
};
