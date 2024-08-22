// Copyright (c) 2024 Liam Rousselle

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tool.generated.h"

/* The tool actor is an actor which all items the players can equip will be derived from.
 * Tools rely on the Backpack actor component to be equipped/unequipped and handle network owners.
 */

UCLASS()
class ROBBER_API ATool : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float deltaTime) override;
};
