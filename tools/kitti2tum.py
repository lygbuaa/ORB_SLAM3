#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import os
#pip install numba scipy numpy-quaternion
import quaternion

def load_kitti_pose(pose_file_path, time_file_path, output_file_path):
    """Load ground truth poses (T_w_cam0) from file."""
    # pose_file = os.path.join(self.pose_path, self.sequence + '.txt')

    # Read and parse the poses
    poses = []
    times = []
    try:
        with open(pose_file_path, 'r') as fin:
            poses = fin.readlines()
            print("load poses {} lines".format(len(poses)))

        with open(time_file_path, 'r') as fin:
            times = fin.readlines()
            print("load times {} lines".format(len(times)))

        assert len(poses) == len(times)

        with open(output_file_path, "w") as fout:
            for i in range(len(poses)):
                pose = poses[i]
                T_w_cam0 = np.fromstring(pose, dtype=float, sep=' ')
                T_w_cam0 = T_w_cam0.reshape(3, 4)
                # print("pose[{}]: {}".format(i, T_w_cam0))
                # print("x: {}, y: {}, z: {}".format(T_w_cam0[0][3], T_w_cam0[1][3], T_w_cam0[2][3]))
                rot = T_w_cam0[:, 0:3]
                q = quaternion.from_rotation_matrix(rot)
                # print("w: {}, x: {}, y: {}, z: {}".format(q.w, q.x, q.y, q.z))
                t_s = float(times[i])
                ## timestamp[ns],tx,ty,tz,qw,qx,qy,qz
                tum_line = "{:.10f} {:.10f} {:.10f} {:.10f} {:.10f} {:.10f} {:.10f} {:.10f}\n".format(t_s, T_w_cam0[0][3], T_w_cam0[1][3], T_w_cam0[2][3], q.w, q.x, q.y, q.z)
                print("tum_line: {}".format(tum_line))
                fout.writelines(tum_line)

    except Exception as err:
        print("load kitti pose error: {}".format(err))


if __name__ == "__main__":
    pose_file_path="/home/hugoliu/github/dataset/kitti/kitti_odom_poses/dataset/poses/00.txt"
    time_file_path="/home/hugoliu/github/dataset/kitti/kitti_odom_gray/dataset/sequences/00/times.txt"
    output_file_path="../output/kitti00_stereo_gt.csv"
    load_kitti_pose(pose_file_path, time_file_path, output_file_path)