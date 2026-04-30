// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class M9_2 : ModuleRules
{
	public M9_2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "AIModule" });
	}
}
