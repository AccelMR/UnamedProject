@echo off
setlocal enabledelayedexpansion

REM =========================
REM Config
REM =========================
set SUBMODULE_DIR=godot-cpp

echo.
echo === Checking prerequisites ===

REM --- Check git ---
where git >nul 2>nul
if errorlevel 1 (
    echo [ERROR] git no esta en PATH. Instala Git for Windows y reabre la consola.
    exit /b 1
)

REM --- Check scons ---
where scons >nul 2>nul
if errorlevel 1 (
    echo [WARN] scons no esta en PATH.

    REM Try winget
    where winget >nul 2>nul
    if not errorlevel 1 (
        echo Intentando instalar SCons con winget...
        winget install -e --id SCons.SCons
        where scons >nul 2>nul
        if errorlevel 1 (
            echo [ERROR] SCons no se pudo instalar con winget.
            exit /b 1
        ) else (
            echo [OK] SCons instalado con winget.
            goto :SCONS_OK
        )
    )

    REM Try choco
    where choco >nul 2>nul
    if not errorlevel 1 (
        echo Intentando instalar SCons con Chocolatey...
        choco install scons -y
        where scons >nul 2>nul
        if errorlevel 1 (
            echo [ERROR] SCons no se pudo instalar con Chocolatey.
            exit /b 1
        ) else (
            echo [OK] SCons instalado con Chocolatey.
            goto :SCONS_OK
        )
    )

    echo [ERROR] No encuentro scons y no hay winget/choco para instalarlo.
    echo Instala SCons manualmente:
    echo   - via pip:  python -m pip install scons
    echo   - o winget/choco y asegurate que quede en PATH
    exit /b 1
)

:SCONS_OK
echo [OK] git y scons disponibles.
echo.

REM =========================
REM Update submodules
REM =========================
echo === Updating submodules ===
git submodule update --init --recursive
if errorlevel 1 (
    echo [ERROR] Fallo git submodule update.
    exit /b 1
)

REM =========================
REM Build submodule (godot-cpp)
REM =========================
if not exist "%SUBMODULE_DIR%\" (
    echo [ERROR] No existe la carpeta "%SUBMODULE_DIR%". Algo salio mal con submodules.
    exit /b 1
)

echo.
echo === Building %SUBMODULE_DIR% ===
pushd "%SUBMODULE_DIR%"
if errorlevel 1 (
    echo [ERROR] No pude entrar a %SUBMODULE_DIR%.
    exit /b 1
)

scons
if errorlevel 1 (
    echo [ERROR] Fallo scons dentro de %SUBMODULE_DIR%.
    popd
    exit /b 1
)
popd

REM =========================
REM Build main project
REM =========================
echo.
echo === Building main project ===
scons
if errorlevel 1 (
    echo [ERROR] Fallo scons en el proyecto principal.
    exit /b 1
)

echo.
echo === DONE ===
exit /b 0
