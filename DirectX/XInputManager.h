#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <commdlg.h>
#include <basetsd.h>
#include <objbase.h>

#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
#include <XInput.h>
#pragma comment(lib,"xinput.lib")
#else
#include <XInput.h>
#pragma comment(lib,"xinput9_1_0.lib")
#endif

#include <DirectXMath.h>

#include "Singleton.h"

class XInputManager : public Singleton< XInputManager >
{
	friend Singleton< XInputManager >;

private://コンストラクタ&デストラクタ

	XInputManager() {};
	~XInputManager();

private://メンバ構造体

	struct CONTROLLER_STATE
	{
		XINPUT_STATE lastState;
		XINPUT_STATE state;
		DWORD dwResult;
		bool bLockVibration;
		XINPUT_VIBRATION vibration;
	};

public://メンバEnum

	//ゲームパッドキーコンフィグ
	enum PudButton {
		PAD_A = 0,//A
		PAD_B,//B
		PAD_Y,//Y
		PAD_X,//X
		PAD_LB,//LB
		PAD_RB,//RB
		PAD_LT,//LT
		PAD_RT,//RT
		PAD_START,//START
		PAD_BUCK,//BUCK
		PAD_UP,//十字上
		PAD_DOWN,//十字下
		PAD_LEFT,//十字左
		PAD_RIGHT,//十字右
		PAD_LEFT_STICK_PUSH,//左ステック押し込み
		PAD_RIGHT_STICK_PUSH,//右ステック押し込み
	};


public://メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 指定ボタンが押されているか
	/// </summary>
	/// <param name="button">ボタン</param>
	/// <returns>押されているか否か</returns>
	bool PushButton(PudButton button);

	/// <summary>
	/// 指定ボタンのトリガーをチェック
	/// </summary>
	/// <param name="button">ボタン</param>
	/// <returns>押されているか否か</returns>
	bool TriggerButton(PudButton button);

	/// <summary>
	/// 左スティックのX軸チェック
	/// </summary>
	/// <param name="UpDown">Up -> true / Down -> false</param>
	/// <returns>true/false</returns>
	bool LeftStickX(bool UpDown);

	/// <summary>
	/// 左スティックのY軸チェック
	/// </summary>
	/// <param name="LeftRight">Left -> true / Right -> false</param>
	/// <returns>true/false</returns>
	bool LeftStickY(bool LeftRight);

	/// <summary>
	/// 右スティックのX軸チェック
	/// </summary>
	/// <param name="UpDown">Up -> true / Down -> false</param>
	/// <returns>true/false</returns>
	bool RightStickX(bool UpDown);

	/// <summary>
	/// 右スティックのY軸チェック
	/// </summary>
	/// <param name="LeftRight">Left -> true / Right -> false</param>
	/// <returns>true/false</returns>
	bool RightStickY(bool LeftRight);

	/// <summary>
	/// 左スティックのX軸トリガーでチェック
	/// </summary>
	/// <param name="UpDown">Up -> true / Down -> false</param>
	/// <returns>true/false</returns>
	bool TriggerLeftStickX(bool UpDown);

	/// <summary>
	/// 左スティックのY軸トリガーでチェック
	/// </summary>
	/// <param name="LeftRight">Left -> true / Right -> false</param>
	/// <returns>true/false</returns>
	bool TriggerLeftStickY(bool LeftRight);

	/// <summary>
	/// 右スティックのX軸トリガーでチェック
	/// </summary>
	/// <param name="UpDown">Up -> true / Down -> false</param>
	/// <returns>true/false</returns>
	bool TriggerRightStickX(bool UpDown);

	/// <summary>
	/// 右スティックのY軸トリガーでチェック
	/// </summary>
	/// <param name="LeftRight">Left -> true / Right -> false</param>
	/// <returns>true/false</returns>
	bool TriggerRightStickY(bool LeftRight);

	/// <summary>
	/// ゲームパッドの左スティックの傾きを取得
	/// </summary>
	/// <returns>ゲームパッドの左スティックの傾き(-1〜1)</returns>
	DirectX::XMFLOAT2 GetPadLStickIncline();

	/// <summary>
	/// ゲームパッドの右スティックの傾きを取得
	/// </summary>
	/// <returns>ゲームパッドの右スティックの傾き(-1〜1)</returns>
	DirectX::XMFLOAT2 GetPadRStickIncline();

	/// <summary>
	/// ゲームパッドの左スティックの角度を取得
	/// </summary>
	/// <returns>ゲームパッドの左スティックの角度</returns>
	float GetPadLStickAngle();

	/// <summary>
	/// ゲームパッドの右スティックの角度を取得
	/// </summary>
	/// <returns>ゲームパッドの右スティックの角度</returns>
	float GetPadRStickAngle();

	/// <summary>
	/// 振動開始
	/// </summary>
	void StartVibration();

	/// <summary>
	/// 振動開始
	/// </summary>
	void EndVibration();

private://メンバ変数

	CONTROLLER_STATE g_Controllers;
};