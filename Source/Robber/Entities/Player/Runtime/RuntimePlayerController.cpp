// Fill out your copyright notice in the Description page of Project Settings.


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
