TUM_TOOLS_PATH="/home/hugoliu/github/ORB_SLAM3/tools/tum_benchmark_tools/"

# associate.py using timestamp in seconds, but TUM groundtruth provide timestamp in nano-seconds
python3 ${TUM_TOOLS_PATH}/evaluate_ate.py  \
    ${TUM_TOOLS_PATH}/../../output/tum_room1_gt.csv  \
    ${TUM_TOOLS_PATH}/../../output/tum_room1_stereo_traj.txt  \
    --max_difference 2e7  \
    --verbose  \
    --plot ate_tum_vi.png

# KITTI groundtruth using timestamp in seconds, 0.02 sec is ok
python3 ${TUM_TOOLS_PATH}/evaluate_ate.py  \
    ${TUM_TOOLS_PATH}/../../output/kitti00_stereo_gt.csv  \
    ${TUM_TOOLS_PATH}/../../output/kitti00_stereo_traj.txt  \
    --max_difference 0.02  \
    --verbose  \
    --plot ate_kitti.png
