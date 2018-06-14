using System.IO;
using Sharpmake;

[module: Sharpmake.Include("Alba.Base.LibraryProject.sharpmake.cs")]
//[module: Sharpmake.Include("External.MathFu.sharpmake.cs")]

namespace Alba
{
    namespace Engine
    {
        [Sharpmake.Generate]
        class MathProject : Alba.Base.LibraryProject
        {
            private readonly string MathFuPath = Alba.Settings.GetExternalLibraryPath("MathFu");

            public MathProject()
            {
                Name = "Math";
                SourceRootPath = @"[project.SharpmakeCsPath]\..\Engine\Math";
            }

            [Configure()]
            public override void ConfigureAll(Configuration conf, Target target)
            {
                base.ConfigureAll(conf, target);

                conf.SolutionFolder = "Alba/Engine";
                conf.ProjectPath = SourceRootPath;

                //---------------------------------------------------------------------------------
                // Includes
                //---------------------------------------------------------------------------------
                conf.IncludePaths.Add(Path.Combine(MathFuPath, "include"));
                conf.IncludePaths.Add(SourceRootPath);

                //conf.AddPublicDependency<External.MathFu.Project>(target);
            }
        }
    }
}