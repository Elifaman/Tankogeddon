// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyTankPawn.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TANKPROJECT_API AMyTankPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyTankPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	/*ќбъ€вл€ю меш дл€ самого танка и его пушки*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* TurretMesh;

	/*ќбъ€вл€ю методы движени€ вперед-назад, влево-вправо*/
	void MoveForwardBack(float AxisValue);
	void MoveRightLeft(float AxisValue);

protected:	

	/*ќбъ€вл€ю компоненты спринг-арм и камера*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintreadOnly)
		float MoveSpeed = 100.0f;

	/*¬ этой переменной хранитс€ последнее полученное значение*/
	float MoveForwardBackInput = 0.f;
	float MoveRightLeftInput = 0.f;

};
