using System.IO;
using Sharpmake;

[module: Sharpmake.Include("Alba.Base.Project.sharpmake.cs")]
[module: Sharpmake.Include("Alba.Engine.Core.sharpmake.cs")]
[module: Sharpmake.Include("Alba.Engine.Graphics.sharpmake.cs")]
[module: Sharpmake.Include("Alba.Engine.Framework.sharpmake.cs")]
[module: Sharpmake.Include("Alba.Demo.Gravity.sharpmake.cs")]
[module: Sharpmake.Include("Alba.Application.GravityDemoExe.sharpmake.cs")]
[module: Sharpmake.Include("Alba.Common.Settings.sharpmake.cs")]
[module: Sharpmake.Include("External.Solution.sharpmake.cs")]

namespace Alba
{
    [Sharpmake.Generate]
    public class Solution : Sharpmake.Solution
    {
        public Solution()
        {
            // The name of the solution.
            Name = "Alba";

            IsFileNameToLower = false;

            // As with the project, define which target this solution builds for.
            // It's usually the same thing.
            AddTargets
		    (
			    new Target
			    (
                    GetDefaultPlatforms(),
                    GetDefaultDevEnvs(),
                    Optimization.Debug | Optimization.Release | Optimization.Retail
                )
		    );
        }

        public static Platform GetDefaultPlatforms()
        {
            return Alba.Settings.GetDefaultPlatforms();
        }

        public static DevEnv GetDefaultDevEnvs()
        {
            return Alba.Settings.GetDefaultDevEnvs();
        }

        [Configure]
        public void ConfigureAll(Solution.Configuration conf, Target target)
        {
            conf.SolutionFileName = "[solution.Name]_[target.Platform]_[target.DevEnv]";
		    conf.SolutionPath = @"[solution.SharpmakeCsPath]\generated";

            //-------------------------------------------------------------------------------------
            // Engine
            //-------------------------------------------------------------------------------------
            conf.AddProject<Alba.Engine.CoreProject>(target);
            conf.AddProject<Alba.Engine.FrameworkProject>(target);
            conf.AddProject<Alba.Engine.GraphicsProject>(target);

            //-------------------------------------------------------------------------------------
            // Demo
            //-------------------------------------------------------------------------------------
            conf.AddProject<Alba.Demo.GravityProject>(target);

            //-------------------------------------------------------------------------------------
            // Applications
            //-------------------------------------------------------------------------------------
            conf.AddProject<Alba.Application.GravityDemoExeProject>(target);
        }

        [Main]
        public static void SharpmakeMain(Arguments sharpmakeArgs)
        {
            sharpmakeArgs.Generate<External.Solution>();
            sharpmakeArgs.Generate<Solution>();
        }
    }
}
