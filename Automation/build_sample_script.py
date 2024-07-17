import subprocess

# configuration
source_files = ["main.cpp", "character.cpp", "math.cpp", "weapon.cpp"]
output_executable = "FightClubGame.exe"
vs_edition = "Professional"  # or "Community"
arch = "32"  # or "32"

# vs
vs_path = r"c:\Program Files\Microsoft Visual Studio\2022"
vcvars_suffix = r"VC\Auxiliary\Build"
vcvarsall_path = rf"{vs_path}\{vs_edition}\{vcvars_suffix}\vcvars{arch}.bat"

# compiler
compile_command = ["cl"] + source_files + ["/c", "/O2", "/EHsc", "/FAc"]

# linker
def source_to_obj(files):
    return [f.replace(".cpp", ".obj") for f in files]

obj_files = source_to_obj(source_files)
link_command = ["link"] + obj_files + ["/out:" + output_executable, "/time", "/map", "/nologo"]

# build
build_commands = [
    compile_command,
    link_command
]

def run_command(command):
    try:
        subprocess.run(command)
    except subprocess.CalledProcessError as e:
        print(f"Error running command: {' '.join(command)}")
        print(e.stderr)

if __name__ == "__main__":
    print("Compiling and linking game...")

    build_command = [vcvarsall_path, "&&"]
    for command in build_commands:
        build_command += command + ["&&"]
    build_command.pop()

    run_command(build_command)
