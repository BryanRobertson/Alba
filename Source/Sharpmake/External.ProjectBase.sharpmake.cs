using System.IO;
using Sharpmake;

namespace External
{
    //-------------------------------------------------------------------------------------------------
    // Name	:	BaseProject
    // Desc	:	Base class for all external projects
    //-------------------------------------------------------------------------------------------------
    abstract class BaseProject : Sharpmake.Project
    {
        public BaseProject()
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
            conf.SolutionFolder = "External Libraries";
        }
    }

    //-------------------------------------------------------------------------------------------------
	// Name	:	LibraryProject
	// Desc	:	Base class for all external library projects
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

        public abstract string GetLibraryDefine();

        [Configure()]
        public override void ConfigureAll(Configuration conf, Target target)
		{
            base.ConfigureAll(conf, target);

            conf.ProjectFileName = "[project.Name]_[target.Platform]_[target.DevEnv]";
            conf.Name = @"[target.Optimization] [target.OutputType]";

            conf.ProjectPath            = Alba.Settings.GetProjectPath();
            conf.IntermediatePath       = Alba.Settings.GetIntermediatePath();
            conf.TargetPath             = Alba.Settings.GetTargetPath();
            conf.TargetLibraryPath      = Alba.Settings.GetLibraryTargetPath();

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
}