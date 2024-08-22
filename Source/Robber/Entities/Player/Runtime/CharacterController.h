// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterController.generated.h"

/* The character controller is the character which all players shall possess. This class
 * handles all basic movement of a character controller, like walking, crouching, etc.
 * All players shall possess a character controller. This class will be parented by a blueprint in the
 * future. Which the blueprint will handle everything visually. (Like character mesh, animations, etc.)
 */

class UCameraController;
class UInputComponent;

UCLASS()
class ROBBER_API ACharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterController();

	// The CameraController which will handle everything camera related
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraController* CameraController = nullptr;
	
protected:
	// The 2D vector which represents the input map of the direction the player wants to move
	FVector2D RawMoveVector = FVector2D(0.f, 0.f);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the input axis "MoveForward" changes
	void InputMoveForward(float axis);
	// Called when the input axis "MoveRight" changes
	void InputMoveRight(float axis);
	// Called when the input axis "TurnUp" changes
	void InputTurnUp(float axis);
	// Called when the input axis "TurnRight" changes
	void InputTurnRight(float axis);
	
	// Called every frame
	// Used to step the character's movement each frame
	void StepMovementThisFrame(float deltaTime);

private:
	// Used to send the yaw we're currently seeing on the client to the server
	// Unreliable as this RPC will be called very often
	UFUNCTION( Server, Unreliable )
	void ServerReplicateYawOrientation(float yaw);
	void ServerReplicateYawOrientation_Implementation(float yaw);

	// Called by ServerReplicateYawOrientation on the server to replicate the character controllers
	// yaw on all clients except the client who sent it
	// Unreliable as this RPC will be called very often
	UFUNCTION( NetMulticast, Reliable )
	void ClientReplicateYawOrientation(float yaw);
	void ClientReplicateYawOrientation_Implementation(float yaw);

public:
	// Called every frame
	virtual void Tick(float deltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* inputComponent) override;
};
