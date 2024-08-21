// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"

#include "CameraController.h"


// Sets default values
ACharacterController::ACharacterController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Allow this character to replicate to other clients.
	bReplicates = true;

	// Construct CameraController
	CameraController = CreateDefaultSubobject<UCameraController>(FName("CameraController"));
	CameraController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterController::InputMoveForward(float axis)
{
	RawMoveVector.Y = axis;
}

void ACharacterController::InputMoveRight(float axis)
{
	RawMoveVector.X = axis;
}

void ACharacterController::InputTurnUp(float axis)
{
	CameraController->RotateCamera(FRotator(axis, 0.f, 0.f));
}

void ACharacterController::InputTurnRight(float axis)
{
	CameraController->RotateCamera(FRotator(0.f, axis, 0.f));
}

void ACharacterController::StepMovementThisFrame(float deltaTime)
{
	if (!CameraController)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing ACameraController from ACharacterController pawn!"));
		return;
	}
	
	TTuple<FVector, FVector> directions = CameraController->GetMovementDirections();
	FVector forward = directions.Get<0>() * RawMoveVector.Y;
	FVector right = directions.Get<1>() * RawMoveVector.X;

	FVector moveDirection = (forward + right); // don't need to normalize as i believe AddMovementInput already handles that
	AddMovementInput(moveDirection);
	
	// Old movement code for testing movement
	// Only moved relative to the world instead of to the player's camera
	//FVector worldDirection = FVector(RawMoveVector.X, RawMoveVector.Y, 0.f);
	//AddMovementInput(worldDirection); // don't need to multiply by deltaTime because unreal already does that for me
}

// Called every frame
void ACharacterController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	StepMovementThisFrame(deltaTime);
}

// Called to bind functionality to input
void ACharacterController::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);

	// Bind input axis
	inputComponent->BindAxis(FName("MoveForward"), this, &ACharacterController::InputMoveForward);
	inputComponent->BindAxis(FName("MoveRight"), this, &ACharacterController::InputMoveRight);
	inputComponent->BindAxis(FName("TurnUp"), this, &ACharacterController::InputTurnUp);
	inputComponent->BindAxis(FName("TurnRight"), this, &ACharacterController::InputTurnRight);
}

