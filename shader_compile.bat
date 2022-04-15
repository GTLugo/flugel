@echo off
SETLOCAL
@REM echo Working directory: %cd%
CALL :compile_shader simple_shader, vertex, res/flugel/shaders, res/flugel/shaders_out
CALL :compile_shader simple_shader, fragment, res/flugel/shaders, res/flugel/shaders_out
EXIT /B %ERRORLEVEL%

:compile_shader
  %VULKAN_SDK%/Bin/glslc.exe -fshader-stage=%~2 %~3/%~1_%~2.hlsl -o %~4/%~1_%~2.spv
EXIT /B 0