#include "open_cv_hog_detector.hpp"

using namespace dlib;
using namespace std;

class OpenCVHOGDetector {
private:
    std::vector<cv::Rect> mRets;

public:
    OpenCVHOGDetector() {}

    inline int det(const cv::Mat& src_img) {
        cv::HOGDescriptor hog;
        hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
        std::vector<cv::Rect> found, found_filtered;
        hog.detectMultiScale(src_img, found, 0, cv::Size(8, 8), cv::Size(32, 32), 1.05, 2);

        size_t i, j;
        for (i = 0; i < found.size(); i++) {
            cv::Rect r = found[i];
            for (j = 0; j < found.size(); j++) {
                if (j != i && (r & found[j]) == r) {
                    break;
                }
            }
            if (j == found.size()) {
                found_filtered.push_back(r);
            }
        }

        mRets = found_filtered;
        return found_filtered.size();
    }

    inline std::vector<cv::Rect>& getResult() {
        return mRets;
    }

    ~OpenCVHOGDetector() {}
};