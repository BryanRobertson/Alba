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

                //---------------------------------------------------------------------------------
                // Defines
                //---------------------------------------------------------------------------------

                // Disable EA's default implementation of sprintf
                conf.Defines.Add("EASTL_EASTDC_VSNPRINTF=false");

                if (target.Optimization == Optimization.Debug)
                {
                    conf.Defines.Add("ALBA_DEBUG_BUILD");

                    // Disable inlining entirely in debug builds
                    // (Reenable this when Sharpmake bug is fixed. Current version writes "Disable" instead of "Disabled"
                    // which breaks the project file)
                    //conf.Options.Add(Options.Vc.Compiler.Inline.Disable);
                }
                else if (target.Optimization == Optimization.Release)
                {
                    conf.Defines.Add("ALBA_RELEASE_BUILD");

                    // More inlining in release build
                    conf.Options.Add(Options.Vc.Compiler.Inline.OnlyInline);
                }
                else if (target.Optimization == Optimization.Retail)
                {
                    conf.Defines.Add("ALBA_RETAIL_BUILD");

                    // Full inlining
                    conf.Options.Add(Options.Vc.Compiler.Inline.AnySuitable);
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

                //---------------------------------------------------------------------------------
                //conf.Options.Add(Options.Vc.Linker.IgnoreAllDefaultLibraries.Enable);
                conf.Options.Add(Options.Vc.Compiler.CppLanguageStandard.CPP14);
                conf.Options.Add(Options.Vc.Compiler.Exceptions.EnableWithSEH);
                conf.Options.Add(Options.Vc.General.TreatWarningsAsErrors.Enable);
                conf.Options.Add(Alba.Settings.WindowsTargetPlatformVersion);
                conf.Options.Add(new Sharpmake.Options.Vc.Compiler.DisableSpecificWarnings("4577"));
            }
		}
	}
}