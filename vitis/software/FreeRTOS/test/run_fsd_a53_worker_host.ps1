$ErrorActionPreference = 'Stop'
$freeRtos = (Resolve-Path -LiteralPath (Join-Path $PSScriptRoot '..')).Path
$shared = (Resolve-Path -LiteralPath (Join-Path $freeRtos '..\shared')).Path
$support = Join-Path $PSScriptRoot 'host_support'
$output = Join-Path $env:TEMP 'uz_fsd_a53_host_tests'
New-Item -ItemType Directory -Path $output -Force | Out-Null
$common = @(
    '-std=c99', '-O2', '-Wall', '-Wextra', '-Wpedantic', '-Werror',
    '-DTEST', '-DUZ_FSD_A53_BENCHMARK_ENABLE=1',
    ('-I' + $support), ('-I' + $shared),
    ('-I' + (Join-Path $freeRtos 'include')),
    ('-I' + (Join-Path $freeRtos 'uz')),
    ('-I' + (Join-Path $freeRtos 'uz/uz_fsd_mpc'))
)
$sources = @(
    (Join-Path $PSScriptRoot 'fsd_a53_worker_host.c'),
    (Join-Path $freeRtos 'sw/fsd_a53_worker.c'),
    (Join-Path $freeRtos 'uz/uz_fsd_mpc/uz_fsd_mpc.c'),
    (Join-Path $freeRtos 'uz/uz_fsd_mpc/uz_fsd_mpc_math.c'),
    (Join-Path $freeRtos 'uz/uz_fsd_mpc/uz_fsd_mpc_solver.c')
)
foreach ($variant in 0..8) {
    $exe = Join-Path $output ("variant_$variant.exe")
    $yangOpt = @()
    if ($variant -ge 6) { $yangOpt = @('-DUZ_FSD_YANG_EXPERIMENT_ENABLE=1') }
    & gcc @common @yangOpt ("-DUZ_FSD_A53_BENCHMARK_VARIANT=$variant") @sources -lm -o $exe
    if ($LASTEXITCODE -ne 0) { throw "Host compile failed for variant $variant" }
    & $exe
    if ($LASTEXITCODE -ne 0) { throw "Host replay failed for variant $variant" }
}
