# -*- coding:utf-8 -*-
import cv2
from scipy import ndimage as ndi
import matplotlib.pyplot as plt
import numpy as np

img = cv2.imread("12.png")
h, w = img.shape[:2]
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
cv2.imshow("gray", gray)

#####
#方法一
#####
edges = cv2.Canny(gray, 50, 200, 0)
# cv2.imshow("canny", edges)
#将canny的边界提取
image, contours, hierarchy = cv2.findContours(edges, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
img_contours = cv2.drawContours(gray, contours, -1, 255, 3)
# cv2.imshow("contours", img_contours)
#对图像进行膨胀
kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))
dilate = cv2.dilate(img_contours, kernel)
# cv2.imshow("dilate", dilate)
#闭操作
close = cv2.morphologyEx(img_contours, cv2.MORPH_CLOSE, kernel)
# cv2.imshow("close", close)

h, w = img.shape[:2]
result = cv2.absdiff(close, dilate)
#取阈值
for x in range(h):
    for y in range(w):
        if result[x, y] < 230:
            result[x, y] = 0
        else:
            result[x, y] = 255
kernel_pic = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))
result_pic = cv2.morphologyEx(result, cv2.MORPH_CLOSE, kernel_pic)
cv2.imshow("img_contours", result_pic)
cv2.imwrite("img_contours.jpg", result_pic)

#####
#方法二
#####
# kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))
# close = cv2.morphologyEx(gray, cv2.MORPH_CLOSE, kernel)
# # close = cv2.GaussianBlur(close, (3, 3), 0)
# cv2.imshow("close", close)
# close_result = close.copy()
# #灰度拉伸
# min_pix, max_pix, min_loc, max_loc = cv2.minMaxLoc(close)
# for x in range(h):
#     for y in range(w):
#         factor = 255.0 / (max_pix - min_pix)
#         close_result[x, y] = factor * (close[x, y] - min_pix)
#         if close_result[x, y] < 60:
#             close_result[x, y] = 0
#         else:
#             close_result[x, y] = 255
#
# # k = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))
# # close_result = cv2.dilate(close_result, k)
# # close_result = cv2.erode(close_result, kernel)
# cv2.imshow("close_result", close_result)
# edges_close = cv2.Canny(close_result, 50, 150, 0)
# cv2.imshow("edges_close", edges_close)
# image, contours, hierarchy = cv2.findContours(edges_close, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
# img_contours = cv2.drawContours(img, contours, -1, (0, 0, 255), 1)
# cv2.imshow("img_contours", img_contours)


# #对图像进行膨胀
# dilate = cv2.dilate(img_contours, kernel)
# cv2.imshow("dilate", dilate)
# #取阈值
# result = cv2.absdiff(close, dilate)
# for x in range(h):
#     for y in range(w):
#         if result[x, y] < 230:
#             result[x, y] = 0
#         else:
#             result[x, y] = 255
# kernel_pic = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))
# result_pic = cv2.morphologyEx(result, cv2.MORPH_CLOSE, kernel_pic)
# cv2.imshow("img_contours", result_pic)
# cv2.imwrite("img_contours.jpg", result_pic)

# #Probabilistic Hough Transform
# minLineLength = 100
# maxLineGap = 0
# close_e = cv2.Canny(close, 50, 200, 0)
# cv2.imshow("close_e", close_e)
# lines = cv2.HoughLinesP(close_e, 1, np.pi/180, minLineLength, maxLineGap)
# for i in range(0, len(lines)):
#     for x1, y1, x2, y2 in lines[i]:
#         cv2.line(img, (x1, y1), (x2, y2), (255, 0, 0), 2)
# cv2.imshow("hough_line", img)

#############提取图例###############
"""
gray_legend = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
# cv2.imshow("gray", gray_legend)

h, w = result.shape[:2]
#取阈值
xx = []
yy = []
for x in range(h-1):
    for y in range(w-1):
        if result[x][y] == result[x][y + 1] and result[x][y] != 0:
            xx.append(x)
        if result[x][y] == result[x + 1][y] and result[x][y] != 0:
            yy.append(y)

xx.sort()    #col[0]为左面的线， col[-1]为最右面的线
yy.sort()    #row[0]为最上面的线, row[-1]为最下面的线
x0, x1 = xx[0], xx[-1]
y0, y1 = yy[0], yy[-1]
for x in range(h):
    for y in range(w):
        if x >= x0 - 5 and x <= x1 + 5 and\
                        y >= y0 - 5 and y <= y1 + 5:
            gray_legend[x, y] = 255
        else:
            pass
cv2.imshow("result", gray_legend)

#图像四部分的图例
legend_1 = gray_legend[0:w, 0:x0]
legend_2 = gray_legend[0:w, x1:w]
legend_3 = gray_legend[0:h, 0:y0]
legend_4 = gray_legend[0:h, y1:h]
# cv2.imshow("legend_1", legend_1)
# cv2.imshow("legend_2", legend_2)
# cv2.imshow("legend_3", legend_3)
# cv2.imshow("legend_4", legend_4)
"""
cv2.waitKey()


