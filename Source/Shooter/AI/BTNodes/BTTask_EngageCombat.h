// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_EngageCombat.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UBTTask_EngageCombat : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_EngageCombat();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
