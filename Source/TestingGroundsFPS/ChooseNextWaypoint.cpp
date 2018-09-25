// Mehdi Sadrpour

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	uint8 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), Index)
	return EBTNodeResult::Succeeded;
}


