from PIL import Image


def resize_pic(path, width, height):
    """修改picture文件夹内图片的大小"""
    image = Image.open(path)
    image = image.resize((width, height))
    image.save(path)


if __name__ == '__main__':
    path = "../pictures/building/sourse.png"
    resize_pic(path, 400, 400)
