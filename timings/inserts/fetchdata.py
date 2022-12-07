import linecache


# Get 1% 10%, 20%, 50%, 80%, 90%, 99% 99.9% 99.99%
percentages = [1, 10, 20, 50, 80, 90, 99,
               99.9, 99.99, 99.999, 99.9999, 99.99999]

avg_vals = []
# index 65536 * (2**i)
for c in range(1, 11):
    file_name = "256_timings_inserts" + str(c) + '.txt'
    with open(file_name) as f:
        lines = f.readlines()
    if len(avg_vals):
        for c in range(len(lines)):
            avg_vals[c] += int(lines[c])
    else:
        for c in range(len(lines)):
            avg_vals.append(int(lines[c]))

for c in range(len(avg_vals)):
    avg_vals[c] = avg_vals[c] / 10

gjennomsnitt = 0
for c, i in enumerate(avg_vals):
    if c+1 == len(avg_vals):
        break
    gjennomsnitt += i
print(gjennomsnitt/(len(avg_vals)-1))
# avg_vals_unsorted = avg_vals.copy()
# avg_vals.sort()

# worst_percent_idxs = []
# nodes = len(avg_vals)

# for i in percentages:
#     # worst_percent_idxs.append([(int(nodes/100) * i), i])
#     print(f"Worst {i}% = {avg_vals[int((nodes/100) * i)]}")


# nums = [2, 4, 8, 16, 32, 64, 128, 256]

# avg_vals = []
# # index 65536 * (2**i)
# for c in range(1, 11):
#     file_name = "256_timings_inserts" + str(c) + '.txt'
#     with open(file_name) as f:
#         avg_mine = []
#         lines = f.readlines()

#         for i in range(8):
#             # line = linecache.getline(file, 2**i * 65536)
#             print(2**i * 65536)
#             avg_mine.append(int(lines[2**i * 65536]))

#         if len(avg_vals):
#             for c in range(len(avg_vals)):
#                 avg_vals[c] += avg_mine[c]
#         else:
#             for val in avg_mine:
#                 avg_vals.append(val)


# for c in range(len(avg_vals)):
#     avg_vals[c] = avg_vals[c] / 10

# for c, n in enumerate(nums):
#     print(f"|{n}| Val: {avg_vals[c]}")
