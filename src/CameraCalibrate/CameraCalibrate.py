
# Import required modules 
import cv2
import numpy as np
import os
import glob
import sys

# configuration parameters to camera calibrate
filename = "camparameters.yml"

# read data from yaml file
fs = cv2.FileStorage(filename, cv2.FILE_STORAGE_READ)

if not fs.isOpened():
    print("File open failed!")
    sys.exit(0)

# Read the data from yaml file
is_crop = bool(int(fs.getNode("is_crop").real()))
crop_height_start = int(fs.getNode("crop_height_start").real())
crop_height_end = int(fs.getNode("crop_height_end").real())
crop_width_start = int(fs.getNode("crop_width_start").real())
crop_width_end = int(fs.getNode("crop_width_end").real())
checkerboard_x= int(fs.getNode("checkerboard_size").at(0).real())
checkerboard_y = int(fs.getNode("checkerboard_size").at(1).real())
checkerboard_size = (checkerboard_x, checkerboard_y)
is_resize = bool(int(fs.getNode("is_resize").real()))
scale_x = float(fs.getNode("scale_x").real())
scale_y = float(fs.getNode("scale_y").real())  # Note the typo in the key name

# close fs
fs.release()

# Define the dimensions of checkerboard 
CHECKERBOARD = checkerboard_size


# stop the iteration when specified 
# accuracy, epsilon, is reached or 
# specified number of iterations are completed. 
criteria = (cv2.TERM_CRITERIA_EPS +
            cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)


# Vector for 3D points 
threedpoints = []

# Vector for 2D points 
twodpoints = []


#  3D points real world coordinates 
objectp3d = np.zeros((1, CHECKERBOARD[0]
                      * CHECKERBOARD[1],
                      3), np.float32)
objectp3d[0, :, :2] = np.mgrid[0:CHECKERBOARD[0],
                      0:CHECKERBOARD[1]].T.reshape(-1, 2)
prev_img_shape = None


# Extracting path of individual image stored 
# in a given directory. Since no path is 
# specified, it will take current directory 
# jpg files alone 
images = glob.glob('img/checkerboard*.png')

for filename in images:
    image = cv2.imread(filename)
    if is_crop:
        image = image[crop_height_start:crop_height_end, crop_width_start:crop_width_end]
    if is_resize:
        image = cv2.resize(image, dsize=(0, 0), fx=scale_x, fy=scale_y, interpolation=cv2.INTER_LINEAR)

    #image = cv2.resize(image, dsize=(0, 0), fx=0.5, fy=0.5, interpolation=cv2.INTER_LINEAR)
    grayColor = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Find the chess board corners 
    # If desired number of corners are 
    # found in the image then ret = true 
    ret, corners = cv2.findChessboardCorners(
        grayColor, CHECKERBOARD,
        cv2.CALIB_CB_ADAPTIVE_THRESH
        + cv2.CALIB_CB_FAST_CHECK +
        cv2.CALIB_CB_NORMALIZE_IMAGE)

    # If desired number of corners can be detected then, 
    # refine the pixel coordinates and display 
    # them on the images of checker board 
    if ret == True:
        threedpoints.append(objectp3d)

        # Refining pixel coordinates 
        # for given 2d points. 
        corners2 = cv2.cornerSubPix(
            grayColor, corners, (11, 11), (-1, -1), criteria)

        twodpoints.append(corners2)

        # Draw and display the corners 
        image = cv2.drawChessboardCorners(image,
                                          CHECKERBOARD,
                                          corners2, ret)

    cv2.imshow('img', image)
    cv2.waitKey(0)

cv2.destroyAllWindows()


# Perform camera calibration by 
# passing the value of above found out 3D points (threedpoints) 
# and its corresponding pixel coordinates of the 
# detected corners (twodpoints) 
ret, matrix, distortion, r_vecs, t_vecs = cv2.calibrateCamera(
    threedpoints, twodpoints, grayColor.shape[::-1], None, None)

# Undistortion with new image
grid = cv2.imread('img/checkerboard3.png')
if is_crop:
    grid = grid[crop_height_start:crop_height_end, crop_width_start:crop_width_end]

if is_resize:
    grid = cv2.resize(grid, dsize=(0, 0), fx=scale_x, fy=scale_y, interpolation=cv2.INTER_LINEAR)

h, w = grid.shape[:2]
newcameramtx, roi = cv2.getOptimalNewCameraMatrix(matrix, distortion, (w,h), 0, (w,h))


dst = cv2.undistort(grid, matrix, distortion)#, None, newcameramtx)

cv2.imshow('undistort', dst)
cv2.waitKey(0)

# Displaying required output 
print(" Camera matrix:")
print(matrix)

print("\n Distortion coefficient:")
print(distortion)

print("\n Rotation Vectors:")
print(r_vecs)

print("\n Translation Vectors:")
print(t_vecs)

filename_write = "calibrate.yml"
fs_result = cv2.FileStorage(filename_write, cv2.FILE_STORAGE_WRITE)
if not fs_result.isOpened():
    print("Result File open failed!")
    sys.exit(0)
fs_result.write("camera_matrix", matrix)
fs_result.write("distortion_coeff", distortion)
fs_result.release()

