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
    }
}