#pragma once

#include <opencv2/opencv.hpp>
#include "ViwoUtils.h"

namespace stereo
{

/* opencv/samples/cpp/stereo_match.cpp */
class CvStereoSgbm
{
private:
    uint64_t average_us_ = 0;
    cv::Ptr<cv::StereoSGBM> sgbm_;
    int numberOfDisparities_;
    constexpr static int DATASET_IMG_W_ = 1242;

public:
    CvStereoSgbm(const int disp_max=170)
    {
        numberOfDisparities_ = disp_max;
        init_sgbm();
        fprintf(stderr, "[sgbm] CvStereoSgbm init: %d\n", disp_max);
    }

    ~CvStereoSgbm(){}

    void init_sgbm(){
        /*
        minDisparity	Minimum possible disparity value. Normally, it is zero but sometimes rectification algorithms can shift images, so this parameter needs to be adjusted accordingly.
        numDisparities	Maximum disparity minus minimum disparity. The value is always greater than zero. In the current implementation, this parameter must be divisible by 16.
        blockSize	Matched block size. It must be an odd number >=1 . Normally, it should be somewhere in the 3..11 range.
        P1	The first parameter controlling the disparity smoothness. See below.
        P2	The second parameter controlling the disparity smoothness. The larger the values are, the smoother the disparity is. P1 is the penalty on the disparity change by plus or minus 1 between neighbor pixels. P2 is the penalty on the disparity change by more than 1 between neighbor pixels. The algorithm requires P2 > P1 . See stereo_match.cpp sample where some reasonably good P1 and P2 values are shown (like 8*number_of_image_channels*blockSize*blockSize and 32*number_of_image_channels*blockSize*blockSize , respectively).
        disp12MaxDiff	Maximum allowed difference (in integer pixel units) in the left-right disparity check. Set it to a non-positive value to disable the check.
        preFilterCap	Truncation value for the prefiltered image pixels. The algorithm first computes x-derivative at each pixel and clips its value by [-preFilterCap, preFilterCap] interval. The result values are passed to the Birchfield-Tomasi pixel cost function.
        uniquenessRatio	Margin in percentage by which the best (minimum) computed cost function value should "win" the second best value to consider the found match correct. Normally, a value within the 5-15 range is good enough.
        speckleWindowSize	Maximum size of smooth disparity regions to consider their noise speckles and invalidate. Set it to 0 to disable speckle filtering. Otherwise, set it somewhere in the 50-200 range.
        speckleRange	Maximum disparity variation within each connected component. If you do speckle filtering, set the parameter to a positive value, it will be implicitly multiplied by 16. Normally, 1 or 2 is good enough.
        mode	Set it to StereoSGBM::MODE_HH to run the full-scale two-pass dynamic programming algorithm. It will consume O(W*H*numDisparities) bytes, which is large for 640x480 stereo and huge for HD-size pictures. By default, it is set to false .
        */
        sgbm_ = cv::StereoSGBM::create(0, 16, 3);
        // numberOfDisparities_ = ((DATASET_IMG_W_/8) + 15) & -16;
        fprintf(stderr, "[sgbm] numberOfDisparities_: %d\n", numberOfDisparities_);
        int sgbmWinSize = 3;
        int cn = 3; //image channel
        sgbm_->setPreFilterCap(63);
        sgbm_->setBlockSize(sgbmWinSize);
        sgbm_->setP1(8*cn*sgbmWinSize*sgbmWinSize);
        sgbm_->setP2(32*cn*sgbmWinSize*sgbmWinSize);
        sgbm_->setMinDisparity(0);
        sgbm_->setNumDisparities(numberOfDisparities_);
        sgbm_->setUniquenessRatio(10);
        sgbm_->setSpeckleWindowSize(100);
        sgbm_->setSpeckleRange(32);
        sgbm_->setDisp12MaxDiff(1);
        sgbm_->setMode(cv::StereoSGBM::MODE_SGBM);
    }

    void save_disp(cv::Mat disp8, double timestamp=1.0f, std::string path="./"){
        ViwoUtils::MakeDir(path);
        std::string tstr = std::to_string(timestamp);
        std::string filepath = path + "/" + tstr + ".disp.png";
        cv::imwrite(filepath.c_str(), disp8);
    }

    cv::Mat run(const cv::Mat& left_img, const cv::Mat& right_img, double timestamp=1.0f, bool save_flag=false){
        cv::Mat disp;

        /* sgbm output is CV_16S */
        sgbm_->compute(left_img, right_img, disp);

        if(save_flag){
            cv::Mat disp8;
            disp.convertTo(disp8, CV_8U, 255/(numberOfDisparities_*16.0f));
            // cv::namedWindow("kitti", cv::WINDOW_NORMAL);
            // cv::imshow("kitti", disp8);
            // cv::waitKey(1000);
            save_disp(disp8, timestamp, "./disp/");
        }

        return disp;
    }

};

}
