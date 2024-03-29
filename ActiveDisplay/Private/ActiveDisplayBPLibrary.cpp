// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ActiveDisplayBPLibrary.h"

/*
* Set Display to user input index display
* Param(s): FDisplayMetric -- DisplayMetricStrut || Index -- int index number of the display you wish to set your game for
* Return  : True if Index is valid, false if not.
*/
bool UActiveDisplayBPLibrary::SetToActiveDisplay(int32 Index)
{
	//Get Display Metrics;
	FDisplayMetrics Display;
	FDisplayMetrics::RebuildDisplayMetrics(Display);



	// return false if user input exceed range of active monitors.
	if (Index > Display.MonitorInfo.Num() || !Display.MonitorInfo.IsValidIndex(Index))
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, TEXT("Input Index is out of range or Invalid"));
		return false;
	}
	else
	{
		//Get User Desired Monitor Info. 
		const FMonitorInfo Monitor = Display.MonitorInfo[Index];

		AdjustGameResolution(Display, Monitor);

		SetDisplay(Monitor);
		
		
	}

	return true;
}


/*
* Get Number of Currently Active Display
* Param(s): None
* Return  : Number of active Display (if you have 2 monitor running, it will return 2, vice versa)
*/
int32 UActiveDisplayBPLibrary::GetActiveDisplay()
{
	FDisplayMetrics Display;
	FDisplayMetrics::RebuildDisplayMetrics(Display);

	return Display.MonitorInfo.Num();
}


/*
* Cycle to next monitor, return to first monitor if it hit the end of the list
* Param(s): CurrentIndex -- CurrentMonitorIndex
* Return  : NextDisplay Index
*/
int32 UActiveDisplayBPLibrary::CycleToNextDisplay(int32 CurrentIndex)
{
	FDisplayMetrics Display;
	FDisplayMetrics::RebuildDisplayMetrics(Display);

	int32 TargetIndex = CurrentIndex;
	if (!Display.MonitorInfo.IsValidIndex(TargetIndex + 1))
	{
		TargetIndex = 0;
	}
	else
	{
		TargetIndex = CurrentIndex + 1;
	}

	//Get User Desired Monitor Info. 
	const FMonitorInfo Monitor = Display.MonitorInfo[TargetIndex];


	AdjustGameResolution(Display, Monitor);

	SetDisplay(Monitor);

	return TargetIndex;
}

/*
* AdjustGameResolution if target Monitor does not support game resolution
* Param(s): Display -- displayMerics struct || Monitor -- MonitorInfo Struct
* Return  : None
*/
void UActiveDisplayBPLibrary::AdjustGameResolution(FDisplayMetrics Display, FMonitorInfo Monitor)
{



	//Get Current Game Resolution Setting.
	FVector2D UserResoSetting = FVector2D(1, 1);

	UserResoSetting.X = GSystemResolution.ResX;
	UserResoSetting.Y = GSystemResolution.ResY;

	//Check if target monitor doesn't support games resolution
	if (UserResoSetting.X > Monitor.NativeWidth || UserResoSetting.Y > Monitor.NativeHeight)
	{
		//Set game resolution to match target monitor resolution.

		UGameUserSettings* Settings = GEngine->GameUserSettings;

		//return false if setting is invalid
		if (!Settings)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, TEXT("Getting Game Setting Failed"));
		}

		TSharedPtr<SWindow> Window = GEngine->GameViewport->GetWindow();
		const EWindowMode::Type CurrentWindowMode = Window->GetWindowMode();
		Settings->RequestResolutionChange(Monitor.NativeWidth, Monitor.NativeHeight, CurrentWindowMode, false);
	}


}


/*
* Set game display to target display
* Param(s): Monitor -- MonitorInfo Struct
* Return  : None
* Works Both in Windows and Linux OS
*/
void UActiveDisplayBPLibrary::SetDisplay(FMonitorInfo Monitor)
{
	const int32 WindowPosX = Monitor.WorkArea.Left;
	const int32 WindowPosY = Monitor.WorkArea.Top;
	const FVector2D Position(static_cast<float>(WindowPosX), static_cast<float>(WindowPosY));

	if (GEngine && GEngine->GameViewport)
	{
		TSharedPtr<SWindow> Window = GEngine->GameViewport->GetWindow();

		// Hack for Linux
	#if PLATFORM_LINUX
		const EWindowMode::Type CurrentWindowMode = Window->GetWindowMode();
		Window->SetWindowMode(EWindowMode::Windowed);
	#endif

		Window->MoveWindowTo(Position);

	#if PLATFORM_LINUX
		// Set back to original
		Window->SetWindowMode(CurrentWindowMode);
	#endif
	}
}

