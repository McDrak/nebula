// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Nebula : ModuleRules
{
	public Nebula(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
