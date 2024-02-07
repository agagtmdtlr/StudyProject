// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class StudyProject : ModuleRules
{
	public StudyProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG","NavigationSystem", "AIModule" , "GameplayTasks"});

		PublicDependencyModuleNames.AddRange(new string[] { "EnhancedInput", "GeometryCore", "Niagara"});


		PrivateDependencyModuleNames.AddRange(new string[] {  "StudyProjectSetting" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
