// Fill out your copyright notice in the Description page of Project Settings.


#include "STWeapon.h"

// Sets default values
ASTWeapon::ASTWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	/// Script / Engine.SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight'
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Weapon(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight"));

	if (SK_Weapon.Succeeded())
	{
		Weapon->SetSkeletalMesh(SK_Weapon.Object);
	}

	Weapon->SetCollisionProfileName(TEXT("NoCollision"));




}

// Called when the game starts or when spawned
void ASTWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

