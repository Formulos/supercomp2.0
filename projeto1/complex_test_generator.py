import numpy as np

rand = np.random.randint
f= open("rand_test","w+")
f.write("20000 20000 0.1"+"\n")
f.write("1000"+"\n")
for i in range(1000):
    f.write('{} {} {} {} {} {} {}'.format(rand(1,50),rand(2,10),rand(2,10),rand(11,19980),rand(11,19980),rand(-100,100),rand(-100,100))+"\n")
f.write("1 10000 10000")
f.close()