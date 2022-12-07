# Deletes single trees of different sizes (ARRAY_SIZE * size + 1)
# |2| Avg 195080.0
# |4| Avg 102550.0
# |8| Avg 153400.0
# |16| Avg 160470.0
# |32| Avg 162470.0
# |64| Avg 235620.0
# |128| Avg 235040.0
# |256| Avg 314320.0

# Deletes multiple trees (ARRAY_SIZE * size - 1)
# |4| Avg 26465220.0
# |8| Avg 26250380.0
# |16| Avg 26345690.0
# |32| Avg 25632430.0
# |64| Avg 25768070.0
# |128| Avg 26392150.0
# |256| Avg 26432620.0

import matplotlib.pyplot as plt

trees = [  # 2,
    4,
    8,
    16,
    32,
    64,
    128,
    256]

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
    26465220/part,
    26250380/part,
    26345690/part,
    25632430/part,
    25768070/part,
    26392150/part,
    26432620/part]


x = range(0, len(average_time))
plt.xlabel("Kdb-tree size")
plt.ylabel("Average delete in milliseconds")
plt.title("Delete timings multiple trees")
# the 20 worst runs are bulk loadings
plt.xticks(x, trees)
plt.plot(x, average_time, color='green', marker='o', linestyle='dashed')
plt.show()
