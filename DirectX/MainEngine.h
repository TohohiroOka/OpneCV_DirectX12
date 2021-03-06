#pragma once
#include "WindowApp.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include"Input.h"
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")
#include<sstream>
#include <iomanip>

using namespace DirectX;
using namespace Microsoft::WRL;

class MainEngine
{
public://クラス内部で使用する
	//深度生成
	void afterInit();

public://メインに書く

	MainEngine() = default;
	~MainEngine();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="gameName">タイトルバー名</param>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	void Initialize(const wchar_t* gameName, int window_width, int window_height);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <returns>ゲームを続けるか</returns>
	bool Update();

	/// <summary>
	/// デバッグ用数字
	/// </summary>
	/// <param name="x">値1</param>
	/// <param name="y">値2</param>
	/// <param name="z">値3</param>
	void debugNum(float x, float y, float z);

	/// <summary>
	/// 描画
	/// </summary>
	void draw();

	/// <summary>
	/// フレームレート固定
	/// </summary>
	void frameRateKeep();

	/// <summary>
	/// エスケープが入力されたら終了する処理
	/// </summary>
	/// <param name="winApp">ウィンドウズインスタンス</param>
	/// <returns>ゲームを続けるか</returns>
	bool gameFin(WindowApp* winApp);

	/// <summary>
	/// DirectXCommonのgetter
	/// </summary>
	/// <returns>DirectXCommonのインスタンス</returns>
	DirectXCommon* GetDXCommon() { return dXCommon; }

	/// <summary>
	/// Inputのgetter
	/// </summary>
	/// <returns>Inputのインスタンス</returns>
	Input* GetInput() { return input; }

	/// <summary>
	/// Cameraのgetter
	/// </summary>
	/// <returns>Cameraのインスタンス</returns>
	Camera* GetCamera() { return camera; }

	/// <summary>
	/// 現在の時間取得
	/// </summary>
	/// <returns></returns>
	LARGE_INTEGER GetTime() { return timeEnd; }

private:

	//WindowAppのインスタンス
	WindowApp* winApp = nullptr;
	//DirectXCommonのインスタンス
	DirectXCommon* dXCommon = nullptr;
	//Inputのインスタンス
	Input* input = nullptr;
	//Cameraのインスタンス
	Camera* camera = nullptr;
	//GameSceneのインスタンス
	GameScene* scene = nullptr;
	//数字表示デバッグ用
	wchar_t str[256] = {};
	//フレームレート固定用
	const float MIN_FREAM_TIME = 1.0f / 60;
	//フレームのカウント
	float frameTime = 0;
	//フレーム始め
	LARGE_INTEGER timeStart;
	//フレーム最後
	LARGE_INTEGER timeEnd;
	//現在フレーム
	LARGE_INTEGER timeFreq;
	//現在FPS
	float fps = 0;
};