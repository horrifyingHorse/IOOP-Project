# PowerShell script for building project with optional execution

$buildOnly = $false

# Check for build-only flag
if ($args.Count -ge 1) {
    if ($args[0] -eq "-b") {
        $buildOnly = $true
    } else {
        Write-Output "Unknown flag $args[0]"
        exit 1
    }
}

# Check if build directory exists; create it if not
if (Test-Path -Path "./build") {
    Write-Output "Found ./build directory;"
} else {
    Write-Output "Creating ./build directory;"
    New-Item -ItemType Directory -Path "./build" | Out-Null
}

# Check for cmake installation
if (!(Get-Command "cmake" -ErrorAction SilentlyContinue)) {
    Write-Output "To build this project you need to install cmake"
    Start-Process "powershell" -ArgumentList "sudo apt install cmake" -Wait
    Write-Output "--------------------------"
    Write-Output "cmake installed to build;"
} else {
    Write-Output "Found cmake to build;"
}

# Change to build directory and run cmake
Set-Location "./build"
cmake -G "MinGW Makefiles" ..
if ($LASTEXITCODE -ne 0) {
    Write-Output "Quit building due to error;"
    exit 1
}

# Run make to build project
mingw32-make
if ($LASTEXITCODE -ne 0) {
    Write-Output "Quit building due to error;"
    exit 1
}

# Return to root directory
Set-Location ..

Write-Output "Build complete"
Write-Output "--------------------------"

# Execute the binary if buildOnly flag is not set
if (-not $buildOnly) {
    Write-Output "Executing binary"
    # Run the executable
    Start-Process "./build/car-dealer"
}
