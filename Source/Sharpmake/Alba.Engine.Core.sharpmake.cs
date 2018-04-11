using System.IO;
using Sharpmake;

[module: Sharpmake.Include("Alba.Base.LibraryProject.sharpmake.cs")]
[module: Sharpmake.Include("External.EASTL.sharpmake.cs")]

namespace Alba
{
    namespace Engine
    {
        [Sharpmake.Generate]
        class CoreProject : Alba.Base.LibraryProject
        {
            public CoreProject()
            {
                Name = "Core";
                SourceRootPath = @"[project.SharpmakeCsPath]\..\Engine\Core";
            }

            [Configure()]
            public override void ConfigureAll(Configuration conf, Target target)
            {
                base.ConfigureAll(conf, target);

                conf.SolutionFolder = "Alba/Engine";
                conf.ProjectPath = SourceRootPath;

                conf.IncludePaths.Add(SourceRootPath);
                conf.IncludePaths.Add(Alba.Settings.GetExternalLibraryPath("eigen"));

                conf.AddPublicDependency<External.EASTL.Project>(target);
            }
        }
    }
}