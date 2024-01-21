#include "BlasterGameModeBase.h"
#include "Character/BlasterCharacter.h"
ABlasterGameModeBase::ABlasterGameModeBase()
{
	//设置指定的Character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Character/BP_BlasterCharacter.BP_BlasterCharacter_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}
