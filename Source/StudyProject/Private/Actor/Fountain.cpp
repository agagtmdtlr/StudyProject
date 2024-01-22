// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Fountain.h"
#include "StudyProject.h"
// Sets default values
AFountain::AFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	_water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WATER"));

	_light = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT"));
	_splash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SPLASH"));

	_rotateMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("MOVEMENT"));
	_rotateSpeed = 30.0f;
	FRotator rotator(0.0f, _rotateSpeed , 0.0f);
	_rotateMovement->RotationRate = rotator;


	RootComponent = _body;
	_water->SetupAttachment(_body.Get());
	_light->SetupAttachment(_body.Get());
	_splash->SetupAttachment(_body.Get());

	_water->SetRelativeLocation(FVector(0.0f, 0.0f, 145.0f));

	_light->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f));
	_splash->SetRelativeLocation(FVector(0.0f, 0.0f, 145.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Ruins/StaticMesh/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01"));
	if (SM_Body.Succeeded())
	{
		_body->SetStaticMesh(SM_Body.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Water(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Meshes/Env/SM_Plains_Fountain_02.SM_Plains_Fountain_02"));
	if (SM_Water.Succeeded())
	{
		_water->SetStaticMesh(SM_Water.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_Splash(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Ambient/Water/P_Water_Fountain_Splash_Base_01.P_Water_Fountain_Splash_Base_01"));
	if (PS_Splash.Succeeded())
	{
		_splash->SetTemplate(PS_Splash.Object);
	}	

}

// Called when the game starts or when spawned
void AFountain::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(StudyProject, Warning, TEXT("Actor Name : %s, ID : %d, Location X : %.3f"), *GetName(), _id, GetActorLocation().X);

	STLOG_S(Warning);
	STLOG(Warning, TEXT("Actor Name : %s, ID : %d, Location X : %.3f"), *GetName(), _id, GetActorLocation().X);

	// check(false); // exit
	// not exit
	//ensure(false);
}

void AFountain::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	STLOG_S(Warning);
}

void AFountain::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	STLOG_S(Warning);
}

// Called every frame
void AFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	//FRotator rotator(0.0f, _rotateSpeed * DeltaTime, 0.0f);
	//AddActorLocalRotation(rotator);

}

