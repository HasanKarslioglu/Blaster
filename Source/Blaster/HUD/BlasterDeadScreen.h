
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BlasterDeadScreen.generated.h"

UCLASS()
class BLASTER_API UBlasterDeadScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* KilledTextBlock; 
protected:
	virtual void NativeConstruct() override;
private:
	void FinishedHideWidgetTimer();
};
