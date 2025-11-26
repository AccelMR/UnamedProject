@echo off
setlocal enabledelayedexpansion

REM =========================
REM Config
REM =========================
set SUBMODULE_DIR=godot-cpp
set "PYTHON_EXE="
set "PYTHON_VERSION="
set "SCONS_CMD="

echo.
echo === Checking prerequisites ===

REM --- Check Python >= 3.8 ---
call :try_python "python"
if not defined PYTHON_EXE call :try_python "py -3"

if not defined PYTHON_EXE (
    echo [ERROR] Necesitas Python 3.8 o mayor (python/py -3 en PATH).
    echo Instala Python 3.8+ y vuelve a ejecutar este script.
    pause
    exit /b 1
)
echo [OK] Python !PYTHON_VERSION! encontrado: !PYTHON_EXE!

REM --- Check pip ---
"!PYTHON_EXE!" -m pip --version >nul 2>nul
if errorlevel 1 (
    echo [ERROR] pip no esta disponible en este Python. Ejecuta "!PYTHON_EXE! -m ensurepip" o instala pip y reintenta.
    pause
    exit /b 1
)

REM --- Check scons/SCons (PATH or python -m scons) ---
where scons >nul 2>nul && set "SCONS_CMD=scons"
if not defined SCONS_CMD where SCons >nul 2>nul && set "SCONS_CMD=SCons"

if not defined SCONS_CMD (
    echo [WARN] scons no esta en PATH. Probando python -m scons...
    "!PYTHON_EXE!" -m scons --version >nul 2>nul
    if errorlevel 1 (
        "!PYTHON_EXE!" -m SCons --version >nul 2>nul
    )
    if errorlevel 1 (
        echo Intentando instalar scons via pip...
        "!PYTHON_EXE!" -m pip install --user scons
        "!PYTHON_EXE!" -m scons --version >nul 2>nul
        if errorlevel 1 (
            echo [ERROR] No se pudo usar ni instalar scons. Agrega scons a PATH o instala manualmente.
            pause
            exit /b 1
        )
    )
    set "SCONS_CMD=!PYTHON_EXE! -m scons"
    echo [OK] scons disponible via python -m scons
) else (
    echo [OK] scons/SCons disponible en PATH.
)

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

%SCONS_CMD%
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
%SCONS_CMD%
if errorlevel 1 (
    echo [ERROR] Fallo scons en el proyecto principal.
    exit /b 1
)

echo.
echo === DONE ===
exit /b 0


REM =========================
REM Helpers
REM =========================
:try_python
set "_CAND=%~1"
for /f "delims=" %%v in ('!_CAND! --version 2^>nul') do set "_VERSTR=%%v"
if not defined _VERSTR goto :eof
for /f "delims=" %%v in ('!_CAND! -c "import sys; print(f'{sys.version_info[0]}.{sys.version_info[1]}')" 2^>nul') do set "PYTHON_VERSION=%%v"
if not defined PYTHON_VERSION goto :eof
for /f "tokens=1,2 delims=." %%a in ("!PYTHON_VERSION!") do (
    set "_MAJ=%%a"
    set "_MIN=%%b"
)
if "!_MAJ!"=="" goto :eof
if !_MAJ! LSS 3 goto :eof
if !_MAJ! EQU 3 if !_MIN! LSS 8 goto :eof
set "PYTHON_EXE=!_CAND!"
goto :eof
