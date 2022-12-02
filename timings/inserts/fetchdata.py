
file_name = "timings_inserts"
file_extension = ".txt"

all_arrays = []
for num in range(1, 11):
    with open(file_name + f"{num}" + file_extension) as f:
        array = []
        for i, line in enumerate(f):  # read rest of lines
            array.append(int(line))
            # if i == 2:
            #     break
    f.close()
    all_arrays.append(array)
# for a in all_arrays:
#     print(a)
avg_arr = []

for i in range(len(all_arrays[0])):
    avg = 0
    for arr in all_arrays:
        avg += arr[i]
    avg_arr.append(avg/10)


# biggest = []
# for i in indexes:
#     biggest.append((i, avg_arr[i]))
# for b in biggest:
#     print(b)

# print(avg_arr)
# print("sorted:")
avg_unsorted = avg_arr.copy()
avg_arr.sort()

for i in avg_arr[-30:]:
    # find index
    for c, j in enumerate(avg_unsorted):
        if(j == i):
            print(f"Index:{c} time: {j} Tree{c/32768}")
# Get 1% 10%, 20%, 50%, 80%, 90%, 99% 99.9% 99.99%
# percentages = [1, 10, 20, 50, 80, 90, 99,
#                99.9, 99.99, 99.999, 99.9999, 99.99999]
# worst_percent_idxs = []
# nodes = len(avg_arr)

# for i in percentages:
#     worst_percent_idxs.append([int(nodes/100 * i), i])
#     # print(f"add: {int(nodes/100 * i)}--{i}")


# for i, x in worst_percent_idxs:
#     # find correct index
#     for c, u in enumerate(avg_unsorted):
#         if avg_arr[i] == u:
#             print(f"Index:{c} | {x}% = {avg_arr[i]}ns")
#             break
