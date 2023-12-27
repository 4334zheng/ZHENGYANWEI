from random import randint, choice
from PIL import Image, ImageDraw, ImageFont, ImageFilter
import string

# 随机字母
characters = string.ascii_letters + string.digits
def rndChar():
    return choice(characters)
# 生成随机颜色
def randomColor(start=0, end=255):
    return randint(start, end), randint(start, end), randint(start, end)
# 生成随机点坐标
def randomPoint():
    # 需要注意他们的取值范围
    return randint(0, img.width), randint(0, img.height)
# 生成两个随机点坐标
def randomPoints():
    return randomPoint(), randomPoint()

if __name__ == '__main__':
    # 首先创建一个画布，选择RGB模式，设置图片尺寸，颜色为白色
    width = 60 * 4
    height = 60
    img = Image.new(mode="RGB", size=(width, height), color=(255, 255, 255))

    # 创建Font对象
    myfont = ImageFont.truetype("C:/Users/4334/Desktop/字体文件/kumo.ttf", size=50)

    # 创建Draw对象
    draw = ImageDraw.Draw(img, mode="RGB")
    draw.point((200, 100), fill="black")

    # 绘制验证码
    total = 4  # 定义验证码长度
    part = img.width // (total + 2)
    pos = 0  # 相当于指针，指在哪个地方哪个地方就填入对应字符
    res = []  # 存放验证码列表
    for i in range(total):
        pos += part
        r = rndChar()
        res.append(r)
        draw.text((pos, 3 * img.height // 13), text=r, fill=randomColor(30, 200), font=myfont)
    res = ''.join(res)

    # 模糊一下
    img = img.filter(ImageFilter.BLUR)

    imgFinal = Image.new(mode="RGB", size=(width, height), color=(255, 255, 255))
    pixelsFinal = imgFinal.load()
    pixelsTemp = img.load()
    # 进行简单的像素点运算，像素点位置的变换
    for y in range(0, height):
        offset = randint(-1, 1)
        for x in range(0, width):
            newx = x + offset
            # 边界处理
            if newx < 0:
                newx = 0
            elif newx > 239:
                newx = 239
            pixelsFinal[newx, y] = pixelsTemp[x, y]

    draw = ImageDraw.Draw(imgFinal)
    # 添加干扰噪点像素
    for i in range(int(img.width * img.height * 0.01)):
        draw.point(randomPoint(), randomColor(150))

    # 添加干扰线条
    for i in range(4):
        draw.line(randomPoints(), fill=randomColor())

    # 添加干扰弧线
    for i in range(4):
        draw.arc(randomPoints(), 0, randint(0, 180), fill=randomColor())

    imgFinal.show()
    print(res)  # 列出验证码

    with open(r"C:\Users\4334\Desktop\img_path\t.png", "wb") as fp:
        imgFinal.save(fp, format="png")