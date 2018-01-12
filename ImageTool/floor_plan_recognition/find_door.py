# -*- coding:utf-8 -*-
import cv2
import numpy as np
import time
import random
#########提取门###################
img = cv2.imread("1.png")
gray_door = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
# cv2.imshow("gray_door", gray_door)
# edges = cv2.Canny(gray_door, 50, 200, 0)
# cv2.imshow("canny", edges)


#取阈值
h, w = gray_door.shape[:2]
# for x in range(h):
#     for y in range(w):
#         if gray_door[x, y] > 100:
#             gray_door[x, y] = 255
#         else:
#             gray_door[x, y] = 0
# cv2.imshow("img_contours", gray_door)
# equ = cv2.equalizeHist(gray_door)
# cv2.imshow("equalizeHist", equ)
# for x in range(h):
#     for y in range(w):
#         neg_pic = gray_door[x:x+100, y:y+100]
#         neg_pic = cv2.resize(neg_pic, (500, 500))
#         img_cascade = cv2.CascadeClassifier('./cascade_3.xml')
#         img_door = img_cascade.detectMultiScale(neg_pic,
#                                                 scaleFactor=1.1,
#                                                 minNeighbors=1,
                                                # minSize=(50, 50),
                                                # maxSize=(60, 60),
                                                # flags=cv2.CASCADE_SCALE_IMAGE
                                                # )
        # for (x, y, w, h) in img_door:
        #     cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 0), 1)
        #     cv2.imwrite('result' + '/' + str(x+y) + '.png', neg_pic)
#

# gray_door = cv2.resize(gray_door, (1000, 1000))
img_cascade = cv2.CascadeClassifier('./cascade_5.xml')
img_door = img_cascade.detectMultiScale(gray_door,
                                        scaleFactor=1.1,
                                        minNeighbors=1,
                                        # minSize=(50, 50),
                                        # maxSize=(70, 70),
                                        flags=cv2.CASCADE_SCALE_IMAGE
                                        )
for (x, y, w, h) in img_door:
    cv2.rectangle(gray_door, (x, y), (x+w, y+h), (0, 255, 0), 1)
cv2.imshow('door', gray_door)
cv2.waitKey()








###################"生成训练文件"
# index = 0
# while index < 4000:
#     x = int(random.random() * h)
#     y = int(random.random() * w)
#     pic = gray_door[x:x+100, y:y+100]
#     if pic.size == 0:
#         pass
#     else:
#         cv2.imwrite('result' + '/' + str(index) + '.png', pic)
#     index += 1

# img_1 = cv2.imread("E:\gitlab\\floor_plan_recognition\cascade_training\dataset\pos\\1.png")
# img_2 = cv2.imread("E:\gitlab\\floor_plan_recognition\cascade_training\dataset\pos\\2.png")
# img_3 = cv2.imread("E:\gitlab\\floor_plan_recognition\cascade_training\dataset\pos\\3.png")
# img_4 = cv2.imread("E:\gitlab\floor_plan_recognition\cascade_training\dataset\pos\\4.png")
# idx = 0
# while idx < 2000:
#     cv2.imwrite("E:\gitlab\\floor_plan_recognition\cascade_training\dataset\pos" + "/" + str(idx+5) + ".png", img_1)
#     cv2.imwrite("E:\gitlab\\floor_plan_recognition\cascade_training\dataset\pos" + "/" + str(idx + 6) + ".png", img_2)
#     cv2.imwrite("E:\gitlab\\floor_plan_recognition\cascade_training\dataset\pos" + "/" + str(idx + 7) + ".png", img_3)
#     cv2.imwrite("E:\gitlab\\floor_plan_recognition\cascade_training\dataset\pos" + "/" + str(idx + 8) + ".png", img_4)
#     idx += 1



