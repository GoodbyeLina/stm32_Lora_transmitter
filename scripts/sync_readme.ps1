param(
    [switch]$Commit
)

$src = "User\README.md"
$dst = "README.md"

if (-not (Test-Path $src)) {
    Write-Error "Source file '$src' not found."
    exit 1
}

$srcHash = (Get-FileHash -Path $src -Algorithm SHA1).Hash
$dstHash = if (Test-Path $dst) { (Get-FileHash -Path $dst -Algorithm SHA1).Hash } else { "" }

if ($srcHash -ne $dstHash) {
    Copy-Item -Path $src -Destination $dst -Force
    Write-Host "Updated $dst from $src"

    # Always stage the updated README so it can be included in the ongoing commit
    & git add $dst

    if ($Commit) {
        & git commit -m "chore(sync): update README.md from User/README.md"
        & git push
    }
} else {
    Write-Host "$dst is already up to date."
}
