# Simple build script for JavaScope (PowerShell)
# Use this until you install Apache Ant

Write-Host "Building JavaScope..." -ForegroundColor Green

$JdkRelease = "21"
$RootDir = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $RootDir

# Create build directories
New-Item -ItemType Directory -Force -Path "build\classes" | Out-Null
New-Item -ItemType Directory -Force -Path "dist" | Out-Null

$Libs = @(
    "lib\jfreechart-1.5.6.jar",
    "lib\flatlaf-3.7.jar"
)

$JarPath = Join-Path $RootDir "dist\UZ_GUI.jar"
if (Test-Path $JarPath) {
    $jarTime = (Get-Item $JarPath).LastWriteTimeUtc
    $newer = Get-ChildItem -Path (Join-Path $RootDir "src"), (Join-Path $RootDir "lib") -Recurse -File | Where-Object { $_.LastWriteTimeUtc -gt $jarTime } | Select-Object -First 1
    if ($null -eq $newer) {
        Write-Host "Build up to date; skipping." -ForegroundColor Green
        exit 0
    }
}

if (Test-Path $JarPath) {
    try {
        Remove-Item $JarPath -Force -ErrorAction Stop
    } catch {
        $removeMessage = $_.Exception.Message
        if ($removeMessage -match 'used by another process|being used by another process|Der Prozess kann nicht auf die Datei zugreifen') {
            Write-Host "Build blocked: dist\UZ_GUI.jar is locked by another process, likely a running JavaScope instance. Close JavaScope and retry." -ForegroundColor Red
        } else {
            Write-Host "Failed to remove dist\UZ_GUI.jar: $removeMessage" -ForegroundColor Red
        }
        exit 1
    }
}

# Compile Java files
Write-Host "Compiling Java sources..." -ForegroundColor Yellow
$classpath = ($Libs -join ";")
javac --release $JdkRelease `
      -Xlint:unchecked `
      -d build\classes `
      -sourcepath src `
      -cp $classpath `
      (Get-ChildItem -Path src -Recurse -Filter *.java | Select-Object -ExpandProperty FullName)

if ($LASTEXITCODE -ne 0) {
    Write-Host "Compilation failed!" -ForegroundColor Red
    exit 1
}

# Copy resource files (everything except .java)
Write-Host "Copying resources..." -ForegroundColor Yellow
Get-ChildItem -Path src -Recurse -File | Where-Object { $_.Extension -ne '.java' } | ForEach-Object {
    $targetPath = $_.FullName.Replace((Resolve-Path src).Path, (Resolve-Path build\classes).Path)
    $targetDir = Split-Path -Parent $targetPath
    if (!(Test-Path $targetDir)) {
        New-Item -ItemType Directory -Force -Path $targetDir | Out-Null
    }
    Copy-Item $_.FullName $targetPath -Force
}

Write-Host "Writing build timestamp..." -ForegroundColor Yellow
$buildInfoDir = "build\classes\UZ_GUI"
if (!(Test-Path $buildInfoDir)) {
    New-Item -ItemType Directory -Force -Path $buildInfoDir | Out-Null
}
$buildTimestamp = (Get-Date).ToUniversalTime().ToString("yyyy-MM-ddTHH:mm:ssZ")
"build.timestamp=$buildTimestamp" | Out-File -FilePath (Join-Path $buildInfoDir "build-info.properties") -Encoding ASCII

# Create manifest
$classPathLine = ($Libs -replace "\\\\", "/" ) -join " "
$manifest = @"
Manifest-Version: 1.0
Main-Class: UZ_GUI.Start
Class-Path: $classPathLine
"@

$manifest | Out-File -FilePath "build\manifest.mf" -Encoding ASCII

# Create JAR
Write-Host "Creating JAR..." -ForegroundColor Yellow
$jarCmd = Get-Command jar -ErrorAction SilentlyContinue
if ($null -eq $jarCmd) {
    $jarExe = $null
    if ($env:JAVA_HOME) {
        $candidate = Join-Path $env:JAVA_HOME "bin\jar.exe"
        if (Test-Path $candidate) {
            $jarExe = $candidate
        }
    }
    if ($null -eq $jarExe) {
        Write-Host "ERROR: 'jar' was not found. Install JDK $JdkRelease, set JAVA_HOME, and add %JAVA_HOME%\\bin to PATH. Restart VS Code/terminal." -ForegroundColor Red
        exit 1
    }
    $jarOutput = & $jarExe -cfm dist\UZ_GUI.jar build\manifest.mf -C build\classes . 2>&1
} else {
    $jarOutput = & jar -cfm dist\UZ_GUI.jar build\manifest.mf -C build\classes . 2>&1
}
$jarExitCode = $LASTEXITCODE
if ($jarOutput) {
    $jarOutput | ForEach-Object { Write-Host $_ }
}

if ($jarExitCode -eq 0 -and (Test-Path $JarPath)) {
    Write-Host "Copying runtime config to dist/" -ForegroundColor Yellow
    if (Test-Path "properties.ini") {
        Copy-Item "properties.ini" "dist\properties.ini" -Force
    }

    Write-Host "Syncing runtime libraries to dist\lib (classpath only)..." -ForegroundColor Yellow
    if (Test-Path "dist\lib") {
        Remove-Item -Recurse -Force "dist\lib"
    }
    New-Item -ItemType Directory -Force -Path "dist\lib" | Out-Null
    foreach ($lib in $Libs) {
        $targetPath = Join-Path "dist" $lib
        $targetDir = Split-Path -Parent $targetPath
        if (!(Test-Path $targetDir)) {
            New-Item -ItemType Directory -Force -Path $targetDir | Out-Null
        }
        Copy-Item $lib $targetPath -Force
    }
    Write-Host "Build successful: dist\UZ_GUI.jar" -ForegroundColor Green
} else {
    $jarOutputText = ($jarOutput | Out-String)
    if ($jarOutputText -match 'used by another process|being used by another process|Der Prozess kann nicht auf die Datei zugreifen|FileSystemException|AccessDeniedException') {
        Write-Host "JAR creation failed because dist\UZ_GUI.jar is locked by another process. Close JavaScope and retry." -ForegroundColor Red
    } else {
        Write-Host "JAR creation failed. See the output above for details." -ForegroundColor Red
    }
    exit 1
}
