import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

#读入图片
image = Image.open('C:/Users/4334/PycharmProjects/pythonProject_test5/view.jpg')

#将原始图片转换为灰度图片
def imgToGray():
    img_gray = image.convert('L')
    img_gray.show()
    img_gray.save('C:/Users/4334/PycharmProjects/pythonProject_test5/img_gray.jpg')

#将图像裁剪到剩下图像的上半部分
def imgToCrop():
    image1 = np.array(image)
    H, W = image1.shape[0], image1.shape[1]
    H1 = H//2
    img_crop = image1[0:H1, :, :]
    plt.imshow(img_crop)
    plt.show()
    plt.imsave('C:/Users/4334/PycharmProjects/pythonProject_test5/img_crop.jpg', img_crop)

#垂直翻转图片
def imgToFlip():
    img_flip_vert = image.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
    img_flip_vert.show()
    img_flip_vert.save('C:/Users/4334/PycharmProjects/pythonProject_test5/img_flip_vert.jpg')

#其他处理：对图片进行任意指定角度的旋转
def imgToRotate():
    print("输入你想翻转的角度：")
    angle = int(input())
    img_rotate = image.rotate(angle)
    img_rotate.show()
    img_rotate.save('C:/Users/4334/PycharmProjects/pythonProject_test5/img_rotate.jpg')

#统一操作
print("现在有一张图片，如图所示\n你可以对图片进行如下操作：\n")
print("1--将图片转换为灰度图片")
print("2--将图片裁剪剩上半部分")
print("3--将图片进行垂直翻转")
print("4--对图片进行指定角度旋转")
print("请输入你想进行的操作编号：")
cnt = int(input())
if cnt == 1:
    imgToGray()
elif cnt == 2:
    imgToCrop()
elif cnt == 3:
    imgToFlip()
elif cnt == 4:
    imgToRotate()
