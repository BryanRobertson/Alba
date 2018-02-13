using System.IO;
using Sharpmake;

[module: Sharpmake.Include("Alba.ProjectBase.sharpmake.cs")]

namespace Alba
{
	[Sharpmake.Generate]
	class CoreProject : Alba.Engine.LibraryProject
	{
		public CoreProject()
		{
			Name = "Core";
			SourceRootPath = @"[project.SharpmakeCsPath]\..\Engine\Core";
		}

        [Configure()]
		public override void ConfigureAll(Configuration conf, Target target)
		{
            base.ConfigureAll(conf, target);
			conf.IncludePaths.Add(SourceRootPath);
		}
	}

}