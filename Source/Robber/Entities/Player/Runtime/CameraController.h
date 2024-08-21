// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CameraController.generated.h"

#define BASE_CAMERA_FIELD_OF_VIEW			110.f
#define CAMERA_EYE_LEVEL					60.f

/* The ACameraController is a component which shall be created inside of a ACharacterController.
 * This camera controller will have some public functions the ACharacterController will utilise. Like
 * "RotateCamera". The ACharacterController will also utilise the CameraControllers orientation to calculate
 * stuff like relative character movement.
 */

class UCameraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ROBBER_API UCameraController : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCameraController();

	// The component which will render the world to the player
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent = nullptr;

	// Rotates the camera using constraints
	// The constraints being the Pitch will always be clamped between -80* and 80*
	void RotateCamera(FRotator direction);

	// Gets both the forward & right directions this camera is facing. Then those directions will
	// lose there Z axis (Z = 0), then finally normalized, and returned in a tuple.
	// These directions are necessary for when the character controller calculates the movement direction
	TTuple<FVector, FVector> GetMovementDirections();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
