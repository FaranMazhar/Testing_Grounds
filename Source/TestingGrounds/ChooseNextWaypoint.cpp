// Developed by Scythe for testing purposes.


#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrollingGuard.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get Patrol Points
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPoints;

	//Set Next Wayppoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(WaypointIndex.SelectedKeyName);
	BlackboardComp->SetValueAsObject(Waypoint.SelectedKeyName, PatrolPoints[Index]);

	//Cycle Index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(WaypointIndex.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}
