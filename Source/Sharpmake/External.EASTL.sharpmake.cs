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
            private readonly string EASTLPath = Alba.Settings.GetExternalLibraryPath("EASTL");

            public Project()
            {
                Name = "EASTL";
                     
                SourceRootPath = Path.Combine(EASTLPath, "source");
                AdditionalSourceRootPaths.Add(Path.Combine(EASTLPath, "include"));
                NatvisFiles.Add(Path.Combine(EASTLPath, "doc", "EASTL.natvis"));
            }

            public override string GetLibraryDefine()
            {
                return "EASTL_DLL";
            }

            [Configure()]
            public override void ConfigureAll(Configuration conf, Target target)
            {
                base.ConfigureAll(conf, target);

                //---------------------------------------------------------------------------------
                // Includes
                //---------------------------------------------------------------------------------
                conf.IncludePaths.Add(Path.Combine(EASTLPath, "include"));
                conf.IncludePaths.Add(Path.Combine(EASTLPath, "test", "packages", "EABase", "include", "Common"));

                //---------------------------------------------------------------------------------
                // Defines
                //---------------------------------------------------------------------------------
                if (target.Optimization == Optimization.Debug)
                {
                    conf.Defines.Add("DEBUG");
                }

                conf.Defines.Add("CHAR16T");
                conf.Defines.Add("CRT_SECURE_NO_WARNINGS");
                conf.Defines.Add("SCL_SECURE_NO_WARNINGS");
                conf.Defines.Add("EASTL_OPENSOURCE=1");

                // Disable EA's default implementation of sprintf
                conf.Defines.Add("EASTL_EASTDC_VSNPRINTF=false");

                //---------------------------------------------------------------------------------
                // Options
                //---------------------------------------------------------------------------------
                conf.Options.Add(Options.Vc.Compiler.CppLanguageStandard.CPP11);
                conf.Options.Add(Options.Vc.Compiler.Exceptions.EnableWithSEH);
                conf.Options.Add(Options.Vc.General.TreatWarningsAsErrors.Enable);
            }
        }
    }
}