// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Boss.generated.h"

// 보스 상태 정의
UENUM(BlueprintType)
enum class EBossState : uint8
{
	IDLE,
	ATTACK_JUMP
};

UCLASS()
class NETTPS_API ABoss : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(
		class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	// 모든 상태의 클래스 담을 변수
	TArray<TSharedPtr<class BossStateBase>> stateList;
	// 현재 보스의 상태 클래스를 담을 변수
	TSharedPtr<class BossStateBase> currStateClass;
	// 현재 보스 상태
	UPROPERTY(Replicated)
	EBossState currState;
	// 상태 전환 함수
	void ChangeState(EBossState newState);

	// 타겟 (Player)
	UPROPERTY()
	class ANetTPSCharacter* target;
};





