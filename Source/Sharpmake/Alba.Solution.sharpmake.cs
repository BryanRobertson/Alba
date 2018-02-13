using System.IO;
using Sharpmake;

[module: Sharpmake.Include("Alba.ProjectBase.sharpmake.cs")]
[module: Sharpmake.Include("Alba.Core.sharpmake.cs")]
[module: Sharpmake.Include("Alba.Settings.sharpmake.cs")]

// Represents the solution that will be generated and that will contain the
// project with the sample code.
[Sharpmake.Generate]
public class AlbaSolution : Sharpmake.Solution
{
    public AlbaSolution()
    {
        // The name of the solution.
        Name = "Alba";

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

        conf.AddProject<Alba.CoreProject>(target);
    }

    [Main]
    public static void SharpmakeMain(Arguments sharpmakeArgs)
    {
        sharpmakeArgs.Generate<AlbaSolution>();
    }
}
