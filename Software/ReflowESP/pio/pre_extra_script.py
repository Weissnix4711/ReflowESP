# pre_extra_scripts.py
#
# Adapted from Marlin FW Project, which is released under the
# GNU General Public License, version 3.
#
# Original file:
# https://github.com/MarlinFirmware/Marlin/blob/bugfix-2.1.x/buildroot/share/PlatformIO/scripts/preprocessor.py

import subprocess

Import("env")

verbose = 1

def blab(s, level=1):
    if verbose >= level:
        print(f"[pio scripts] {s}")

def set_env_field(field, value):
    proj = env.GetProjectConfig()
    proj.set("env:" + env['PIOENV'], field, value)

def run_preprocessor(file=None):
    file = file or 'pio/dependencies.h'

    cmd = f"gcc -w -dM -E -x c++ {file}"

    build_flags = env.get('BUILD_FLAGS')
    build_flags = env.ParseFlagsExtended(build_flags)

    for s in build_flags['CPPDEFINES']:
        if isinstance(s, tuple):
            cmd += ' -D' + s[0] + '=' + str(s[1])
        else:
            cmd += ' -D' + s

    blab(cmd)

    out = subprocess.check_output(cmd.split()).splitlines()
    defines = [define[8:].decode('UTF-8') for define in out]

    features = {}
    for define in defines:
        define = define.split(' ')
        feature, definition = define[0], ' '.join(define[1:])
        features[feature] = definition

    return features

features = run_preprocessor()

deps = env.GetProjectOption('lib_deps')

libs_to_add = []

if 'HAS_MAX31855' in features:
    libs_to_add.append('adafruit/Adafruit MAX31855 library@^1.4.0')
elif 'HAS_MAX6675' in features:
    libs_to_add.append('adafruit/MAX6675 library@^1.1.0')

set_env_field('lib_deps', deps + libs_to_add)

blab(env.GetProjectOption('lib_deps'))
