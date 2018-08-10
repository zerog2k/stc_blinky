''' custom script for platformio '''

from os.path import join
from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()

print "custom extra_script launching..."

env.Append(
    # stcgal expected in stcgal subdir
    STCGALCMD="/stcgal.py"
)
