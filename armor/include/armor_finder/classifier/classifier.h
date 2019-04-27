//
// Created by xinyang on 19-4-19.
//

#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>
#include <vector>
#include <string>
#include <opencv2/core.hpp>

using namespace std;
using namespace Eigen;

class Classifier {
private:
    bool state;

    vector<vector<MatrixXd>> conv1_w, conv2_w;
    vector<double> conv1_b, conv2_b;
    MatrixXd fc1_w, fc2_w;
    VectorXd fc1_b, fc2_b;

    vector<vector<MatrixXd>> load_conv_w(const string &file);
    vector<double> load_conv_b(const string &file);
    MatrixXd load_fc_w(const string &file);
    VectorXd load_fc_b(const string &file);

    MatrixXd softmax(const MatrixXd &input);
    MatrixXd relu(const MatrixXd &input);
    vector<vector<MatrixXd>> apply_bias(const vector<vector<MatrixXd>> &input, const vector<double> &bias);
    vector<vector<MatrixXd>> relu(const vector<vector<MatrixXd>> &input);
    vector<vector<MatrixXd>> max_pool(const vector<vector<MatrixXd>> &input, int size);
    vector<vector<MatrixXd>> mean_pool(const vector<vector<MatrixXd>> &input, int size);
    vector<vector<MatrixXd>> pand(const vector<vector<MatrixXd>> &input, int val);
    MatrixXd conv(const MatrixXd &filter, const MatrixXd &input);
    vector<vector<MatrixXd>> conv2(const vector<vector<MatrixXd>> &filter, const vector<vector<MatrixXd>> &input);
    MatrixXd flatten(const vector<vector<MatrixXd>> &input);

public:
    explicit Classifier(const string &folder);
    ~Classifier() = default;

    MatrixXd calculate(const vector<vector<MatrixXd>> &input);
    explicit operator bool() const;
    int operator()(const cv::Mat &image);
};


#endif //RUNCNN_CLASSIFIER_H
