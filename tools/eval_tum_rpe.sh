# python3 tum_benchmark_tools/evaluate_rpe.py output/groundtruth.csv output/vio.csv --verbose
TUM_TOOLS_PATH="/home/hugoliu/github/ORB_SLAM3/tools/tum_benchmark_tools/"

# associate.py using timestamp in seconds, but groundtruth provide timestamp in nano-seconds
python3 ${TUM_TOOLS_PATH}/evaluate_rpe.py  \
    ${TUM_TOOLS_PATH}/../../output/tum_room1_gt.csv  \
    ${TUM_TOOLS_PATH}/../../output/tum_room1_stereo_traj.txt  \
    --verbose  \
    # --fixed_delta \
    # --plot rpe_tum_vi.png

python3 ${TUM_TOOLS_PATH}/evaluate_rpe.py  \
    ${TUM_TOOLS_PATH}/../../output/kitti00_stereo_gt.csv  \
    ${TUM_TOOLS_PATH}/../../output/kitti00_stereo_traj.txt  \
    --verbose  \
    # --fixed_delta \
    # --plot rpe_kitti.png
