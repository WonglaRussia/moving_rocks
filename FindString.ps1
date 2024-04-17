Param (
[Parameter (Mandatory=$true, Position=1)]
[string]$pattern)
[string]$path = "C:\users\asanov\Desktop\GITHUB\moving_rocks\"

Set-Location -Path $path
Get-ChildItem | Where-Object {$_.name -match ".*\.[h|c]"} | Select-String -Pattern $pattern | Select-Object filename,linenumber,line