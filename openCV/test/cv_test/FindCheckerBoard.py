# import required libraries
import cv2

# read input image
img = cv2.imread('checkerboard_phone.jpg')
img = cv2.resize(img, dsize=(0, 0), fx=0.3, fy=0.3, interpolation=cv2.INTER_AREA)
# gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
# m, n = img.shape[:2]
# for i in range(m):
#     for j in range(n):
#         #print(gray[i, j])
#         if gray[i, j] < 100:
#             gray[i, j] = 0

# convert the input image to a grayscale
gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

#cv2.equalizeHist( gray, gray )

cv2.imshow( "Source image", gray)
cv2.waitKey(0)


# Find the chess board corners
ret, corners = cv2.findChessboardCorners(gray, (9,6),None)

# if chessboard corners are detected
if ret == True:

    # Draw and display the corners
    img = cv2.drawChessboardCorners(img, (9,6), corners,ret)
    cv2.imshow('Chessboard',img)
    cv2.waitKey(0)
else:
    print("pattern not found!\n")
cv2.destroyAllWindows()
