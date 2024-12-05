Import('env')
import time
import hashlib

fw_version = "0.9.2"
api_version = "1.3.10"

fw_major, fw_minor, fw_patch = fw_version.split(".")

env.Append(BUILD_FLAGS=[f"-DFIRMWARE_VERSION=\\\"{fw_version}\\\""])
env.Append(BUILD_FLAGS=[f"-DFIRMWARE_VERSION_MAJOR={fw_major}"])
env.Append(BUILD_FLAGS=[f"-DFIRMWARE_VERSION_MINOR={fw_minor}"])
env.Append(BUILD_FLAGS=[f"-DFIRMWARE_VERSION_PATCH={fw_patch}"])

env.Append(BUILD_FLAGS=[f"-DAPI_VERSION=\\\"{api_version}\\\""])

build_hash = hashlib.sha1(str(time.time()).encode()).hexdigest()[:8]
build_hash_str = str(build_hash)  # Convert build_hash to a string
env.Append(BUILD_FLAGS=[f"-DBUILD_HASH=\\\"{build_hash_str}\\\""])
