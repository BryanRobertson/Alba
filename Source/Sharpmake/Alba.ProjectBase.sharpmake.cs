using System.IO;
using Sharpmake;

[module: Sharpmake.Include("Alba.Settings.sharpmake.cs")]

namespace Alba
{
	namespace Base
	{
        //-------------------------------------------------------------------------------------------------
        // Name	:	BaseProject
        // Desc	:	Base class for all projects
        //-------------------------------------------------------------------------------------------------
        abstract class BaseProject : Project
		{
			public BaseProject()
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
				if ( target.Optimization == Optimization.Debug )
				{
					conf.Defines.Add("ALBA_DEBUG_BUILD");
				}
				else if ( target.Optimization == Optimization.Release )
				{
					conf.Defines.Add("ALBA_RELEASE_BUILD");
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
			
                conf.Options.Add(Options.Vc.General.TreatWarningsAsErrors.Enable);
                conf.Options.Add(Options.Vc.General.WindowsTargetPlatformVersion.v10_0_15063_0);
				conf.Options.Add(new Sharpmake.Options.Vc.Compiler.DisableSpecificWarnings("4577"));
			}
		}

		//-------------------------------------------------------------------------------------------------
		// Name	:	LibraryProject
		// Desc	:	Base class for all library projects
		//-------------------------------------------------------------------------------------------------
		abstract class LibraryProject : BaseProject
		{
			public LibraryProject()
			{
				AddTargets
				(
					new Target
					(
                        GetDefaultPlatforms(),
                        GetDefaultDevEnvs(),
						Optimization.Debug | Optimization.Release | Optimization.Retail,
						OutputType.Dll | OutputType.Lib
					)
				);
			}

            public string GetLibraryDefine()
            {
                return string.Format("ALBA_{0}_LIBRARY_DLL", Name.ToUpper());
            }
			
			[Configure()]
			public override void ConfigureAll(Configuration conf, Target target)
			{
                base.ConfigureAll(conf, target);

                conf.Name = @"[target.Optimization] [target.OutputType]";

                if (target.OutputType == OutputType.Dll)
                {
                    // We want this to output a shared library. (DLL)
                    conf.Output = Configuration.OutputType.Dll;

                    // This library project expects LIBRARY_DLL symbol to be defined
                    // when used as a DLL. While we could define it in the executable,
                    // it is better to put it as an exported define. That way, any
                    // projects with a dependency on this one will have LIBRARY_DLL
                    // automatically defined by Sharpmake.
                    conf.ExportDefines.Add(GetLibraryDefine());

                    // Exported defines are not necessarily defines as well, so we need
                    // to add LIBRARY_DLL as an ordinary define too.
                    conf.Defines.Add(GetLibraryDefine());
                }
                else if (target.OutputType == OutputType.Lib)
                {
                    // We want this to output a static library. (LIB)
                    conf.Output = Configuration.OutputType.Lib;
                }
            }
		}

        //-------------------------------------------------------------------------------------------------
        // Name	:	ExecutableProject
        // Desc	:	Base class for all executable projects
        //-------------------------------------------------------------------------------------------------
        abstract class ExecutableProject : BaseProject
		{
			public ExecutableProject()
			{
				AddTargets
				(
					new Target
					(
                        GetDefaultPlatforms(),
                        GetDefaultDevEnvs(),
                        Optimization.Debug | Optimization.Release | Optimization.Retail
                    )
				);
			}
			
			[Configure()]
			public override void ConfigureAll(Configuration conf, Target target)
			{
				base.ConfigureAll(conf, target);
			}
		}
	}
	
	namespace Engine
	{
        //-------------------------------------------------------------------------------------------------
        // Name	:	LibraryProject
        // Desc	:	Base class for engine library projects
        //-------------------------------------------------------------------------------------------------
        abstract class LibraryProject : Base.LibraryProject
		{
			public LibraryProject()
			{
				
			}
			
			[Configure()]
			public override void ConfigureAll(Configuration conf, Target target)
			{
				base.ConfigureAll(conf, target);
			}
		}
	}
}