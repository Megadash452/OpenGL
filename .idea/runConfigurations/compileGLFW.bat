"%ProgramFiles%/Microsoft Visual Studio/2022/Community/Common7/Tools/VsDevCmd.bat"
msbuild external/GLFW/build/GLFW.sln -property:Configuration=Release;Platform=x64;OutputPath=external/lib
