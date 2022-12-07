# Deletes multiple trees (ARRAY_SIZE * size - 1)
# |2| Avg 26862460.0
# |4| Avg 26845230.0
# |8| Avg 26695010.0
# |16| Avg 26353500.0
# |32| Avg 27075790.0
# |64| Avg 28102320.0
# |128| Avg 27102320.0

import matplotlib.pyplot as plt

trees = [2,
         4,
         8,
         16,
         32,
         64,
         128]

part = 1000000

average_time = [
    26862460.0/part,
    26845230.0/part,
    26695010.0/part,
    26353500.0/part,
    27075790.0/part,
    28102320.0/part,
    27102320.0/part]
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


trees_text = [
    "",
    "",
    "",
    "",
    "",
    "",
    "",
]


x = range(0, len(average_time))
plt.xlabel("Kdb-tree size")
plt.ylabel("Average delete in milliseconds")
plt.title("Delete timing multiple trees")
# the 20 worst runs are bulk loadings
plt.xticks(x, trees_text)
plt.plot(x, average_time, color='green', marker='D', linestyle='-')
plt.show()
