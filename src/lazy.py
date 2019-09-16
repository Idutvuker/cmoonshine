from pathlib import Path
import os
#import file

pathlist = Path("").glob('**/*.h')
for path in pathlist:
	path_in_str = str(path)
	y = path_in_str[:-2] + ".cpp"
	
	if (os.path.isfile(y) == False):
		f = open(y, "w+")
		f.write("#include " + path.name + "\n")
		f.close()