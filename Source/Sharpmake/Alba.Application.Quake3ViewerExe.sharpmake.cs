using Sharpmake;

[module: Sharpmake.Include("Alba.Base.ExecutableProject.sharpmake.cs")]

namespace Alba
{
    namespace Application
    {
        [Sharpmake.Generate]
        class Quake3ViewerExeProject : Alba.Base.ExecutableProject
        {
            public Quake3ViewerExeProject()
            {
                Name = "Quake3ViewerExe";
                SourceRootPath = @"[project.SharpmakeCsPath]\..\Application\Quake3ViewerExe";
            }

            [Configure()]
            public override void ConfigureAll(Configuration conf, Target target)
            {
                base.ConfigureAll(conf, target);

                conf.SolutionFolder = "Alba/Application";
                conf.ProjectPath = SourceRootPath;

                conf.IncludePaths.Add(SourceRootPath);
                conf.AddPrivateDependency<Alba.Demo.Quake3ViewerProject>(target);

                conf.Options.Add(Options.Vc.Linker.SubSystem.Application);
            }
        }
    }
}
