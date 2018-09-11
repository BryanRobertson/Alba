using Sharpmake;

[module: Sharpmake.Include("Alba.Base.ExecutableProject.sharpmake.cs")]
[module: Sharpmake.Include("Alba.Tests.AlbaTest.sharpmake.cs")]

namespace Alba
{
    namespace Tests
    {
        [Sharpmake.Generate]
        class AlbaTestExeProject : Alba.Base.ExecutableProject
        {
            public AlbaTestExeProject()
            {
                Name = "AlbaTestExe";
                SourceRootPath = @"[project.SharpmakeCsPath]\..\Tests\AlbaTestExe";
            }

            [Configure()]
            public override void ConfigureAll(Configuration conf, Target target)
            {
                base.ConfigureAll(conf, target);

                conf.SolutionFolder = "Alba/Tests";
                conf.ProjectPath = SourceRootPath;

                conf.IncludePaths.Add(SourceRootPath);
				
                conf.AddPrivateDependency<Alba.Tests.AlbaTestProject>(target);

                conf.Options.Add(Options.Vc.Linker.SubSystem.Console);
            }
        }
    }
}
