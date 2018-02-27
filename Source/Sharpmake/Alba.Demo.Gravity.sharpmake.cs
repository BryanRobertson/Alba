using System.IO;
using Sharpmake;

[module: Sharpmake.Include("Alba.Base.LibraryProject.sharpmake.cs")]

namespace Alba
{
    namespace Demo
    {
        [Sharpmake.Generate]
        class GravityProject : Alba.Base.LibraryProject
        {
            public GravityProject()
            {
                Name = "Gravity";
                SourceRootPath = @"[project.SharpmakeCsPath]\..\Demo\Gravity";
            }

            [Configure()]
            public override void ConfigureAll(Configuration conf, Target target)
            {
                base.ConfigureAll(conf, target);

                conf.SolutionFolder = "Alba/Demo";
                conf.ProjectPath = SourceRootPath;

                conf.IncludePaths.Add(SourceRootPath);
                conf.AddPublicDependency<Alba.Engine.FrameworkProject>(target);
            }
        }
    }
}