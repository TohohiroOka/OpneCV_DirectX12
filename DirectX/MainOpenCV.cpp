#include "MainOpenCV.h"
#include "MainEngine.h"
#include <iostream>

using namespace std;
using namespace cv;

MainOpenCV* instance = nullptr;
VideoCapture MainOpenCV::cap = {};
Mat MainOpenCV::frame = {};
int MainOpenCV::isCascade = 0;
CascadeClassifier MainOpenCV::cascade = {};
vector<cv::Rect> MainOpenCV::contour = {};

MainOpenCV::~MainOpenCV()
{
	//すべてのウィンドウを閉じる
	destroyAllWindows();
}

//シングルトンパターン
MainOpenCV* MainOpenCV::GetInstance()
{
	static MainOpenCV instance;
	return &instance;
}

void MainOpenCV::Initialize()
{
	//カメラのセット
	cap = 2;

	//カメラデバイスが正常にオープンしたか確認
	if (!cap.isOpened())
	{
		//読み込みに失敗したときはエラーを出力
		assert(0);
	}

	//カスケード分類器の読み込み
	cascade.load("OpenCV/haarcascades/haarcascade_frontalface_default.xml");
}

void MainOpenCV::Update()
{
	//位置フレームを変数に保存
	cap.read(frame);

	//対象の検出
	isCascade++;
	if (isCascade % 51 == 50)
	{
		cascade.detectMultiScale(frame, contour, 1.1, 5, 0, cv::Size(30, 30));
		isCascade = 0;
	}

	//検出個数分繰り返し
	for (int i = 0; i < contour.size(); i++)
	{
		//矩形の可視化
		rectangle(frame, Point(contour[i].x, contour[i].y),
			Point(contour[i].x + contour[i].width, contour[i].y + contour[i].height), Scalar(255, 255, 255), 1);
	}
}

void MainOpenCV::Draw()
{
	imshow("camera4", frame);
}