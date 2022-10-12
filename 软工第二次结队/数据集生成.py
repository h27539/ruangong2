from faker import Faker
import pandas as pd
import numpy
import random

for m in range(5) :
    fake = Faker(locale='zh_CN')
    user_name = []
    score = []
    # 生成人数
    num = 90
    # 生成信息
    for i in range(num):
        user_name.append(fake.name())
        temp = numpy.random.normal(3, 1)
        while temp < 0 or temp > 4:
            temp = numpy.random.normal(3, 1)
        score.append(format(temp, '.6f'))
    presence = [[1] * 90 for i in range(20)]
    # print(presence)

    temp = random.randint(5, 8)
    for i in range(temp):
        temp1 = random.randint(0, 89)
        for j in range(16):
            temp2 = random.randint(0, 19)
            while presence[temp2][temp1] == 0: temp2 = random.randint(0, 19)
            presence[temp2][temp1] = 0
    for i in range(0, 20):
        temp = random.randint(0, 89)
        presence[i][temp] = 0
        temp = random.randint(0, 89)
        presence[i][temp] = 0
        temp = random.randint(0, 89)
        presence[i][temp] = 0

    data = {'姓名': user_name, '绩点': score, '第1次课': presence[0], '第2次课': presence[1], '第3次课': presence[2],
            '第4次课': presence[3], '第5次课': presence[4], '第6次课': presence[5], '第7次课': presence[6],
            '第8次课': presence[7], '第9次课': presence[8], '第10次课': presence[9], '第11次课': presence[10],
            '第12次课': presence[11], '第13次课': presence[12], '第14次课': presence[13], '第15次课': presence[14],
            '第16次课': presence[15], '第17次课': presence[16], '第18次课': presence[17], '第19次课': presence[18],
            '第20次课': presence[19]}
    # print(data)

    users = pd.DataFrame.from_dict(data)
    # print(users)
    filename = "course"+str(m)+".csv"
    users.to_csv(filename, index=True, )
