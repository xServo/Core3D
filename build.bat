cmake -B build/win
msbuild build/win/Core3D.sln /p:Configuration=Debug /p:Platform=x64
move build\win\Debug\Core3D.exe .\
@echo Build completed. Press any key to exit...
@pause >nul
