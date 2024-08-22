// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraController.h"

#include "Camera/CameraComponent.h"

// Used to remove the Z axis from vector (set Z to zero)
const FVector XYPlane = FVector(1.f, 1.f, 0.f);

// Sets default values for this component's properties
UCameraController::UCameraController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; // maybe change in future

	// Offset this component to be eye level
	SetRelativeLocation(FVector::ZAxisVector * CAMERA_EYE_LEVEL);
	
	// Construct the CameraComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("CameraComponent"));
	CameraComponent->FieldOfView = BASE_CAMERA_FIELD_OF_VIEW;
	CameraComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
}


void UCameraController::RotateCameraWithConstraints(FRotator direction)
{
	if (bLockCharacterRotation)
	{
		// When the character shouldn't rotate along the yaw axis
		FRotator current = GetRelativeRotation();

		float pitch = FMath::Clamp(direction.Pitch + current.Pitch, -80.f, 80.f);
		float yaw = current.Yaw + direction.Yaw;

		FRotator result = FRotator(pitch, yaw, 0.f);
		SetRelativeRotation(result);
	}
	else
	{
		// When teh character should rotate along the yaw axis
		FRotator current = GetRelativeRotation();
		
	}
}

TTuple<FVector, FVector> UCameraController::GetMovementDirections()
{
	FVector forward = GetForwardVector() * XYPlane;
	FVector right = GetRightVector() * XYPlane;
	return TTuple<FVector, FVector>(forward.GetSafeNormal(), right.GetSafeNormal());
}

// Called when the game starts
void UCameraController::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UCameraController::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

