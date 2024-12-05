Import('env')
import os
import shutil
import datetime

OUTPUT_DIR = "build_output{}".format(os.path.sep)

def _get_cpp_define_value(env, define):
    define_list = [item[-1] for item in env["CPPDEFINES"] if item[0] == define]

    if define_list:
        return define_list[0]

    return None

def _create_dirs(dirs=["firmware"]):
    # check if output directories exist and create if necessary
    if not os.path.isdir(OUTPUT_DIR):
        os.mkdir(OUTPUT_DIR)

    for d in dirs:
        if not os.path.isdir("{}{}".format(OUTPUT_DIR, d)):
            os.mkdir("{}{}".format(OUTPUT_DIR, d))

def hex_rename_copy(source, target, env):
  _create_dirs()

  version = _get_cpp_define_value(env, "FIRMWARE_VERSION")
  # remove backslashes and quotes
  version = version.replace("\\", "").replace("\"", "")

  antenna = _get_cpp_define_value(env, "ANTENNA")
  solar = _get_cpp_define_value(env, "SOLAR")
  helio = _get_cpp_define_value(env, "HELIOSTAT")
  
  device = "nan"
  if antenna:
    device = "antenna"
  if solar:
    device = "solar"
  if helio:
    device = "helio"

  # format file_name as YYMMDD-version_jack-device.hex
  today = datetime.datetime.now()
  file_name = today.strftime("%Y%m%d")[2:] + "-v" + version + "_jack-" + device

  firmware_file = "{}firmware{}{}.hex".format(OUTPUT_DIR, os.path.sep, file_name)

  shutil.copy(str(target[0]), firmware_file)

def print_build_hash(source, target, env):
    build_hash = _get_cpp_define_value(env, "BUILD_HASH")
    print("BUILD_HASH " + build_hash)

env.AddPostAction("$BUILD_DIR/${PROGNAME}.hex", hex_rename_copy)
env.AddPostAction("$BUILD_DIR/${PROGNAME}.hex", print_build_hash)
