

#pragma once

#include "CoreMinimal.h"
#include "COABaseCharacter.h"
#include "COAAvatar.generated.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

/**
 * 
 */
UCLASS()
class GAD2006_API ACOAAvatar : public ACOABaseCharacter
{
    GENERATED_BODY()

public:

    ACOAAvatar();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
    UCameraComponent* mCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
    USpringArmComponent* mSpringArm;


    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float value);
    void MoveRight(float value);
}

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
float Stamina;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
float MaxStamina;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
float StaminaGainRate;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
float StaminaDrainRate;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
float RunSpeed;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
float WalkSpeed;

UPROPERTY(BlueprintReadOnly, Category = "Stamina")
bool bStaminaDrained;

UPROPERTY(BlueprintReadOnly, Category = "Stamina")
bool bRunning;

void UpdateMovementParams();

void RunPressed();
void RunReleased();

