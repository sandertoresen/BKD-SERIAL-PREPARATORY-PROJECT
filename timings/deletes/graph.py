# ---------------------------------------------30 Slowest times:
# Index:974228 time: 118440.0 Tree29.7310791015625
# Index:1149818 time: 132580.0 Tree35.08966064453125
# Index:1193836 time: 134090.0 Tree36.4329833984375
# Index:387940 time: 139070.0 Tree11.8389892578125
# Index:325630 time: 158470.0 Tree9.93743896484375
# Index:428417 time: 160790.0 Tree13.074249267578125
# Index:445144 time: 179530.0 Tree13.584716796875
# Index:896031 time: 183230.0 Tree27.344696044921875
# Index:669289 time: 184570.0 Tree20.425079345703125
# Index:367721 time: 724950.0 Tree11.221954345703125
# Index:983040 time: 96815000.0 Tree30.0
# Index:65536 time: 97293790.0 Tree2.0
# Index:196608 time: 98513190.0 Tree6.0
# Index:720896 time: 99206260.0 Tree22.0
# Index:1114112 time: 100361580.0 Tree34.0
# Index:851968 time: 103277940.0 Tree26.0
# Index:458752 time: 107955490.0 Tree14.0
# Index:589824 time: 109743320.0 Tree18.0
# Index:1245184 time: 110767100.0 Tree38.0
# Index:327680 time: 116700940.0 Tree10.0
# Index:917504 time: 329947540.0 Tree28.0
# Index:1179648 time: 331500000.0 Tree36.0
# Index:655360 time: 333776310.0 Tree20.0
# Index:131072 time: 336547230.0 Tree4.0
# Index:393216 time: 362259260.0 Tree12.0
# Index:262144 time: 1203818170.0 Tree8.0
# Index:1310720 time: 1205365450.0 Tree40.0
# Index:786432 time: 1218636890.0 Tree24.0
# Index:524288 time: 4656385450.0 Tree16.0
# Index:1048576 time: 17514707890.0 Tree32.0

import matplotlib.pyplot as plt
[30,
 2,
 6,
 22,
 34,
 26,
 14,
 18,
 38,
 10,
 28,
 36,
 20,
 4,
 12,
 8,
 40,
 24,
 16,
 32]

worst = [96815000.0,
         97293790.0,
         98513190.0,
         99206260.0,
         100361580.0,
         103277940.0,
         107955490.0,
         109743320.0,
         110767100.0,
         116700940.0,
         329947540.0,
         331500000.0,
         333776310.0,
         336547230.0,
         362259260.0,
         1203818170.0,
         1205365450.0,
         1218636890.0,
         4656385450.0,
         17514707890.0]

for c, i in enumerate(worst):
    worst[c] = i/1000000000


x = range(0, len(worst))
plt.xlabel("Bkd-tree size")
plt.ylabel("Insert time in seconds")
plt.title("20 slowest inserts")
# the 20 worst runs are bulk loadings
plt.xticks(x, [30,
               2,
               6,
               22,
               34,
               26,
               14,
               18,
               38,
               10,
               28,
               36,
               20,
               4,
               12,
               8,
               40,
               24,
               16,
               32])
plt.plot(x, worst, color='green', marker='o', linestyle='dashed')
plt.show()
