

file_name = "timings_deletes"
file_extension = ".txt"


nums = [2, 4, 8, 16, 32, 64, 128, 256]

for c, tree in enumerate(nums):
    avg_val = 0
    for num in range(1, 11):
        with open(f"{tree}" + file_name + f"{num}" + file_extension) as f:
            for i, line in enumerate(f):  # read rest of lines
                avg_val += int(line)
        f.close()

    avg_val = avg_val / (10)

    print(f"|{tree}| Avg {avg_val}")
