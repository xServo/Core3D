cmake -B build
msbuild build/Core3D.sln /p:Configuration=Debug /p:Platform=x64
@echo Press any key to exit...
@pause >nul
