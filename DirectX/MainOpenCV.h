#pragma once

#include <opencv2/opencv.hpp>

class MainOpenCV
{
public://静的メンバ関数

private://シングルトンパターン
	MainOpenCV() = default;
	~MainOpenCV();

public://シングルトンパターン
	MainOpenCV(const MainOpenCV& mainOpenCV) = delete;
	MainOpenCV& operator=(const MainOpenCV& mainOpenCV) = delete;

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static MainOpenCV* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	static void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	static void Update();

	/// <summary>
	/// 描画
	/// </summary>
	static void Draw();

private://静的メンバ変数

	MainOpenCV* instance;
	//カメラ保存用変数
	static cv::VideoCapture cap;
	//カメラの再生フレーム
	static cv::Mat frame;
	//分類器にかけるタイミング
	static int isCascade;
	//カスケード分類器格納用
	static cv::CascadeClassifier cascade;
	//矩形格納用
	static std::vector<cv::Rect> contour;
};