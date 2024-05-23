
# Import required modules
import cv2
import numpy as np

def drawHough(edges):
    lines = cv2.HoughLinesP(edges, 3, np.pi / 180., 100, minLineLength=50, maxLineGap=10)

    dst = cv2.cvtColor(edges, cv2.COLOR_GRAY2BGR)

    if lines is not None:
        for i in range(lines.shape[0]):
            pt1 = (lines[i][0][0], lines[i][0][1]) # 시작점 좌표 x,y
            pt2 = (lines[i][0][2], lines[i][0][3]) # 끝점 좌표, 가운데는 무조건 0
            cv2.line(dst, pt1, pt2, (0, 0, 255), 2, cv2.LINE_AA)

    return dst

img1_dir = "../saved_img/2024-05-23_20-22-48.png"
#img2_dir = "../saved_img/2024-05-23_23-04-11.png"

kernel = np.ones((5, 5), np.float32)/25

img1 = cv2.imread(img1_dir)
#img2 = cv2.imread(img2_dir)

img1_gray = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
#img2_gray = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)

img1_avg = cv2.filter2D(img1_gray, -1, kernel)
#img2_avg = cv2.filter2D(img2_gray, -1, kernel)

img1_histeq = cv2.equalizeHist(img1_avg)
#img2_histeq = cv2.equalizeHist(img2_avg)

# cv2.imshow("img1", img1_histeq)
# cv2.waitKey(0)
# cv2.imshow("img2", img2_histeq)
# cv2.waitKey(0)

edges1 = cv2.Canny(img1_histeq, 100, 200)
#edges2 = cv2.Canny(img2_histeq, 100, 200)

# cv2.imshow("img1", edges1)
# cv2.waitKey(0)
# cv2.imshow("img2", edges2)
# cv2.waitKey(0)

img1_hough = drawHough(edges1)
#img2_hough = drawHough(edges2)
cv2.imshow("img1", img1_hough)
cv2.waitKey(0)
# cv2.imshow("img2", img2_hough)
# cv2.waitKey(0)




cv2.destroyAllWindows()