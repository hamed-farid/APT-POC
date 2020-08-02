$64EncodedData = Get-Content mail.ps1
$DecodedData = [Convert]::ToBase64String([Text.Encoding]::Unicode.GetBytes($64EncodedData))
([regex]::Matches($DecodedData ,'.','RightToLeft') | ForEach {$_.value}) -join ''
$DecodedData 