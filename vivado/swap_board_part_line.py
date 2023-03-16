import os

# https://stackoverflow.com/questions/28925585/swap-lines-of-text-around-in-text-file
inp = open('_build.tcl', 'r')
out = open('_build2.tcl', 'w')
prev = inp.readline()
for line in inp:
   if line.startswith('set_property -name "board_part_repo_paths"'):
      out.write(line)
      continue
   else:
      out.write(prev)
   prev = line
out.write(prev)
out.close()
inp.close()

os.remove('_build.tcl')
os.rename('_build2.tcl','_build.tcl')
