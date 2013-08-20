import fnmatch
import os
import re
import sys

def filter_c_files(path):
	matches = []
	for root, dirnames, filenames in os.walk(path):
		for hfile in fnmatch.filter(filenames, '*.h'):
			matches.append(os.path.join(root, hfile))
		for cfile in fnmatch.filter(filenames, '*.c'):
			matches.append(os.path.join(root, cfile))
	#print matches
	return matches

def filter_globals(filename):
	fd = open(filename)

	ret = {}
	va = []
	brace_number = 0
	for line in fd:
		if line.find('{') != -1 and line.find('}') == -1:
			brace_number += 1
		elif line.find('}') != -1 and line.find('{') == -1:
			brace_number -= 1

		if brace_number == 0:
			# find the global variable
			if line.find('}') != -1 or line.find(')') != -1 or re.search(r'#define', line) is not None or line.find('typedef') != -1: #skip the struct decalration and function declaration also the macro
				continue;
			if re.match(r'//.*', line) is not None or re.match(r'/\*.*', line) is not None:
				continue;
			elif line.find(';') != -1 and re.search(r'\(.*\)', line) is None:#skip the function declaration
				va.append(line)
			elif re.search(r'=.*;', line) is not None:#global variable initialize by function
				va.append(line)
		elif brace_number == 1:
			if re.search(r'=(\s*)\{', line) is not None: #global array assignment
				va.append(line)
		else:
			continue

	fd.close()
	ret['name'] = filename
	ret['globals'] = va
	return ret
	
def main():
	files = filter_c_files(sys.argv[1])
	global_variables = {}
	for fi in files:
		va = filter_globals(fi)
		global_variables[va['name']] = va['globals']

	#print global_variables
	#for var in global_variables:
	#	print "file %s and variable is %s" % var, global_variables[var]
	fd = open('allglobals.txt', 'w+')
	for name in global_variables:
		fd.write(str(name)+'\n')
		for va in global_variables[name]:
			fd.write(str(va))
	fd.close()

if __name__ == '__main__':
	main()
