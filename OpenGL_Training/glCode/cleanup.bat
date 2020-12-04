attrib *.* -H
attrib *.suo -H
attrib *.opensdf -H

del /F /Q *.*~  
Del /F /Q  *.sln
Del /F /Q  *.vcxproj
Del /F /Q  *.cmake 
Del /F /Q  *.opensdf 
Del /F /Q  *moc* 
Del /F /Q  *.filters 
Del /F /Q  *.suo
Del /F /Q  *.user
Del /F /Q  *.v12.suo
Del /F /Q  *.v12.suo
Del /F /Q  *CMakeCache.txt 
Del /F /Q  *.sdf
Del /F /Q  *.lib 
Del /F /Q  *.dll 
Del /F /Q  *.pdb 
Del /F /Q  *.exp 
Del /F /Q  *.dir
Del /F /Q  *CMakeFiles
Del /F /Q  *x64*
Del /F /Q  *Debug*
Del /F /Q  *Win*
Del /F /Q  *.db
rd  /Q /S  *.vs

FOR /f %%a IN ( 'dir /s /b *.*~ ' ) Do del /S /Q  %%a
FOR /f %%a IN ( 'dir /s /b *.sln ' ) Do del /S /Q %%a
FOR /f %%a IN ( 'dir /s /b *.vcxproj ' ) Do del /S /Q %%a
FOR /f %%a IN ( 'dir /s /b *.cmake' ) Do del /S /Q  %%a
FOR /f %%a IN ( 'dir /s /b *.opensdf' ) Do del /S /Q  %%a
FOR /f %%a IN ( 'dir /s /b *moc*' ) Do del /S /Q  %%a
FOR /f %%a IN ( 'dir /s /b *.filters' ) Do del /S /Q  %%a
FOR /f %%a IN ( 'dir /s /b *.suo' ) Do del /S /Q %%a
FOR /f %%a IN ( 'dir /s /b *.user' ) Do del /S /Q %%a
FOR /f %%a IN ( 'dir /s /b *.v12.suo' ) Do attrib -H %%a
FOR /f %%a IN ( 'dir /s /b *.v12.suo' ) Do del /S /Q %%a
FOR /f %%a IN ( 'dir /s /b *CMakeCache.txt' ) Do del /S /Q  %%a
FOR /f %%a IN ( 'dir /s /b *.sdf' ) Do del /S /Q %%a
FOR /f %%a IN ( 'dir /s /b *.lib' ) Do del /S /Q  %%a
FOR /f %%a IN ( 'dir /s /b *.dll' ) Do del /S /Q  %%a
FOR /f %%a IN ( 'dir /s /b *.pdb' ) Do del /S /Q  %%a
FOR /f %%a IN ( 'dir /s /b *.exp' ) Do del /S /Q  %%a
FOR /f %%a IN ( 'dir /s /b *.dir' ) Do rd /S /Q %%a
FOR /f %%a IN ( 'dir /s /b *CMakeFiles' ) Do rd /S /Q %%a
FOR /f %%a IN ( 'dir /s /b *x64*' ) Do rd /S /Q %%a
FOR /f %%a IN ( 'dir /s /b *Debug*' ) Do rd /S /Q %%a
FOR /f %%a IN ( 'dir /s /b *Win*' ) Do rd /S /Q %%a
FOR /f %%a IN ( 'dir /s /b *.vs' ) Do rd /S /Q %%a


md Debug 
copy "..\3rd party\libs\freeglut.dll" Debug\
copy "..\3rd party\libs\glew32.dll" Debug\

md src\glutMod\Debug
copy "..\3rd party\libs\freeglut.lib" src\glutMod\Debug
md src\glMod\Debug
copy "..\3rd party\libs\glew32.lib" src\glMod\Debug

pause
