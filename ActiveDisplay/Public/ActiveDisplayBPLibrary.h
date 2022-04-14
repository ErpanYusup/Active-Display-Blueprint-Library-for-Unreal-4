
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine.h"
#include "SWindow.h" // For Newer Version of Unreal, Use Widgets/SWindow.h
#include "ActiveDisplayBPLibrary.generated.h"

/* 
*	Function library class to change active display for your game.
*	If Functions are not working correctly or it's outdated. Please email me.
*	
*	Authur: Erpan "Wolf" Yusup
*   Creation Date: 05 / 06 / 2019
*   Last Edit Date: 05/ 06 / 2019
*	Email: Erpan9354@hotmail.com
*	Website: https://www.erpan.me
*/

/*
*  LOG
*  05/ 06 / 2019 : Created Active Display Library
*
*/


UCLASS(config=GAME)
class UActiveDisplayBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY() // For Newer Version of Unreal, Use GENERATED_BODY() instead

public:
	//Set Current Game Display to Specific Monitor Index from input value, return true if successful, return false if input is out of index range.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set To Active Display", Keywords = "Monitor, Display, Screen"), Category = "Active Display")
	static bool SetToActiveDisplay(int32 Index);

	//Get number of current active Monitor count.
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Active Display Number(s)", Keywords = "Monitor, Display, Screen"), Category = "Active Display")
	static int32 GetActiveDisplay();

	//Cycle to next active monitor, go back to 0 at the end.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Cycle To Next Display", Keywords = "Monitor, Display, Screen"), Category = "Active Display")
		static int32 CycleToNextDisplay(int32 Index);

protected:

	static void AdjustGameResolution(FDisplayMetrics Display, FMonitorInfo Monitor);

	static void SetDisplay(FMonitorInfo Monitor);

	class UGameUserSettings* Settings;
};
