# ---------------------------------------------30 Slowest times:
# Worst 1% = 20.0
# Worst 10% = 40.0
# Worst 20% = 50.0
# Worst 50% = 60.0
# Worst 80% = 70.0
# Worst 90% = 80.0
# Worst 99% = 100.0
# Worst 99.9% = 1850.0
# Worst 99.99% = 5070.0
# Worst 99.999% = 100423710.0
# Worst 99.9999% = 4576106470.0
# Worst 99.99999% = 1093112409220.0

import matplotlib.pyplot as plt


percentage = [
    # 20.0,
    # 40.0,
    # 50.0,
    # 60.0,
    # 70.0,
    # 80.0,
    100.0,
    1850.0,
    5070.0,
    100423710.0,
    4576106470.0,
    # 1093112409220.0

]

per_x = [
    # 1,
    # 10,
    # 20,
    # 50,
    # 80,
    # 90,
    99,
    99.9,
    99.99,
    99.999,
    99.9999,
    # 99.99999
]

x_tix = [
    # "1%",
    # "10%",
    # "20%",
    # "50%",
    # "80%",
    # "90%",
    "99%",
    "99.9%",
    "99.99%",
    "99.999%",
    "99.9999%",
    # "99.99999%"

]

plt.xlabel("Percentage")
plt.ylabel("Insert in nanoseconds")
plt.title("Insert timing worst percentiles")
plt.xticks(per_x, x_tix)

plt.plot(per_x, percentage, color='r', marker='v', linestyle='-')
plt.show()


# trees_text = [
#     "",
#     "",
#     "",
#     "",
#     "",
#     "",
#     "",
#     ""
# ]

# print(average_time)
# x = range(0, len(average_time))
# plt.xlabel("Kdb-tree size")
# plt.ylabel("Average insert in seconds")
# plt.title("Insert timing bulk loading")
# # the 20 worst runs are bulk loadings
# plt.xticks(x, trees_text)
# plt.plot(x, average_time, color='m', marker='X', linestyle='-')
# plt.show()

# [30,
#  2,
#  6,
#  22,
#  34,
#  26,
#  14,
#  18,
#  38,
#  10,
#  28,
#  36,
#  20,
#  4,
#  12,
#  8,
#  40,
#  24,
#  16,
#  32]
