// Copyright (c) 2024 Liam Rousselle


#include "CharacterController.h"

#include "CameraController.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ACharacterController::ACharacterController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Allow this character to replicate to other clients.
	bReplicates = true;

	// Don't use Unreal's built in rotators
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	// Construct CameraController
	CameraController = CreateDefaultSubobject<UCameraController>(FName("CameraController"));
	CameraController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	// Properties
	UCharacterMovementComponent* movementComponent = GetCharacterMovement();
	
	// NOTE!
	// If the CharacterMovementComponent doesn't exist or doesn't construct successfully we want
	// the program to crash as that component is a vital part to the character controller.
	// Without it, the character controller will lose most of its functionality. It's best to just
	// boot the player out of the application.
	
	movementComponent->BrakingFriction = 10.f;
	movementComponent->MaxAcceleration = 1351.680054;
	movementComponent->MaxWalkSpeed = 340.f;
	movementComponent->bIgnoreBaseRotation = true;
	movementComponent->bOrientRotationToMovement = false;
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
	CameraController->RotateCameraWithConstraints(FRotator(axis, 0.f, 0.f));
}

void ACharacterController::InputTurnRight(float axis)
{
	CameraController->RotateCameraWithConstraints(FRotator(0.f, axis, 0.f));

	// Replicate the yaw
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		ServerReplicateYawOrientation(CameraController->GetRelativeRotation().Yaw);
	}
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

	FVector moveDirection = forward + right; // don't need to normalize since AddMovementInput already handles that
	AddMovementInput(moveDirection);
	
	// Old movement code for testing movement
	// Only moved relative to the world instead of to the player's camera
	//FVector worldDirection = FVector(RawMoveVector.X, RawMoveVector.Y, 0.f);
	//AddMovementInput(worldDirection); // don't need to multiply by deltaTime because unreal already does that for me
}

void ACharacterController::ServerReplicateYawOrientation_Implementation(float yaw)
{
	ClientReplicateYawOrientation(yaw);
}

void ACharacterController::ClientReplicateYawOrientation_Implementation(float yaw)
{
	GetMesh()->SetWorldRotation(FRotator(0.f, yaw, 0.f));
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

