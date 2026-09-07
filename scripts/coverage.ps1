$root = Split-Path -Parent $PSScriptRoot
$build = Join-Path $root "build\tests"
$coverage = Join-Path $root "coverage"

if (-not (Test-Path $build))
{
    Write-Error "Test build directory does not exist: $build"
    exit 1
}

Remove-Item $coverage -Recurse -Force -ErrorAction SilentlyContinue

Write-Host "[coverage] Running tests..."

OpenCppCoverage `
    "--export_type=html:$coverage" `
    "--sources=$root\engine" `
    "--sources=$root\ai" `
    "--sources=$root\app" `
    "--cover_children" `
    "--" `
    "ctest" `
    "--test-dir" `
    $build `
    "-C" `
    "Debug" `
    "--output-on-failure"

if ($LASTEXITCODE -ne 0)
{
    exit $LASTEXITCODE
}

Start-Process (Join-Path $coverage "index.html")