

# name_count = f'{nums[c]}edge_timings_deletes' + str(i) + '.txt'

# file_name = "256timings_deletes"
# file_extension = ".txt"

# nums = [4, 8, 16, 32, 64, 128, 256]
# for c, tree in enumerate(nums):
#     avg_val = 0
#     for run in range(1, 11):
#         file_name = f'{nums[c]}edge_timings_deletes' + str(run) + '.txt'
#         with open(file_name) as f:
#             for i, line in enumerate(f):  # read rest of lines
#                 avg_val += int(line)
#             f.close()
#     avg_val = avg_val / (10)
#     print(f"|{tree}| Avg {avg_val}")

navn = "4timings_deletesTest.txt"
navn = "64edge_timings_deletes4.txt"
avg_val = 0
vals = 1
with open(navn) as f:
    for i, line in enumerate(f):  # read rest of lines
        avg_val += int(line)
        vals += 1
    f.close()
avg_val /= vals
print(avg_val)


# nums = [4, 8, 16, 32, 64, 128, 256]
# for c, tree in enumerate(nums):
#     avg_val = 0
#     for run in range(1, 11):
#         file_name = f'{nums[c]}edge_timings_deletes' + str(run) + '.txt'
#         with open(file_name) as f:
#             for i, line in enumerate(f):  # read rest of lines
#                 avg_val += int(line)
#             f.close()
#     avg_val = avg_val / (10*100)
#     print(f"|{tree}| Avg {avg_val}")


# for num in range(1, 11):
#     with open(file_name + f"{num}" + file_extension) as f:
#         for i, line in enumerate(f):  # read rest of lines
#             avg_val += int(line)
#     f.close()

# avg_val = avg_val / (10*100)

# print(f"|256| Avg {avg_val}")
