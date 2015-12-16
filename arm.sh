#########################################################################
# File Name: arm.sh
# Author: YangShuoLiu
# mail: yangshuoliu@sina.com
# Created Time: 2015年12月05日 星期六 22时18分34秒
#########################################################################
#!/bin/bash

arm-linux-g++ -Isrc -L. -lopencv_core -lopencv_imgproc -lopencv_features2d  -lopencv_ml -lopencv_flann  -lopencv_photo  -lopencv_gpu  -lpthread -lrt  src/main.cpp src/V4L2.cpp src/Ccom.cpp src/com.c
