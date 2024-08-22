// Copyright (c) 2024 Liam Rousselle

#pragma once

#include "CoreMinimal.h"
#include "Tool.h"
#include "Components/ActorComponent.h"
#include "Backpack.generated.h"

/* The backpack is the component which is responsible for managing all items
 * which a player might have in there inventory. From the backpack you will be able to pick tools
 * in the backpack and tell the owner (which would be typeof ACharacterController) to equip those tools.
 */

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ROBBER_API UBackpack : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBackpack();

	// The list of tools which the player owns
	TArray<TSubclassOf<ATool>> OwnedTools = TArray<TSubclassOf<ATool>>();

	// The hash which will be used for the players hot bar
	// The key represents the slot which corresponds with the input they need to do
	// The value is the tool in that slot.
	TMap<int32, TSubclassOf<ATool>> ToolHotBar;

	
};
