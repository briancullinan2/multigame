for /r %%v in (*.mdl) do ( 
modelconv.exe -force -i "%%v" ".\%%~nv.md2"
copy ".\skin0.pcx" ".\%%~nv.pcx"
)
