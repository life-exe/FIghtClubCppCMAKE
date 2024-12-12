conan install . --output-folder=build --profile=conanProfileRelease --profile:b=conanProfileRelease --build=missing
call Automation/build.bat generate
call Automation/build.bat build_release