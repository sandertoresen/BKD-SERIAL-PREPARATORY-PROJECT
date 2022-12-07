import os

executables_multiple = [".\program16m",
                        ".\program32m", ".\program64m", ".\program128m", ".\program256m"]

executables_single = [".\program16s",
                      ".\program32s", ".\program64s", ".\program128s", ".\program256s"]

nums = [16, 32, 64, 128, 256]

# for c, ex in enumerate(executables):
#     for i in range(1, 11):
#         name = f'{nums[c]}edge_timings_deletes.txt'
#         name_count = f'{nums[c]}edge_timings_deletes' + str(i) + '.txt'
#         os.system(ex)
#         print(f"[{c}/{len(executables)}] Finished {i}/10")
#         os.rename(name, name_count)

for c in range(len(executables_single)):
    print(
        f"Currently working on {c}/{len(executables_single)} tree: {nums[c]}")
    for i in range(1, 11):
        original_name_single = f"{nums[c]}" + "delete_single.txt"
        single_no_txt = f"{nums[c]}" + "delete_single"

        single_new_name = single_no_txt + str(i) + '.txt'

        os.system(executables_single[c])
        print(f"[Finished {i}/10 singles")
        os.rename(original_name_single, single_new_name)

        original_name_multiple = f"{nums[c]}" + "delete_multiple.txt"
        multiple_no_txt = f"{nums[c]}" + "delete_multiple"

        multiple_new_name = f"{nums[c]}" + "delete_multiple" + f"{i}.txt"
        os.system(executables_multiple[c])
        print(f"[Finished {i}/10 multiples")
        os.rename(original_name_multiple, multiple_new_name)


# filename = "256_timings_inserts.txt"
# filename1 = "256_timings_inserts"
# for i in range(1, 11):
#     single_new_name = filename1 + str(i) + '.txt'
#     os.system(".\program")
#     print(f"[Finished {i}/10")
#     os.rename(filename, single_new_name)
