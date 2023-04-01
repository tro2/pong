#Requires -Version 3

# Set directory to solution root
$solutionDir = Join-Path -Path $PSScriptRoot -ChildPath ".."
Set-Location -Path $solutionDir

# Check if NathanPong.sln exists and exit otherwise
if (-not(Test-Path -Path "NathanPong.sln" -PathType Leaf)) {
	Write-Host "Fatal error: NathanPong.sln not found"
	exit 1
}

# Check if NathanPongApp\ exists and exit otherwise
if (-not(Test-Path -Path "NathanPongApp" -PathType Container)) {
	Write-Host "Fatal error: NathanPongApp\ not found"
	exit 1
}

# Get NathanPongApp's project GUID
$currentGuid = "f2bbb07f-924d-44d9-995b-1a74a3d753af"
$newGuid = New-Guid

# Get new project name
$newName = Read-Host "Please enter your new project name (must be a valid Visual Studio name, no spaces preferred)"
$newNameApp = $newName + "App"

# TODO: delete VS cache (fail if VS has lock on cache) and/or build folders?

# Temporary: Provide old and new GUIDs for manual find-and-replace
Write-Host "Old GUID: $currentGuid"
Write-Host "New GUID: $newGuid"

# Rename solution file
$newSolutionFileName = "$newName.sln"
Rename-Item -Path "NathanPong.sln" -NewName "$newSolutionFileName"

# Rename project directory
$newProjectDirectoryName = "$newNameApp"
Rename-Item -Path "NathanPongApp" -NewName "$newProjectDirectoryName"

# Rename project files
Rename-Item -Path "$newProjectDirectoryName\NathanPongApp.vcxproj" -NewName "$newNameApp.vcxproj"
Rename-Item -Path "$newProjectDirectoryName\NathanPongApp.vcxproj.filters" -NewName "$newNameApp.vcxproj.filters"

if (Test-Path -Path "$newProjectDirectoryName\NathanPongApp.vcxproj.user") {
	Rename-Item -Path "$newProjectDirectoryName\NathanPongApp.vcxproj.user" -NewName "$newNameApp.vcxproj.user"
}

########################################################################################################################
########################################################################################################################
# TODO: Learn powershell to do this properly
########################################################################################################################
########################################################################################################################

# Why is this failing?

# Get-ChildItem -Exclude "Dependencies" |
# Get-ChildItem -Recurse *.* |
# ForEach-Object {
# 	Write-Host $_.fullname
# }

# Replace the old project name

# Get-ChildItem -Exclude "Dependencies\", ".git\" |
# ForEach-Object {
# 	Get-ChildItem -Recurse *.* |
# 	ForEach-Object {
# 		$a = $_.fullname;
# 		$content = Get-Content $a;
# 
# 		$content |
# 		ForEach-Object { $_ -replace "NathanPong", "$newName" } | 
# 		set-content $a
# 	}
# }

# Replace the old guid

# Get-ChildItem -Recurse *.* -Exclude "Dependencies\*" |
# ForEach-Object {
# 	$a = $_.fullname;
# 	$content = Get-Content $a;
# 	
# 	if ($content.Contains("NathanPong")) {
# 		$content |
# 		ForEach-Object { $_ -replace "$currentGuid", "$newName" } | 
# 		set-content $a
# 	}
# 	
# 	(Get-Content $a) |
# 	ForEach-Object { $_ -replace "$currentGuid", "$newGuid" } | 
# 	set-content $a
# }