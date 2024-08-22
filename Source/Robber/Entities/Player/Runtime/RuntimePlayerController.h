// Copyright (c) 2024 Liam Rousselle

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RuntimePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROBBER_API ARuntimePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Attempts to make the player controller possess the provided actor
	void TryPossessActor(AActor* target);

protected:
	// Called when this player controller needs to possess a pawn
	virtual void OnPossess(APawn* pawnToPossess) override;
};
