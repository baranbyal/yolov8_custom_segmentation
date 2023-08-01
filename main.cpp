#include <iostream>
#include<opencv2/opencv.hpp>

#include<math.h>
//#include "yolov8.h"
//#include "yolov8_onnx.h"
//#include "yolov8_seg.h"
#include "yolov8_seg_onnx.h"
#include<time.h>
#include <chrono>

using namespace std;
using namespace cv;
using namespace dnn;

//template<typename _Tp>
//int yolov8(_Tp& cls,Mat& img,string& model_path)
//{
//
//	Net net;
//	if (cls.ReadModel(net, model_path, false)) {
//		cout << "read net ok!" << endl;
//	}
//	else {
//		return -1;
//	}
//	//生成随机颜色
//	vector<Scalar> color;
//	srand(time(0));
//	for (int i = 0; i < 80; i++) {
//		int b = rand() % 256;
//		int g = rand() % 256;
//		int r = rand() % 256;
//		color.push_back(Scalar(b, g, r));
//	}
//	vector<OutputSeg> result;
//
//
//	if (cls.Detect(img, net, result)) {
//		DrawPred(img, result, cls._className, color);
//	}
//	else {
//		cout << "Detect Failed!" << endl;
//	}
//	system("pause");
//	return 0;
//}

template<typename _Tp>
int yolov8_onnx(_Tp& cls, Mat& img, string& model_path)
{

	if (cls.ReadModel( model_path, false)) {
		cout << "read net ok!" << endl;
	}
	else {
		return -1;
	}
	//生成随机颜色
	vector<Scalar> color;
	srand(time(0));
	for (int i = 0; i < 80; i++) {
		int b = rand() % 256;
		int g = rand() % 256;
		int r = rand() % 256;
		color.push_back(Scalar(b, g, r));
	}
	vector<OutputSeg> result;
	if (cls.OnnxDetect(img, result)) {
		DrawPred(img, result, cls._className, color);
	}
	else {
		cout << "Detect Failed!" << endl;
	}
	//system("pause");
	return 0;
}


int main() {

	string img_path = "./images/337__jpg.rf.1a8d01d7a0690849440f11ff690607cf.jpg";
	//string seg_model_path = "./models/yolov8x-seg.onnx";
	string seg_model_path = "./models/best_2.onnx";
	//string detect_model_path = "./models/yolov8x.onnx";
	Mat img = imread(img_path);

	//Yolov8 task_detect;
	//Yolov8Seg task_segment;
	//Yolov8Onnx task_detect_onnx;
	Yolov8SegOnnx task_segment_onnx;
	auto t_start = std::chrono::high_resolution_clock::now();
	//yolov8(task_detect,img,detect_model_path);    //Opencv detect
	//yolov8(task_segment,img,seg_model_path);   //opencv segment
	//yolov8_onnx(task_detect_onnx,img,detect_model_path);  //onnxruntime detect
	yolov8_onnx(task_segment_onnx,img,seg_model_path); //onnxruntime segment
	auto t_end = std::chrono::high_resolution_clock::now();
	double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();

	std::cout << "Elapsed time: " <<elapsed_time_ms << " ms "<< std::endl;

	return 0;
}


