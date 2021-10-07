// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"


// Sets default values
AMyTankPawn::AMyTankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	/*Отключаю зависимость поворота персонажа вместе с поворотом камеры*/
	bUseControllerRotationYaw = false;



	/*Создаю компонент BodyMesh и делаю его корневым*/
	BodyMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);
	
	/*Создаю компонент TurretMesh и наследую его от BodyMesh*/
	TurretMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	
	
	/*Создаю спринг-арм компонент и делаю его корневым*/
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 400.f;
	SpringArmComp->bUsePawnControlRotation = true;

	/*Создаю камера компонент и наследую его от спринг-арм*/
	FollowCamera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void AMyTankPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*получаю позицию текущего актора и его вектор направления*/
	FVector CurrentLocation1 = GetActorLocation();
	FVector ForwardVector1 = GetActorForwardVector();

	FVector NewLocation1 = CurrentLocation1 + (ForwardVector1 * MoveSpeed * MoveForwardBackInput * DeltaTime);
	SetActorLocation(NewLocation1);


	FVector CurrentLocation2 = GetActorLocation();
	FVector ForwardVector2 = GetActorRightVector();

	FVector NewLocation2 = CurrentLocation2 + (ForwardVector2 * MoveSpeed * MoveRightLeftInput * DeltaTime);
	SetActorLocation(NewLocation2);

}

// Called to bind functionality to input
void AMyTankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*Бинд поворота камеры g сторонам*/
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	/*Бинд движения влево-вправо, вперед-назад*/
	PlayerInputComponent->BindAxis("MoveForwardBack", this, &AMyTankPawn::MoveForwardBack);
	PlayerInputComponent->BindAxis("MoveRightLeft", this, &AMyTankPawn::MoveRightLeft);

}

void AMyTankPawn::MoveForwardBack(float AxisValue)
{
	//MoveForwardBackInput = AxisValue * (-1); // движение назад
	MoveForwardBackInput = AxisValue; // движение вперед
	
}

void AMyTankPawn::MoveRightLeft(float AxisValue)
{
	MoveRightLeftInput = AxisValue; // движение вперед
}


