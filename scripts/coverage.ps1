$root = Split-Path -Parent $PSScriptRoot
$exe = Get-ChildItem "$root\build\tests" -Filter "minesweeper_tests.exe" -Recurse | Select-Object -First 1
$coverage = "$root\coverage"

Remove-Item $coverage -Recurse -Force -ErrorAction SilentlyContinue

OpenCppCoverage `
    "--export_type=html:$coverage" `
    "--sources=$root\engine" `
    "--" $exe.FullName

Start-Process "$coverage\index.html"