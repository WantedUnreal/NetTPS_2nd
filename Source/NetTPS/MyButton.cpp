// Fill out your copyright notice in the Description page of Project Settings.


#include "MyButton.h"

void UMyButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	OnClicked.AddDynamic(this, &UMyButton::OnClick);
}

void UMyButton::OnClick()
{
	
	UE_LOG(LogTemp, Warning, TEXT("버튼 눌림"));
	onClick.ExecuteIfBound(buttonIdx);
}
