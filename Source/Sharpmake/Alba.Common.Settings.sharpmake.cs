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
            return DevEnv.vs2019;
        }

        public static string GetNatvisPath(string relativePath)
        {
            return System.IO.Path.Combine(@"[project.SharpmakeCsPath]\..\Debug", relativePath);
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

        public static Options.Vc.General.WindowsTargetPlatformVersion WindowsTargetPlatformVersion
        {
            get
            {
                return Options.Vc.General.WindowsTargetPlatformVersion.v10_0_18362_0;
            }
        }

        public static Options.Vc.General.PlatformToolset Toolset
        {
            get
            {
                return Options.Vc.General.PlatformToolset.v142;
            }
        }
    }
}