#pragma once
#include"FbxModel.h"
#include"Camera.h"

class FbxObject3d
{
public://サブクラス（定数バッファ）
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
	};

public://定数
	//ボーンの最大数
	static const int MAX_BONES = 32;

	//定数バッファ用データ構造体
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};

protected://メンバ変数
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource>constBuffTransform;

	//定数バッファ(スキン)
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffSkin;

private:
	//ID3D12デバイス
	static Microsoft::WRL::ComPtr<ID3D12Device> dev;
	//ルートシグネチャ
	static Microsoft::WRL::ComPtr<ID3D12RootSignature> rootsignature;
	//パイプラインステートオブジェクト
	static Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelinestate;

	//ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	//ローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	//ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	//ローカルワールド変換行列
	XMMATRIX matWorld;
	//モデル
	FbxModel* model = nullptr;

	//フレームの時間
	FbxTime frameTime;
	//アニメーション開始時間
	FbxTime startTime;
	//アニメーション終了時間
	FbxTime endTime;
	//現在時間
	FbxTime currentTime;
	//アニメーション再生中
	bool isPlay = false;




public://メンバ関数
	//初期化
	void Init();

	//グラフィックスパイプラインの設定
	static void CreateGraphicsPipeline();

	//毎フレーム処理
	void Update();

	//描画
	void Draw();

	//モデルのセット
	void SetModel(FbxModel* model) { this->model = model; }

	//setter
	static void SetDevice(Microsoft::WRL::ComPtr<ID3D12Device> dev) { FbxObject3d::dev = dev; }

	//アニメーション開始
	void PlayAnimation();

	//ゲッタ
	XMFLOAT3& GetPosition() { return position; }

	void SetPosition(const XMFLOAT3& pos) { position = pos; }
};