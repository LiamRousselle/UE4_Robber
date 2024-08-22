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

class ACharacterController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ROBBER_API UBackpack : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBackpack();

	// Ran after the constructor, used to pass more arguments which i can't for the constructor
	void AfterConstructor(ACharacterController* owner);

	// The list of starting tools the player will receive
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ATool>> StartingTools = TArray<TSubclassOf<ATool>>();
	
	// The list of tools which the player owns
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_OwnedTools)
	TArray<TSubclassOf<ATool>> OwnedTools = TArray<TSubclassOf<ATool>>();

	// The hash which will be used for the players hot bar
	// The key represents the slot which corresponds with the input they need to do
	// The value is the tool in that slot.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<int32, TSubclassOf<ATool>> ToolHotBar;

	// This function may be called either on the server or client
	// This function is responsible for equipping a tool which we own. When equipping a tool
	// if a tool is already equipped, that already equipped tool will be told to un-equip.
	// Please note! If the tool provided is not owned by this backpack class nothing will
	// happen. As this goes against the server.
	void EquipTool(TSubclassOf<ATool> tool);

	// This function may be called either on the server or client
	// Called to un-equip the current tool we're holding
	void UnEquipCurrentTool();
	
	void AddToolToOwnedTools(TSubclassOf<ATool> tool);
	
protected:
	// The tool which is currently being yielded by the player
	TSubclassOf<ATool> EquippedTool = nullptr;

	// Called once the actor is spawned into the world or when it's initialized
	virtual void BeginPlay() override;
	
	// @TODO(Liam): Describe what this does
	// This does networking stuff, describe it idiot
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Called when OwnedTools changes on the server
	UFUNCTION()
	void OnRep_OwnedTools();
	
	// This is called to inform the server that the client is trying to
	// equip a tool
	UFUNCTION( Server, Reliable )
	void InformServerOfToolToEquip(TSubclassOf<ATool> tool);
	void InformServerOfToolToEquip_Implementation(TSubclassOf<ATool> tool);
	
private:
	// The CharacterController that has this backpack as a child
	ACharacterController* ParentCharacterController = nullptr;
	
};
