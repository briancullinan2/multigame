for /r %%v in (*.md2) do ( 
"C:\Program Files (x86)\Maverick Model 3D\mm3d.x86.exe" --convert md3 "%%v" 
"C:\Program Files (x86)\Maverick Model 3D\mm3d.x86.exe" --convert cfg "%%v" 
copy ".\animations.cfg" "%%~nv.cfg"
)
