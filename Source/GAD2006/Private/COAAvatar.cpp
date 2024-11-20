



#include "CoreMinimal.h"
#include "COAAvatar.h"
#include "COAAvatar.generated.h"

ACOAAvatar::ACOAAvatar()
{
    Stamina = 100.0f;
    MaxStamina = 100.0f;
    StaminaGainRate = 10.0f;
    StaminaDrainRate = 5.0f;
    RunSpeed = 600.0f;
    bStaminaDrained = false;
    bRunning = false;
}

ACOAAvatar::ACOAAvatar()

{
    mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    mSpringArm->TargetArmLength = 300.0f;
    mSpringArm->SetupAttachment(RootComponent);
   

    mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
    mCamera->SetupAttachment(mSpringArm, USpringArmComponent::SocketName);
    

    mCamera->bUsePawnControlRotation = false;
    mSpringArm->bUsePawnControlRotation = true;
    bUseControllerRotationYaw = false;

}
void ACOAAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);

    PlayerInputComponent->BindAxis("MoveForward", this, &ACOAAvatar::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ACOAAvatar::MoveRight);

}
void ACOAAvatar::MoveForward(float Value)
{
    FRotator Rotation = GetController()->GetControlRotation();
    FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

    FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(ForwardDirection, Value);
}

void ACOAAvatar::MoveRight(float Value)
{
    FRotator Rotation = GetController()->GetControlRotation();
    FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

    FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    AddMovementInput(RightDirection, Value);
}

void ACOAAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);

    PlayerInputComponent->BindAxis("MoveForward", this, &ACOAAvatar::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ACOAAvatar::MoveRight);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACOAAvatar::RunPressed);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ACOAAvatar::RunReleased);
}

void ACOAAvatar::RunPressed()
{
    GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ACOAAvatar::RunReleased()
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ACOAAvatar::UpdateMovementParams()
{
    if (bStaminaDrained)
    {
        GetCharacterMovement()->MaxWalkSpeed = 300.0f; 
    }
    else if (bRunning)
    {
        GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = 300.0f;
    }
}
void ACOAAvatar::RunPressed()
{
    if (!bStaminaDrained) 
    {
        bRunning = true;
        UpdateMovementParams();
    }
}
void ACOAAvatar::RunReleased()
{
    bRunning = false;
    UpdateMovementParams();
}

void ACOAAvatar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bRunning && !bStaminaDrained)
    {
        Stamina -= StaminaDrainRate * DeltaTime;
        if (Stamina <= 0.0f)
        {
            Stamina = 0.0f;
            bStaminaDrained = true;
            bRunning = false;
            UpdateMovementParams();
        }
    }
    else
    {
        Stamina += StaminaGainRate * DeltaTime;
        if (Stamina >= MaxStamina)
        {
            Stamina = MaxStamina;
            bStaminaDrained = false;
        }
    }
}