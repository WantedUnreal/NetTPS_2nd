#include "BossAttackJumpState.h"

#include "Boss.h"
#include "NetTPSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

BossAttackJumpState::BossAttackJumpState(class ABoss* ownedPawn)
	: BossStateBase(ownedPawn)
{
	delayTime = 1;
}

void BossAttackJumpState::OnEnter()
{
	BossStateBase::OnEnter();

	// level 에 있는 모든 플레이어 찾자.
	UGameplayStatics::GetAllActorsOfClass(boss->GetWorld(), ANetTPSCharacter::StaticClass(), allPlayer);

	// 현재까지 최장거리
	float farthest = 0;
	// 현재까지 최장거리 Player 의 idx
	int32 farthestIdx = -1;

	for (int32 i = 0; i < allPlayer.Num(); i++)
	{
		// 나 (Boss) 와 Player 의 거리를 구하자.
		float dist = FVector::Distance(allPlayer[i]->GetActorLocation(), boss->GetActorLocation());
		// 그 거리가 현재까지 최장거리 보다 크다면
		if (dist > farthest)
		{
			// 현재까지 최장거리 갱신
			farthest = dist;
			// 현재까지 최장거리 Player 의 idx 갱신
			farthestIdx = i;
		}
	}

	// 만약에 가장 먼 Player 찾았다면
	if (farthestIdx != -1)
	{
		// 가장 먼 Player 를 Boss 의 타겟으로 설정
		boss->target = Cast<ANetTPSCharacter>(allPlayer[farthestIdx]);
		// 점프!
		GetJumpInitialVelocity();
		// 타겟을 바라보자.
		LookTarget();
	}
}

void BossAttackJumpState::OnUpdate(float deltaTime)
{
	BossStateBase::OnUpdate(deltaTime);
	// 만약에 보스가 바닥에 있다면
	if (boss->GetCharacterMovement()->IsFalling() == false)
	{
		// 1 초 있다가
		if (IsDelayComplete())
		{
			// IDLE 상태로 전환
			boss->ChangeState(EBossState::IDLE);
		}
	}
}

void BossAttackJumpState::GetJumpInitialVelocity()
{
	// target 이 있는 방향과 (target 까지의 거리 - 200) 만큼 이동
	// target 위치에서 200 만큼 떨어지 위치까지 점프 하겠다.
	FVector jumpLocation = boss->target->GetActorLocation() - boss->GetActorLocation();
	jumpLocation = jumpLocation.GetSafeNormal() * (jumpLocation.Length() - 200);
	// 원하는 최고점에 맞는 Z 속도 계산
	float gravity = FMath::Abs(boss->GetWorld()->GetGravityZ() * 1);
	// V0 (초기 Z 속력) = Sqrt ( 2 * 중력 * 올라가고 싶은 높이)
	float initialZ = FMath::Sqrt(2 * gravity * 500);

	// 판별식 (b^2 - 4ac)
	float deltaZ = boss->target->GetActorLocation().Z - boss->GetActorLocation().Z;
	float discriminant = FMath::Square(initialZ) - 2 * gravity * deltaZ;
	// 최종 걸린 시간
	float totalTime = (initialZ + FMath::Sqrt(discriminant)) / gravity;

	// 수평 방향 속도 ( 속력 = 거리 / 시간)
	FVector xy = FVector(jumpLocation.X, jumpLocation.Y, 0);
	FVector xySpeed = xy / totalTime;
	// 최종 속도
	FVector velocity = xySpeed;
	velocity.Z = initialZ;

	// velocity 값으로 움직여라
	boss->LaunchCharacter(velocity, true, true);
}

void BossAttackJumpState::LookTarget()
{
	// 타겟을 향하는 방향을 구하자.
	FVector toTarget = boss->target->GetActorLocation() - boss->GetActorLocation();
	// 수직 성분 0 으로 하자.
	toTarget.Z = 0;
	toTarget.Normalize();
	// 타겟을 바라보는 각도를 구하자.
	FRotator rot = UKismetMathLibrary::MakeRotFromXZ(toTarget, FVector::UpVector);
	boss->SetActorRotation(rot);
}
