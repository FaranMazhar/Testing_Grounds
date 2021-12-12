// Developed by Scythe for testing purposes.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

class UCameraComponent;
class AGun;
class USkeletalMeshComponent;

UCLASS()
class TESTINGGROUNDS_API AMannequin : public ACharacter
{
	GENERATED_BODY()

		
public:
	// Sets default values for this character's properties
	AMannequin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AGun> GunBlueprint;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		AGun* Gun;

};
