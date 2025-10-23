// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "MyButton.generated.h"

DECLARE_DELEGATE_OneParam(FClick, int32);

UCLASS()
class NETTPS_API UMyButton : public UButton
{
	GENERATED_BODY()

public:
	virtual void SynchronizeProperties() override;

	UFUNCTION()
	void OnClick();

	int32 buttonIdx = -1;
	FClick onClick;
};
