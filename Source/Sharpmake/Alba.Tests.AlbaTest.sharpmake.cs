using System.IO;
using Sharpmake;

[module: Sharpmake.Include("Alba.Base.LibraryProject.sharpmake.cs")]

namespace Alba
{
    namespace Tests
    {
        [Sharpmake.Generate]
        class AlbaTestProject : Alba.Base.LibraryProject
        {
            public AlbaTestProject()
            {
                Name = "AlbaTest";
                SourceRootPath = @"[project.SharpmakeCsPath]\..\Tests\AlbaTest";
            }

            [Configure()]
            public override void ConfigureAll(Configuration conf, Target target)
            {
                base.ConfigureAll(conf, target);

                conf.SolutionFolder = "Alba/Tests";

                conf.AddPublicDependency<Alba.Engine.FrameworkProject>(target);
            }
        }
    }
}