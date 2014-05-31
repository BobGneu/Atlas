// Copyright 2013 Gneu, LLC. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class Atlas : ModuleRules
{
    public Atlas(TargetInfo Target)
    {
        PrivateIncludePaths.AddRange(new string[] 
        { 
            Path.Combine("Atlas", "Private") 
        });
        
        PublicIncludePaths.AddRange(new string[] 
        { 
            Path.Combine("Atlas", "Public") 
        });

        PublicDependencyModuleNames.AddRange(new string[] 
        { 
            "Engine", 
            "Core", 
            "HTTP"
        });

        Definitions.Add("WITH_ATLAS=1");
    }
}
