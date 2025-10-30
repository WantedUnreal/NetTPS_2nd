// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Boss.h"
#include "Animation/AnimInstance.h"
#include "BossAnim.generated.h"

/**
 * 
 */
UCLASS()
class NETTPS_API UBossAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// 소유폰
	UPROPERTY()
	ABoss* pawnOwner;
	// 보스 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBossState currState;
	// 보스가 공중에 있는지 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isAir;	
};
