

#include "BlasterDeadScreen.h"

void UBlasterDeadScreen::NativeConstruct()
{
	Super::NativeConstruct();

	FTimerHandle HideTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(HideTimerHandle, this, &UBlasterDeadScreen::FinishedHideWidgetTimer, 2.9f);
}

void UBlasterDeadScreen::FinishedHideWidgetTimer()
{
	RemoveFromParent();
}
