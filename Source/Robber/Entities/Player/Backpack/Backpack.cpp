// Copyright (c) 2024 Liam Rousselle


#include "Backpack.h"

#include "Net/UnrealNetwork.h"
#include "Robber/Entities/Player/Runtime/CharacterController.h"

UBackpack::UBackpack()
{
	SetIsReplicated(true);
}

void UBackpack::AfterConstructor(ACharacterController* owner)
{
	// Set the parent character controller to the one passed
	ParentCharacterController = owner;
}

void UBackpack::EquipTool(TSubclassOf<ATool> tool)
{
	if (!ParentCharacterController)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing ParentCharacterController (that shit is neccessary)"));
		return;
	}
	
	if (ParentCharacterController->HasAuthority())
	{
		InformServerOfToolToEquip_Implementation(tool);
		return;
	}
	else if (ParentCharacterController->GetLocalRole() == ROLE_AutonomousProxy)
	{
		InformServerOfToolToEquip(tool);
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Could not equip tool. Not running on server nor owning client."));
}

void UBackpack::UnEquipCurrentTool()
{
	
}

void UBackpack::AddToolToOwnedTools(TSubclassOf<ATool> tool)
{
	if (!ParentCharacterController->HasAuthority())
	{
		return;
	}
	OwnedTools.Add(tool);
}

void UBackpack::BeginPlay()
{
	Super::BeginPlay();
	
	for (TSubclassOf<ATool> tool : StartingTools)
	{
		AddToolToOwnedTools(tool);
	}
}

void UBackpack::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps); // the super function MUST be called, otherwise these properties won't be replicated

	DOREPLIFETIME_CONDITION(UBackpack, OwnedTools, COND_OwnerOnly);
}

void UBackpack::OnRep_OwnedTools()
{
	UE_LOG(LogTemp, Log, TEXT("Fucking replicated!"));
}

void UBackpack::InformServerOfToolToEquip_Implementation(TSubclassOf<ATool> tool)
{
	UE_LOG(LogTemp, Log, TEXT("Equipped tool: %s"), *tool->GetName());
}
