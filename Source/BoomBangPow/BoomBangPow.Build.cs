// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BoomBangPow : ModuleRules
{
	public BoomBangPow(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" , "EnhancedInput", "UMG", "AIModule", "GameplayTasks", "NavigationSystem"});

		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
