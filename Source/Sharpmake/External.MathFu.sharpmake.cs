using System.IO;
using Sharpmake;

[module: Sharpmake.Include("External.ProjectBase.sharpmake.cs")]

namespace External
{
    namespace MathFu
    {
        [Sharpmake.Generate]
        class Project : External.LibraryProject
        {
            private readonly string MathFuPath = Alba.Settings.GetExternalLibraryPath("MathFu");

            public Project()
            {
                Name = "MathFu";
            }

            public override string GetLibraryDefine()
            {
                return "";
            }

            [Configure()]
            public override void ConfigureAll(Configuration conf, Target target)
            {
                base.ConfigureAll(conf, target);

                //---------------------------------------------------------------------------------
                // Includes
                //---------------------------------------------------------------------------------
                conf.IncludePaths.Add(Path.Combine(MathFuPath, "include"));

                //---------------------------------------------------------------------------------
                // Defines
                //---------------------------------------------------------------------------------
                if (target.Optimization == Optimization.Debug)
                {
                    conf.Defines.Add("DEBUG");
                }

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