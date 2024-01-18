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

	AttackRange = 150.0f;
	AttackDamageMin = -2.5f;
	AttackDamageMax = 10.0f;
	AttackModifierMin = 0.85;
	AttackModifierMax = 1.25f;

}

float ASTWeapon::GetAttackRange() const
{
	return AttackRange;
}

float ASTWeapon::GetAttackDamage() const
{
	return AttackDamage;
}

float ASTWeapon::GetAttackModifier() const
{
	return AttackModifier;
}

// Called when the game starts or when spawned
void ASTWeapon::BeginPlay()
{
	Super::BeginPlay();

	AttackDamage = FMath::RandRange(AttackDamageMin, AttackDamageMax);
	AttackModifier = FMath::RandRange(AttackModifierMin, AttackModifierMax);

	STLOG(Warning, TEXT("Weapon Damage : %f, Modifier : %f"), AttackDamage, AttackModifier);
	
}

// Called every frame
void ASTWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

