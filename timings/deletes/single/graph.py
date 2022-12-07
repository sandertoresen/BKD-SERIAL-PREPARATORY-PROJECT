# Deletes single trees of different sizes (ARRAY_SIZE * size + 1)
# |2| Avg 105930.0
# |4| Avg 131150.0
# |8| Avg 156040.0
# |16| Avg 164740.0
# |32| Avg 193350.0
# |64| Avg 218830.0
# |128| Avg 331180.0

import matplotlib.pyplot as plt

trees = [2,
         4,
         8,
         16,
         32,
         64,
         128]

part = 1000000

# average_time = [
#     195080/part,
#     102550/part,
#     153400/part,
#     160470/part,
#     162470/part,
#     235620/part,
#     235040/part,
#     314320/part]
# x = range(0, len(average_time))
# plt.xlabel("Kdb-tree size")
# plt.ylabel("Average delete in milliseconds")
# plt.title("Delete timings single trees")
# # the 20 worst runs are bulk loadings
# plt.xticks(x, trees)
# plt.plot(x, average_time, color='green', marker='o', linestyle='dashed')
# plt.show()


average_time = [
    105930.0/part,
    131150.0/part,
    156040.0/part,
    164740.0/part,
    193350.0/part,
    218830.0/part,
    331180.0/part]


x = range(0, len(average_time))
plt.xlabel("Kdb-tree size")
plt.ylabel("Average time in milliseconds")
plt.title("Delete timing single trees")
# the 20 worst runs are bulk loadings
plt.xticks(x, trees)
plt.plot(x, average_time, color='blue',
         marker='o', linestyle='-')
plt.show()
