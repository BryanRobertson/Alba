using System.IO;
using Sharpmake;

[module: Sharpmake.Include("Alba.Base.LibraryProject.sharpmake.cs")]

namespace Alba
{
    namespace Demo
    {
        [Sharpmake.Generate]
        class Quake3ViewerProject : Alba.Base.LibraryProject
        {
            public Quake3ViewerProject()
            {
                Name = "Quake3Viewer";
                SourceRootPath = @"[project.SharpmakeCsPath]\..\Demo\Quake3Viewer";
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