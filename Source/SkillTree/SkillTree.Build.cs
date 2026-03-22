// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SkillTree : ModuleRules
{
	public SkillTree(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"SkillTree",
			"SkillTree/Variant_Platforming",
			"SkillTree/Variant_Platforming/Animation",
			"SkillTree/Variant_Combat",
			"SkillTree/Variant_Combat/AI",
			"SkillTree/Variant_Combat/Animation",
			"SkillTree/Variant_Combat/Gameplay",
			"SkillTree/Variant_Combat/Interfaces",
			"SkillTree/Variant_Combat/UI",
			"SkillTree/Variant_SideScrolling",
			"SkillTree/Variant_SideScrolling/AI",
			"SkillTree/Variant_SideScrolling/Gameplay",
			"SkillTree/Variant_SideScrolling/Interfaces",
			"SkillTree/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
