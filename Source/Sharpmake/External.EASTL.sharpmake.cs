using System.IO;
using Sharpmake;

namespace External
{
    namespace EASTL
    {
        [Sharpmake.Generate]
        class Project : Sharpmake.Project
        {
            public Project()
            {
                Name = "EASTL";
                SourceRootPath = Path.Combine(Alba.Settings.GetExternalLibraryPath("EASTL"), "source");
                IsFileNameToLower = false;

                AddTargets
                (
                    new Target
                    (
                        Alba.Settings.GetDefaultPlatforms(),
                        Alba.Settings.GetDefaultDevEnvs(),
                        Optimization.Debug | Optimization.Release | Optimization.Retail,
                        OutputType.Dll | OutputType.Lib
                    )
                );
            }

            [Configure()]
            public void ConfigureAll(Configuration conf, Target target)
            {
                conf.ProjectFileName = "[project.Name]_[target.Platform]_[target.DevEnv]";

                // Paths
                conf.ProjectPath = Alba.Settings.GetProjectPath();
                conf.IntermediatePath = Alba.Settings.GetIntermediatePath();
                conf.TargetPath = Alba.Settings.GetTargetPath();
                conf.TargetLibraryPath = Alba.Settings.GetLibraryTargetPath();

                conf.IncludePaths.Add(Path.Combine(Alba.Settings.GetExternalLibraryPath("EASTL"), "include"));
                conf.IncludePaths.Add(Path.Combine(Alba.Settings.GetExternalLibraryPath("EASTL"), "test", "packages", "EABase", "include", "Common"));

                if (target.Optimization == Optimization.Debug)
                {
                    conf.Defines.Add("DEBUG");
                }

                conf.Defines.Add("CHAR16T");
                conf.Defines.Add("CRT_SECURE_NO_WARNINGS");
                conf.Defines.Add("SCL_SECURE_NO_WARNINGS");
                conf.Defines.Add("EASTL_OPENSOURCE", "1");

                conf.Name = @"[target.Optimization] [target.OutputType]";
                conf.TargetFileName = "[project.Name]_[target.Platform]_[target.Optimization]";

                if (target.OutputType == OutputType.Dll)
                {
                    // We want this to output a shared library. (DLL)
                    conf.Output = Configuration.OutputType.Dll;

                    // This library project expects LIBRARY_DLL symbol to be defined
                    // when used as a DLL. While we could define it in the executable,
                    // it is better to put it as an exported define. That way, any
                    // projects with a dependency on this one will have LIBRARY_DLL
                    // automatically defined by Sharpmake.
                    conf.ExportDefines.Add("EASTL_DLL");

                    // Exported defines are not necessarily defines as well, so we need
                    // to add LIBRARY_DLL as an ordinary define too.
                    conf.Defines.Add("EASTL_DLL");
                }
                else if (target.OutputType == OutputType.Lib)
                {
                    // We want this to output a static library. (LIB)
                    conf.Output = Configuration.OutputType.Lib;
                }
            }
        }
    }
}