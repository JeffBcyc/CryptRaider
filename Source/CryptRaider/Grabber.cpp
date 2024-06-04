// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Got Physics Handle: %s"), *PhysicsHandle->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Physics Handle Found!"));
	}

}



// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	

}

void UGrabber::ReleaseGrab()
{
	UE_LOG(LogTemp, Log, TEXT("Grab Released"));
	UE_LOG(LogBlueprintUserMessages, Log,TEXT("Grab Released"));
	UKismetSystemLibrary::PrintString(GetWorld(), "E Button Released");
}

void UGrabber::Grab()
{
	UKismetSystemLibrary::PrintString(GetWorld(), "E Button Pressed");
	FVector StartLine = GetComponentLocation();
	FVector EndLine = (StartLine + GetForwardVector() * LineLength);
	DrawDebugLine(GetWorld(), StartLine, EndLine, FColor::Red);
	DrawDebugSphere(GetWorld(),EndLine, 10, 10, FColor::Blue, true, 5);
	
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult HitResult;
	
	
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult,
		StartLine, EndLine,FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere);
	if (HasHit)
	{
		UE_LOG(LogTemp, Log, TEXT("%s has been hit by player"), *HitResult.GetActor()->GetActorNameOrLabel());
	}
	
}

