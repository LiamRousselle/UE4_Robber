// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

};
