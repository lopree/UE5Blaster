#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BlasterCharacter.generated.h"


class AWeapon;
UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABlasterCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//定义CombatComponents
	virtual void PostInitializeComponents() override;
protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	//E键位绑定
	void EquipButtonPressed();

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	class UWidgetComponent* OverHeadWidgetComponent;
	//赋值属性，服务器会复制到其他客户端
	//当属性发生变化时，会调用对应的方法通知是否显示组件
	UPROPERTY(ReplicatedUsing = OnRep_OverLappingWeapon)
	AWeapon* OverLappingWeapon;
	UFUNCTION()
	void OnRep_OverLappingWeapon(AWeapon* LastWeapon);
	UPROPERTY(VisibleAnywhere)
	class UCombatComponent* Combat;
	UFUNCTION(Server,Reliable)
	void ServerEquipButtonPressed();
public:
	void SetOverLappingWeapon(AWeapon* Weapon);
};
