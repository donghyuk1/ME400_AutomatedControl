import cv2 as cv
import numpy as np

def read_data():
    filename = "../build/CameraCalibrate/mydata.yml"

    # Open the file in read mode
    fs = cv.FileStorage(filename, cv.FILE_STORAGE_READ)

    if not fs.isOpened():
        print("File open failed!")
        return

    # Read the data
    name = fs.getNode("name").string()
    age = int(fs.getNode("age").real())
    pt1_x = int(fs.getNode("point").at(0).real())
    pt1_y = int(fs.getNode("point").at(1).real())
    pt1 = (pt1_x, pt1_y)
    # scores = fs.getNode("scores").mat().flatten().astype(int).tolist()
    mat1 = fs.getNode("data").mat()
    is_resize = bool(int(fs.getNode("is_resize").real()))

    fs.release()

    print(f"name: {name}")
    print(f"age: {age}")
    print(f"point: {pt1}")
    # print(f"scores: {np.array(scores).reshape(1, -1)}")
    print(f"data:\n{mat1}")
    print(f"is_resize: {is_resize}")


if __name__ == "__main__":
    read_data()