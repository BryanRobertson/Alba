using System.IO;
using Sharpmake;

[module: Sharpmake.Include("Alba.Common.Settings.sharpmake.cs")]

namespace Alba
{
	namespace Base
	{
        //-------------------------------------------------------------------------------------------------
        // Name	:	Project
        // Desc	:	Base class for all projects
        //-------------------------------------------------------------------------------------------------
        abstract class Project : Sharpmake.Project
		{
			public Project()
                : base(typeof(Target))
            {
                IsFileNameToLower = false;
            }

            public static Platform GetDefaultPlatforms()
            {
                return Alba.Settings.GetDefaultPlatforms();
            }

            public static DevEnv GetDefaultDevEnvs()
            {
                return Alba.Settings.GetDefaultDevEnvs();
            }

            [Configure()]
			public virtual void ConfigureAll(Configuration conf, Target target)
			{
				// Project filename
				conf.ProjectFileName = "[project.Name]_[target.Platform]_[target.DevEnv]";

                // Paths
                conf.ProjectPath        = Alba.Settings.GetProjectPath();
                conf.IntermediatePath   = Alba.Settings.GetIntermediatePath();
                conf.TargetPath         = Alba.Settings.GetTargetPath();
                conf.TargetLibraryPath  = Alba.Settings.GetLibraryTargetPath();
                conf.TargetFileName     = "[project.Name]_[target.Platform]_[target.Optimization]";

                // If not set, no precompile option will be used.
                conf.PrecompHeader = "[project.Name]_Precompile.hpp";
				conf.PrecompSource = "[project.Name]_Precompile.cpp";

                // Defines
                if (target.Optimization == Optimization.Debug)
                {
                    conf.Defines.Add("ALBA_DEBUG_BUILD");
                }
                else if (target.Optimization == Optimization.Release)
                {
                    conf.Defines.Add("ALBA_RELEASE_BUILD");
                }
                else if (target.Optimization == Optimization.Retail)
                {
                    conf.Defines.Add("ALBA_RETAIL_BUILD");
                }
				
				if ( target.Platform == Platform.win32 || target.Platform == Platform.win64 )
				{
					conf.Defines.Add("ALBA_PLATFORM_WINDOWS");
					
					if ( target.Platform == Platform.win32 )
					{
						conf.Defines.Add("ALBA_ARCHITECTURE_32BIT");
					}
					else if (target.Platform == Platform.win64 )
					{
						conf.Defines.Add("ALBA_ARCHITECTURE_64BIT");
					}
				}

                conf.Options.Add(Options.Vc.Compiler.CppLanguageStandard.CPP14);
                conf.Options.Add(Options.Vc.Compiler.Exceptions.EnableWithSEH);
                conf.Options.Add(Options.Vc.General.TreatWarningsAsErrors.Enable);
                conf.Options.Add(Options.Vc.General.WindowsTargetPlatformVersion.v10_0_15063_0);
                conf.Options.Add(new Sharpmake.Options.Vc.Compiler.DisableSpecificWarnings("4577"));
			}
		}
	}
}