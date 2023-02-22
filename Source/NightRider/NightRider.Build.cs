// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NightRider : ModuleRules
{
	public NightRider(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Slate", "SlateCore", "WorldBuilderModule" });

        PublicDependencyModuleNames.AddRange(new string[] { "Json", "JsonUtilities" });

        OptimizeCode = CodeOptimization.Never;
    }
}
