// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetCodeGameMode.generated.h"

/*
 * "NetCodeGameMode" is the game mode which will be responsible for the main NetCode of the game.
 * Other game modes should be derived from NetCodeGameMode as NetCodeGameMode handles everything related
 * to replication, and the main mechanics of the game. (Like guns, interactions, ect.)
*/

UCLASS()
class ANetCodeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANetCodeGameMode();
	
};
