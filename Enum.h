#pragma once

//3D図形データID
enum ShapeDataID {
	SHAPEDATA_CONE,
	SHAPEDETA_CLYINDER,
	SHAPEDATA_SPHERE
};

//どんな投影をするかのID
enum projectionID {
	PROJECTIONID_UI,						//平行投影
	PROJECTIONID_OBJECT,					//透視投影
	PROJECTIONID_BILLBOARD					//ビルボード
};

//どんなブレンドをするかのID
enum blendID {
	BLENDMODE_ADD,							//加算合成
	BLENDMODE_ALPHA							//アルファブレンド
};

//パイプラインID	PIPLINE _ (型名) _ (処理) _ (合成)
enum PipelineID {
	/*ライン用*/
	PIPELINE_LINE_ALPHA,								//ライン用												アルファブレンド		定数1つ、テクスチャ1つ
	/*スプライト用*/
	PIPELINE_SPRITE_ADD,								//スプライト用												加算合成				定数1つ、テクスチャ1つ
	PIPELINE_SPRITE_ALPHA,							//スプライト用												アルファブレンド		定数1つ、テクスチャ1つ
	/*オブジェクト用*/
	PIPELINE_OBJECT_SIMPLE_COLOR_ALPHA,
	PIPELINE_OBJECT_LIGHT_ALPHA,						//3Dオブジェクト用			ライティング						アルファブレンド		定数3つ、テクスチャ1つ
	PIPELINE_OBJECT_NOLIGHT_ALPHA,					//3Dオブジェクト用			ライティング無し					アルファブレンド		定数3つ、テクスチャ1つ
	PIPELINE_OBJECT_NOLIGHT_ALPHA_F,					//3Dオブジェクト用			ライティング無し 前面カリング			アルファブレンド		定数3つ、テクスチャ1つ
	PIPELINE_OBJECT_OUTLINE_ALPHA,					//3Dオブジェクト用			アウトライン用						アルファブレンド		定数3つ、テクスチャ1つ
	PIPELINE_OBJECT_TOONSHADER_ALPHA,				//3Dオブジェクト用			トゥーンシェーダー					アルファブレンド		定数3つ、テクスチャ1つ
	/*GSパーティクル用*/
	PIPELINE_GSPARTICLE_NOLIGHT_ALPHA,				//GSパーティクル用			点から立体を生成					アルファブレンド		定数1つ、テクスチャ1つ
	/*マルチパスレンダリング用*/
	PIPELINE_MULTIPATH_NORMAL_ADD,					//マルチパスレンダリング用									加算合成				定数2つ、テクスチャ1つ
	PIPELINE_MULTIPATH_NORMAL_ALPHA,					//マルチパスレンダリング用									アルファブレンド		定数2つ、テクスチャ1つ
	PIPELINE_MULTIPATH_MONOCHROME_ADD,				//マルチパスレンダリング用	モノクロ化						加算合成				定数2つ、テクスチャ1つ
	PIPELINE_MULTIPATH_MONOCHROME_ALPHA,				//マルチパスレンダリング用	モノクロ化						アルファブレンド		定数2つ、テクスチャ1つ
	PIPELINE_MULTIPATH_GAUSSIAN_X_ALPHA,				//マルチパスレンダリング用	ガウスぼかしをかける				アルファブレンド		定数2つ、テクスチャ1つ
	PIPELINE_MULTIPATH_GAUSSIAN_Y_ALPHA,				//マルチパスレンダリング用	ガウスぼかしをかける				アルファブレンド		定数2つ、テクスチャ1つ
};