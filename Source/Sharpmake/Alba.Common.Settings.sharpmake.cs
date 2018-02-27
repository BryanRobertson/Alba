using System.IO;
using Sharpmake;

namespace Alba
{
    //-------------------------------------------------------------------------------------------------
    // Name	:	Settings
    // Desc	:	Shared Settings
    //-------------------------------------------------------------------------------------------------
    static class Settings
	{
        public static Platform GetDefaultPlatforms()
        {
            return Platform.win64;
        }

        public static DevEnv GetDefaultDevEnvs()
        {
            return DevEnv.vs2017;
        }

        public static string GetExternalLibraryPath(string relativePath)
        {
            return System.IO.Path.Combine(@"[project.SharpmakeCsPath]\..\External", relativePath);
        }

        public static string GetIntermediatePath()
        {
            return @"[project.SharpmakeCsPath]\..\..\Intermediate\[project.Name]";
        }

        public static string GetTargetPath()
        {
            return @"[project.SharpmakeCsPath]\..\..\Binaries";
        }

        public static string GetLibraryTargetPath()
        {
            return @"[project.SharpmakeCsPath]\..\..\Libraries\[project.Name]";
        }

        public static string GetProjectPath()
        {
            return @"[project.SharpmakeCsPath]\generated";
        }
    }
}