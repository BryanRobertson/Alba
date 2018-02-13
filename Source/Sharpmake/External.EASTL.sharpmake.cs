using System.IO;
using Sharpmake;

namespace External
{
    namespace EASTL
    {
        class Project : Sharpmake.Project
        {
            public Project()
            {
                Name = "EASTL";
                SourceRootPath = Alba.Settings.GetExternalLibraryPath("EASTL");
            }
        }
    }
}