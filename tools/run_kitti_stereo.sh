#!/bin/bash
# set -ex

PRJ_PATH=/home/hugoliu/github/ORB_SLAM3
BIN_PATH=${PRJ_PATH}/Examples/Stereo/stereo_kitti
VOC_PATH=${PRJ_PATH}/Vocabulary/ORBvoc.txt
CONFIG_PATH=${PRJ_PATH}/Examples/Stereo/KITTI00-02.yaml
DATA_PATH=/home/hugoliu/github/dataset/kitti/kitti_odom_gray/dataset/sequences/00

# "Usage: ./stereo_kitti path_to_vocabulary path_to_settings path_to_sequence" 
${BIN_PATH} ${VOC_PATH} ${CONFIG_PATH} ${DATA_PATH}