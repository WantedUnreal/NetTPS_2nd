#pragma once
#include "BossStateBase.h"

class BossAttackJumpState : public BossStateBase
{
public:
	BossAttackJumpState(class ABoss* ownedPawn);
	virtual ~BossAttackJumpState() {}

	virtual void OnEnter() override;
	virtual void OnUpdate(float deltaTime) override;
	void GetJumpInitialVelocity();
	void LookTarget();

	TArray<AActor*> allPlayer;
};
