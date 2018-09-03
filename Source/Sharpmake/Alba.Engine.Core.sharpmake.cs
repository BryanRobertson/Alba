using System.IO;
using Sharpmake;

[module: Sharpmake.Include("Alba.Base.LibraryProject.sharpmake.cs")]
[module: Sharpmake.Include("Alba.Engine.Math.sharpmake.cs")]
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
                
                conf.IncludePaths.Add(Alba.Settings.GetExternalLibraryPath("eigen"));
                conf.IncludePaths.Add(Alba.Settings.GetExternalLibraryPath(Path.Combine("remotery", "lib")));

				conf.AddPublicDependency<Alba.Engine.MathProject>(target);
                conf.AddPublicDependency<External.EASTL.Project>(target);
            }
        }
    }
}