

file_name = "delete_multiple"

nums = [2, 4, 8, 16, 32, 64, 128]

for c, tree in enumerate(nums):
    avg_val = 0
    for run in range(1, 11):
        file_name = f'{nums[c]}delete_multiple' + str(run) + '.txt'
        with open(file_name) as f:
            for i, line in enumerate(f):  # read rest of lines
                avg_val += int(line)
            f.close()
    avg_val = avg_val / (10)
    print(f"|{tree}| Avg {avg_val}")
