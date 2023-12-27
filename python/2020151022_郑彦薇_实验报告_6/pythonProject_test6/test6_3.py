import warnings
warnings.filterwarnings("ignore")
import numpy as np
from PIL import Image
# 此处为路径，获取图像路径存放到paths中
img_path = "C:/Users/4334/Desktop/img_path"
paths = []
for i in range(5):
    paths.append(img_path + '/0' + str(i+1) + '.jpg')
#print(paths)
img_array = ''
img = ''
for i, v in enumerate(paths):
    if i == 0:
        img = Image.open(v)  # 打开图片
        # 此放处将单张图像进行缩为统一大小
        img = img.resize((741, 986), Image.ANTIALIAS)
        img_array = np.array(img)  # 转化为np array对象
    if i > 0:
        img = Image.open(v)
         # 此处将单张图像进行缩放为统一大小
        img = img.resize((741, 986), Image.ANTIALIAS)
        img_array1 = np.array(img)
        img_array = np.concatenate((img_array, img_array1), axis=1)  # 横向拼接
        #img_array = np.concatenate((img_array, img_array1), axis=0)# 纵向拼接
        img = Image.fromarray(img_array)
# 保存图片
img.save('C:/Users/4334/Desktop/img_path/final1.jpg')
#img.save('C:/Users/4334/Desktop/img_path/final2.jpg')
