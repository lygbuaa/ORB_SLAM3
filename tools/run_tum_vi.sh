#!/bin/bash
# set -ex

PRJ_PATH=/home/hugoliu/github/ORB_SLAM3
BIN_PATH=${PRJ_PATH}/Examples/Stereo/stereo_tum_vi
VOC_PATH=${PRJ_PATH}/Vocabulary/ORBvoc.txt
CONFIG_PATH=${PRJ_PATH}/Examples/Stereo/TUM-VI.yaml
DATA_PATH=/home/hugoliu/github/dataset/tum-vi/dataset-room1_512_16/dso
CAMERA_L_PATH=${DATA_PATH}/cam0/images
CAMERA_R_PATH=${DATA_PATH}/cam1/images
TIME_FILE_PATH=${DATA_PATH}/cam0/times.txt

#"Usage: ./stereo_tum_vi path_to_vocabulary path_to_settings path_to_image_folder1_1 path_to_image_folder2_1 path_to_times_file_1 
# (path_to_image_folder1_2 path_to_image_folder2_2 path_to_times_file_2 ... path_to_image_folder1_N path_to_image_folder2_N path_to_times_file_N) (trajectory_file_name)"
# ${BIN_PATH} ${VOC_PATH} ${CONFIG_PATH} ${DATA_PATH}
${BIN_PATH} ${VOC_PATH} ${CONFIG_PATH} ${CAMERA_L_PATH} ${CAMERA_R_PATH} ${TIME_FILE_PATH}