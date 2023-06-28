def write_clean(cleaned_arr):
	g = open("clean.csv", "w")
	
	for item in cleaned_arr:
		for idx, attr in enumerate(item):
			if idx == len(item) - 1:
				g.write(str(attr))	
			else:
				g.write(str(attr) + ",")
		g.write("\n")

	g.close()


if __name__ == "__main__":
	f = open("dirty.csv", "r")
	dirty = f.read()

	dirty = dirty.split("\n")[:-1]

	f.close()

	cleaner = []

	for item in dirty:
		cleaner.append(item.split(" "))

	for idx, item in enumerate(cleaner):
		cleaner[idx][0] = int(item[0])
		cleaner[idx][1] = int(item[1])
		cleaner[idx].append(1)

	write_clean(cleaner)

