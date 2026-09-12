// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Gameplay/YCNPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "UIDemo/Settings/YCNGameUserSettings.h"

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

	UYCNGameUserSettings* GameUserSettings = UYCNGameUserSettings::Get();
	if (!GameUserSettings)return;

	if (GameUserSettings->GetLastCPUBenchmarkResult() == -1.f || GameUserSettings->GetLastGPUBenchmarkResult() == -1.f)
	{
		GameUserSettings->RunHardwareBenchmark();
		GameUserSettings->ApplyHardwareBenchmarkResults();
	}
}
