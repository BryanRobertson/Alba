using System.IO;
using Sharpmake;

[module: Sharpmake.Include("External.EASTL.sharpmake.cs")]

namespace External
{
    [Sharpmake.Generate]
    public class Solution : Sharpmake.Solution
    {
        public Solution()
        {
            // The name of the solution.
            Name = "ExternalLibs";

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

        // Configure for all 4 generated targets. Note that the type of the
        // configuration object is of type Solution.Configuration this time.
        // (Instead of Project.Configuration.)
        [Configure]
        public void ConfigureAll(Solution.Configuration conf, Target target)
        {
            conf.SolutionFileName = "[solution.Name]_[target.Platform]_[target.DevEnv]";
            conf.SolutionPath = @"[solution.SharpmakeCsPath]\generated";

            conf.AddProject<External.EASTL.Project>(target);
        }
    }
}