using System.IO;
using Sharpmake;

[module: Sharpmake.Include("Alba.Common.Settings.sharpmake.cs")]
[module: Sharpmake.Include("Alba.Base.Project.sharpmake.cs")]

namespace Alba
{
    namespace Base
    {
        //-------------------------------------------------------------------------------------------------
        // Name	:	ExecutableProject
        // Desc	:	Base class for all executable projects
        //-------------------------------------------------------------------------------------------------
        abstract class ExecutableProject : Project
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
                conf.ProjectPath = SourceRootPath;
                conf.IncludePaths.Add(SourceRootPath);

                base.ConfigureAll(conf, target);
            }
        }
    }
}