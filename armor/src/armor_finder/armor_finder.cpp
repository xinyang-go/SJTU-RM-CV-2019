//
// Created by xinyang on 19-3-27.
//
#define LOG_LEVEL LOG_NONE
#include <log.h>
#include <options/options.h>
#include <show_images/show_images.h>
#include <opencv2/highgui.hpp>
#include <armor_finder/armor_finder.h>

std::map<int, string> id2name = {
        {-1, "OO"},{ 0, "NO"},
        { 1, "B1"},{ 2, "B2"},{ 3, "B3"},{ 4, "B4"},{ 5, "B5"},{ 6, "B7"},{ 7, "B8"},
        { 8, "R1"},{ 9, "R2"},{10, "R3"},{11, "R4"},{12, "R5"},{13, "R7"},{14, "R8"},
};

std::map<string, int> name2id = {
        {"OO", -1},{"NO",  0},
        {"B1",  1},{"B2",  2},{"B3",  3},{"B4",  4},{"B5",  5},{"B7",  6},{"B8",  7},
        {"R1",  8},{"R2",  9},{"R3", 10},{"R4", 11},{"R5", 12},{"R7", 13},{"R8", 14},
};

ArmorFinder::ArmorFinder(uint8_t &color, Serial &u, string paras_folder, const uint8_t &use) :
            serial(u),
            enemy_color(color),
            state(STANDBY_STATE),
            classifier(std::move(paras_folder)),
            contour_area(0),
            use_classifier(use),
            boxid(-1)
            {
}

void ArmorFinder::run(cv::Mat &src) {
    static int tracking_cnt = 0;
    cv::Mat src_use;
    src_use = src.clone();

    if(show_armor_box){
        showArmorBox("box", src, armor_box, boxid);
        cv::waitKey(1);
    }
//    stateSearchingTarget(src_use);
//    return;
    switch (state){
        case SEARCHING_STATE:
            if(stateSearchingTarget(src_use)){
                if((armor_box & cv::Rect2d(0, 0, 640, 480)) == armor_box) {
                    if(!classifier && use_classifier){
                        cv::Mat roi = src_use.clone()(armor_box), roi_gray;
                        cv::cvtColor(roi, roi_gray, CV_RGB2GRAY);
                        cv::threshold(roi_gray, roi_gray, 180, 255, cv::THRESH_BINARY);
                        contour_area = cv::countNonZero(roi_gray);
                    }
                    tracker = TrackerToUse::create();
                    tracker->init(src_use, armor_box);
                    state = TRACKING_STATE;
                    tracking_cnt = 0;
                    LOGM(STR_CTR(WORD_LIGHT_CYAN, "into track"));
                }
            }
            break;
        case TRACKING_STATE:
            if(++tracking_cnt>100 || !stateTrackingTarget(src_use)){
                state = SEARCHING_STATE;
                LOGM(STR_CTR(WORD_LIGHT_YELLOW ,"into search!"));
            }
            break;
        case STANDBY_STATE:
        default:
            stateStandBy();
    }
}

#define FOCUS_PIXAL_8MM  (1488)
#define FOCUS_PIXAL_5MM  (917)
#define FOCUS_PIXAL      FOCUS_PIXAL_5MM

bool sendTarget(Serial& serial, double x, double y, double z) {
	static short x_tmp, y_tmp, z_tmp;
	static time_t last_time = time(nullptr);
	static int fps;
	uint8_t buff[8];

	time_t t = time(nullptr);
	if (last_time != t) {
		last_time = t;
		cout << "fps:" << fps << ", (" << x << "," << y << "," << z << ")" << endl;
		fps = 0;
	}
	fps += 1;

	x_tmp = static_cast<short>(x * (32768 - 1) / 100);
	y_tmp = static_cast<short>(y * (32768 - 1) / 100);
	z_tmp = static_cast<short>(z * (32768 - 1) / 1000);

	buff[0] = 's';
	buff[1] = static_cast<char>((x_tmp >> 8) & 0xFF);
	buff[2] = static_cast<char>((x_tmp >> 0) & 0xFF);
	buff[3] = static_cast<char>((y_tmp >> 8) & 0xFF);
	buff[4] = static_cast<char>((y_tmp >> 0) & 0xFF);
	buff[5] = static_cast<char>((z_tmp >> 8) & 0xFF);
	buff[6] = static_cast<char>((z_tmp >> 0) & 0xFF);
	buff[7] = 'e';
	
	return serial.WriteData(buff, sizeof(buff));
}

bool ArmorFinder::sendBoxPosition() {
    auto rect = armor_box;
    double dx = rect.x + rect.width/2 - 320 - 10;
    double dy = rect.y + rect.height/2 - 240 - 20;
    double yaw   = atan(dx / FOCUS_PIXAL) * 180 / 3.14159265459;
    double pitch = atan(dy / FOCUS_PIXAL) * 180 / 3.14159265459;
//    cout << yaw << endl;
    return sendTarget(serial, yaw, -pitch, 0);
}