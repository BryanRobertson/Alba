using Sharpmake;

[module: Sharpmake.Include("Alba.Base.ExecutableProject.sharpmake.cs")]

namespace Alba
{
    namespace Application
    {
        [Sharpmake.Generate]
        class GravityDemoExeProject : Alba.Base.ExecutableProject
        {
            public GravityDemoExeProject()
            {
                Name = "GravityDemoExe";
                SourceRootPath = @"[project.SharpmakeCsPath]\..\Application\GravityDemoExe";
            }

            [Configure()]
            public override void ConfigureAll(Configuration conf, Target target)
            {
                base.ConfigureAll(conf, target);

                conf.SolutionFolder = "Alba/Application";
                conf.ProjectPath = SourceRootPath;

                conf.IncludePaths.Add(SourceRootPath);
                conf.AddPrivateDependency<Alba.Demo.GravityProject>(target);

                conf.Options.Add(Options.Vc.Linker.SubSystem.Application);
            }
        }
    }
}
