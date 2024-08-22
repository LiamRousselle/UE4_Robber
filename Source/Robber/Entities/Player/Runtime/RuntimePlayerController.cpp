// Copyright (c) 2024 Liam Rousselle


#include "RuntimePlayerController.h"

void ARuntimePlayerController::TryPossessActor(AActor* target)
{
	if (target && HasAuthority())
	{
		target->SetOwner(this);
	}
}

void ARuntimePlayerController::OnPossess(APawn* pawnToPossess)
{
	Super::OnPossess(pawnToPossess);
	TryPossessActor(pawnToPossess);
}
