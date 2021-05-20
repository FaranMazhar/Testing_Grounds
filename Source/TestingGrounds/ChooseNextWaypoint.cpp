// Developed by Scythe for testing purposes.


#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolRoutes.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get Patrol Points
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoutesComp = ControlledPawn->FindComponentByClass<UPatrolRoutes>();
	if (!ensure(PatrolRoutesComp)) { return EBTNodeResult::Failed; }

	auto PatrolPoints = PatrolRoutesComp->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no patrol points"), *ControlledPawn->GetName());
		return EBTNodeResult::Failed;
	}

	//Set Next Wayppoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(WaypointIndex.SelectedKeyName);
	BlackboardComp->SetValueAsObject(Waypoint.SelectedKeyName, PatrolPoints[Index]);

	//Cycle Index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(WaypointIndex.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}
