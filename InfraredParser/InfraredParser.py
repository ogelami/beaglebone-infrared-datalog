import sys

def main(argv):
	if len(argv) < 2:
		sys.stderr.write("Missing argument [filename ...]\n")
		return 1
		
	parseFile(argv[1])
		
def parseFile(file):
	sys.stderr.write("Parsing %s\n" % (file))
	fileHandler = open(file, "r")
	previousTime = 0
	
	for line in fileHandler:
		line = line.replace("\n", "").split(" ")
		time = int(line[1])
#		sys.stderr.write("%d\n" % (int("1") - 1))
		
		if previousTime == 0:
			previousTime = time
			
		sys.stderr.write("%s %d\n" % (line, time - previousTime))
		previousTime = time

	return 1

if __name__ == "__main__":
	mainResults = main(sys.argv)
	input("")
	sys.exit(mainResults)