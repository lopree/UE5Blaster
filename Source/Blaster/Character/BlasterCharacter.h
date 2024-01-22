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
protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	class UWidgetComponent* OverHeadWidgetComponent;
	//��ֵ���ԣ��������Ḵ�Ƶ������ͻ���
	//�����Է����仯ʱ������ö�Ӧ�ķ���֪ͨ�Ƿ���ʾ���
	UPROPERTY(ReplicatedUsing = OnRep_OverLappingWeapon)
	AWeapon* OverLappingWeapon;
	UFUNCTION()
	void OnRep_OverLappingWeapon(AWeapon* LastWeapon);
public:
	void SetOverLappingWeapon(AWeapon* Weapon);
};
