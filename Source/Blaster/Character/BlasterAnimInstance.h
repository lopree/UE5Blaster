#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BlasterCharacter.h"
#include "BlasterAnimInstance.generated.h"


UCLASS()
class BLASTER_API UBlasterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:
	UPROPERTY(BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = true))
	class ABlasterCharacter* BlasterCharacter;
	UPROPERTY(BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	float Speed;
	UPROPERTY(BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	bool bIsInAir;
	UPROPERTY(BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	bool bIsAccelerating;
	UPROPERTY(BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	bool bWeaponEquipped;
	UPROPERTY(BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	bool bIsCrouched;
	UPROPERTY(BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	bool bIsAiming;
};
