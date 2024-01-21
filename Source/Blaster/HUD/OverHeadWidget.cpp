#include "OverHeadWidget.h"
#include "Components/TextBlock.h"

void UOverHeadWidget::SetDisplayText(FString Text2Display)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(Text2Display));
	}
}

void UOverHeadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	ENetRole LocalRole = InPawn->GetLocalRole();
	FString Role;
	switch (LocalRole)
	{
	case ROLE_None:
		Role = FString("None");
		break;
	case ROLE_SimulatedProxy:
		Role = FString("SimulatedProxy");
		break;
	case ROLE_AutonomousProxy:
		Role = FString("AutonomousProxy");
		break;
	case ROLE_Authority:
		Role = FString("Authority");
		break;
	default:
		break;
	}
	FString LocalRoleStr = FString::Printf(TEXT("LocalRole: %s"), *Role);
	SetDisplayText(LocalRoleStr);
}

void UOverHeadWidget::NativeDestruct()
{
	Super::NativeDestruct();
	RemoveFromParent();
}
