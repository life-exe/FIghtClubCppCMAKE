conan install . --output-folder=build --profile=conanProfileDebug --profile:b=conanProfileDebug --build=missing
call Automation/build.bat generate
call Automation/build.bat build_debug