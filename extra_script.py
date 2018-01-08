''' custom script for platformio '''

from os.path import join
from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()

print "custom extra_script launching..."

# env.Replace(
#     MYUPLOADERFLAGS=[
#         "-v",
#         "-p", "$BOARD_MCU",
#         "-C",
#         '"%s"' % join("$PIOPACKAGES_DIR", "tool-avrdude", "avrdude.conf"),
#         "-c", "$UPLOAD_PROTOCOL",
#         "-b", "$UPLOAD_SPEED"
#      ],
#     UPLOADHEXCMD='"$UPLOADER" $MYUPLOADERFLAGS -U flash:w:$SOURCES:i'
# )

if "BOARD" in env and env.BoardConfig().get("vendor") == "STC":
    f_cpu_khz = int(env.BoardConfig().get("build.f_cpu")) / 1000
    env.Replace(
            UPLOAD_OPTIONS = [
                "-p", "$UPLOAD_PORT",
                "-P", "stc15a",
                "-t", int(f_cpu_khz),
            ],
            UPLOADHEXCMD = "stcgal/stcgal.py $UPLOAD_OPTIONS $SOURCE"
    )
