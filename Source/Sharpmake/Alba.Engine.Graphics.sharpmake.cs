using System.IO;
using Sharpmake;

[module: Sharpmake.Include("Alba.Base.LibraryProject.sharpmake.cs")]
[module: Sharpmake.Include("External.EASTL.sharpmake.cs")]

namespace Alba
{
    namespace Engine
    {
        [Sharpmake.Generate]
        class GraphicsProject : Alba.Base.LibraryProject
        {
            public GraphicsProject()
            {
                Name = "Graphics";
                SourceRootPath = @"[project.SharpmakeCsPath]\..\Engine\Graphics";
            }

            [Configure()]
            public override void ConfigureAll(Configuration conf, Target target)
            {
                base.ConfigureAll(conf, target);

                conf.SolutionFolder = "Alba/Engine";
                conf.ProjectPath = SourceRootPath;

                conf.IncludePaths.Add(SourceRootPath);
                conf.IncludePaths.Add(Alba.Settings.GetExternalLibraryPath("imgui"));

                if (target.Platform == Platform.win64)
                {
                    conf.LibraryFiles.Add("d3d11");
                    conf.LibraryFiles.Add("D3DCompiler");
                    //conf.LibraryFiles.Add("d3dx11");
                }

                conf.AddPublicDependency<CoreProject>(target);
            }
        }
    }
}