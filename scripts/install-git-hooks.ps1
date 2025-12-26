# Install repository git hooks (copy from githooks/ to .git/hooks)
$repoRoot = (git rev-parse --show-toplevel) -replace '\\$',''
$srcHook = Join-Path $repoRoot "githooks\pre-commit"
$destHook = Join-Path $repoRoot ".git\hooks\pre-commit"

if (-not (Test-Path $srcHook)) {
    Write-Error "Hook source '$srcHook' not found."
    exit 1
}

Copy-Item -Path $srcHook -Destination $destHook -Force
# Ensure hook is executable when used in environments that rely on exec bit
try {
    icacls $destHook /grant "*S-1-1-0:(RX)" | Out-Null
} catch {
    # ignore permission errors
}

Write-Host "Installed pre-commit hook to .git/hooks/pre-commit"
Write-Host "You may need to make it executable in your environment (e.g., chmod +x .git/hooks/pre-commit)"