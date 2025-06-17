@echo off

REM GERADO POR I.A! NÃO USO WINDOWS!

if not exist build (
    mkdir build
)

cd build

cmake ..
if errorlevel 1 (
    echo [ERRO] Falha no CMake.
    exit /b
)

make
if errorlevel 1 (
    echo [ERRO] Falha no make.
    exit /b
)

opengl_code.exe
cls
