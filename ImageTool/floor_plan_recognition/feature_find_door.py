# -*- coding:utf-8 -*-
import cv2
import numpy as np
#########提取门###################
img = cv2.imread("1.png")
img_door = cv2.imread("2.png")

gray_door = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
# cv2.imshow("gray_door", gray_door)
# h, w = gray_door.shape[:2]
# img_door = cv2.resize(img_door, (h,w))
#init sift
orb = cv2.ORB_create()
cv2.FastFeatureDetector_create("SIFT")
#find the keypoints and descriptors with sift
keypoint1, descriptor1 = orb.detectAndCompute(img, None)
keypoint2, descriptor2 = orb.detectAndCompute(img_door, None)

#create BFMatcher object
bfmatcher = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True)

#match descriptors
matches = bfmatcher.match(descriptor1, descriptor2)

#sort them in the order of their distance
matches = sorted(matches, key=lambda x:x.distance)

#draw first 10 matches
dst = np.zeros((500, 500), np.uint8)
dst = cv2.drawMatches(img, keypoint1, img_door, keypoint2, matches[:10])

#show image
cv2.imshow("dst", dst)
cv2.waitKey()