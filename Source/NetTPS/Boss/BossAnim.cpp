// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAnim.h"

#include "GameFramework/CharacterMovementComponent.h"

void UBossAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	// 소유 폰 얻어오자
	pawnOwner = Cast<ABoss>(TryGetPawnOwner());
}

void UBossAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (pawnOwner)
	{
		// 현재 보스 상태 설정
		currState = pawnOwner->currState;
		// 공중에 있는지 여부 설정
		isAir = pawnOwner->GetCharacterMovement()->IsFalling();
	}
}
