// Mehdi Sadrpour

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the patrol points
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = AIController->GetPawn();
	UPatrolRoute* PatrolRouteComp = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRouteComp)) { return EBTNodeResult::Failed; }
	TArray<AActor*> PatrolPoints = PatrolRouteComp->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		return EBTNodeResult::Failed;
	}

	// Set next waypoint
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	uint8 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);


	// Cycle the index
	uint8 NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);


	return EBTNodeResult::Succeeded;
}


