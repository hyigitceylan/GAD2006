

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "COABaseCharacter.generated.h"

UCLASS()
class GAD2006_API ACOABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACOABaseCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
	bool bDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
	float HealingRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
	float WalkSpeed;


protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

private:

	void MoveForward(float value);
	void MoveRight(float value);
	void RunPressed();
	void RunReleased();

	


};
