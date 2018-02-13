using System.IO;
using Sharpmake;

[module: Sharpmake.Include("External.ProjectBase.sharpmake.cs")]

namespace External
{
    namespace EASTL
    {
        [Sharpmake.Generate]
        class Project : External.LibraryProject
        {
            public Project()
            {
                Name = "EASTL";
                SourceRootPath = Path.Combine(Alba.Settings.GetExternalLibraryPath("EASTL"), "source");
            }

            public override string GetLibraryDefine()
            {
                return "EASTL_DLL";
            }

            [Configure()]
            public override void ConfigureAll(Configuration conf, Target target)
            {
                base.ConfigureAll(conf, target);

                conf.IncludePaths.Add(Path.Combine(Alba.Settings.GetExternalLibraryPath("EASTL"), "include"));
                conf.IncludePaths.Add(Path.Combine(Alba.Settings.GetExternalLibraryPath("EASTL"), "test", "packages", "EABase", "include", "Common"));

                if (target.Optimization == Optimization.Debug)
                {
                    conf.Defines.Add("DEBUG");
                }

                conf.Defines.Add("CHAR16T");
                conf.Defines.Add("CRT_SECURE_NO_WARNINGS");
                conf.Defines.Add("SCL_SECURE_NO_WARNINGS");
                conf.Defines.Add("EASTL_OPENSOURCE", "1");
            }
        }
    }
}