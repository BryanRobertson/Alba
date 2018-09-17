using System.IO;
using Sharpmake;

[module: Sharpmake.Include("Alba.Base.Project.sharpmake.cs")]
[module: Sharpmake.Include("External.EASTL.sharpmake.cs")]

namespace Alba
{
    namespace Engine
    {
        [Sharpmake.Generate]
        class InputProject : Alba.Base.LibraryProject
        {
            public InputProject()
            {
                Name = "Input";
                SourceRootPath = @"[project.SharpmakeCsPath]\..\Engine\Input";
            }

            [Configure()]
            public override void ConfigureAll(Configuration conf, Target target)
            {
                base.ConfigureAll(conf, target);

                conf.SolutionFolder = "Alba/Engine";

                conf.AddPublicDependency<CoreProject>(target);
            }
        }
    }
}