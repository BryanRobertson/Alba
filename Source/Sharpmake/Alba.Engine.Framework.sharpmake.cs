using System.IO;
using Sharpmake;

[module: Sharpmake.Include("Alba.Base.Project.sharpmake.cs")]
[module: Sharpmake.Include("External.EASTL.sharpmake.cs")]

namespace Alba
{
    namespace Engine
    {
        [Sharpmake.Generate]
        class FrameworkProject : Alba.Base.LibraryProject
        {
            public FrameworkProject()
            {
                Name = "Framework";
                SourceRootPath = @"[project.SharpmakeCsPath]\..\Engine\Framework";
            }

            [Configure()]
            public override void ConfigureAll(Configuration conf, Target target)
            {
                base.ConfigureAll(conf, target);

                conf.SolutionFolder = "Alba/Engine";

                conf.AddPublicDependency<CoreProject>(target);
                conf.AddPublicDependency<GraphicsProject>(target);
            }
        }
    }
}