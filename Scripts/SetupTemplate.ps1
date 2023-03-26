#Requires -Version 3

# Set directory to solution root
$solutionDir = Join-Path -Path $PSScriptRoot -ChildPath ".."
Set-Location -Path $solutionDir

# Check if GameTemplate.sln exists and exit otherwise
if (-not(Test-Path -Path "GameTemplate.sln" -PathType Leaf)) {
	Write-Host "Fatal error: GameTemplate.sln not found"
	exit 1
}

# Check if GameTemplateApp\ exists and exit otherwise
if (-not(Test-Path -Path "GameTemplateApp" -PathType Container)) {
	Write-Host "Fatal error: GameTemplateApp\ not found"
	exit 1
}

# Get GameTemplateApp's project GUID
$currentGuid = "13ddd496-ccd0-4a60-96c1-81bc1d8cfde5"
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
Rename-Item -Path "GameTemplate.sln" -NewName "$newSolutionFileName"

# Rename project directory
$newProjectDirectoryName = "$newNameApp"
Rename-Item -Path "GameTemplateApp" -NewName "$newProjectDirectoryName"

# Rename project files
Rename-Item -Path "$newProjectDirectoryName\GameTemplateApp.vcxproj" -NewName "$newNameApp.vcxproj"
Rename-Item -Path "$newProjectDirectoryName\GameTemplateApp.vcxproj.filters" -NewName "$newNameApp.vcxproj.filters"

if (Test-Path -Path "$newProjectDirectoryName\GameTemplateApp.vcxproj.user") {
	Rename-Item -Path "$newProjectDirectoryName\GameTemplateApp.vcxproj.user" -NewName "$newNameApp.vcxproj.user"
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
# 		ForEach-Object { $_ -replace "GameTemplate", "$newName" } | 
# 		set-content $a
# 	}
# }

# Replace the old guid

# Get-ChildItem -Recurse *.* -Exclude "Dependencies\*" |
# ForEach-Object {
# 	$a = $_.fullname;
# 	$content = Get-Content $a;
# 	
# 	if ($content.Contains("GameTemplate")) {
# 		$content |
# 		ForEach-Object { $_ -replace "$currentGuid", "$newName" } | 
# 		set-content $a
# 	}
# 	
# 	(Get-Content $a) |
# 	ForEach-Object { $_ -replace "$currentGuid", "$newGuid" } | 
# 	set-content $a
# }