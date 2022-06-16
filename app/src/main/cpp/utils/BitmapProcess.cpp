//
// Created by huzongyao on 2021/3/2.
//

#include "BitmapProcess.hpp"

int processBmp(void *pixels, AndroidBitmapInfo &info, const char *options) {
    Mat image(info.height, info.width, CV_8UC4, pixels);
    auto opts = json::parse(options);
    std::string action = opts["action"];
    Mat gray;
    cvtColor(image, gray, COLOR_RGBA2GRAY);
    if (action == "grayScale") {
        cvtColor(gray, image, COLOR_GRAY2RGBA);
    } else if (action == "markFace") {
        std::string cascadePath = opts["cascade"];
        CascadeClassifier cascade(cascadePath);
        std::vector<Rect> faces;
        cascade.detectMultiScale(image, faces);
        Scalar rectColor(255, 11, 0);
        for (const auto &face : faces) {
            rectangle(image, face, rectColor, 10);
        }
    }
    return 0;
}
