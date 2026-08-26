// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Gameplay/YCNPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

void AYCNPlayerController::OnPossess(APawn* PawnToPossess)
{
	Super::OnPossess(PawnToPossess);

	TArray<AActor*>AllCamera;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), FName("Default"), AllCamera);

	if (!AllCamera.IsEmpty())
	{
		//将根据标签获取来的摄像机设置给视图目标
		SetViewTarget(AllCamera[0]);
	}
}
