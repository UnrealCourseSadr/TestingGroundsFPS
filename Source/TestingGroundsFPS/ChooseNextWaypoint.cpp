// Mehdi Sadrpour

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h" // TODO Remove coupling

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// TODO Protect against empty patrol routes

	// Get the patrol points
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = AIController->GetPawn();
	APatrollingGuard* PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	TArray<AActor*> PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	// Set next waypoint
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	uint8 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	

	// Cycle the index
	uint8 NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	/*UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), Index)*/


	return EBTNodeResult::Succeeded;
}


