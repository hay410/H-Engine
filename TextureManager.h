#pragma once
#include "Singleton.h"
#include <wrl/client.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <vector>
#include <DirectXTex.h>
#include "DescriptorHeapManager.h"


struct Texture {
	LPCWSTR fileName;				//ファイル名
	int IDNum;						//識別番号
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;	//テクスチャバッファ
	//以下は必ず必要ではないがあったら便利
	DirectX::TexMetadata metadata;			//画像のサイズなど、テクスチャとしての各情報が入る
	DirectX::ScratchImage* scratchImg;
	DirectX::Image* image;					//ビットマップ形式での画像データのそのもののアドレスが入る
	DirectX::XMFLOAT4 colorData;				//色を指定してテクスチャを生成する際、このテクスチャがどの色なのかを渡すための変数
};

class TextureManager : public Singleton<TextureManager> {

private:

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescHeap;
	std::vector<Texture> texture;
	std::vector<int> descriptorHeadMgrIndex;		// DescriptorHeapMgr上での保存先インデックス。
	//コンストラクタ
	friend Singleton<TextureManager>;
	TextureManager();

public:
	//画像をロードして識別番号を返す関数、ロード済みだったら識別番号を返す。
	int LoadTexture(LPCWSTR fileName);
	//画像をロードして識別番号を返す関数、ロード済みだったら識別番号を返す。
	int LoadTextureInDescriptorHeapMgr(LPCWSTR fileName);
	//画像を生成して識別番号を返す関数
	int CreateTexture(DirectX::XMFLOAT4 color);
	//レンダーターゲット用のテクスチャを生成して識別番号を返す関数
	int CreateRenderTargetTexture(int width, int height, int mipLevel, int arraySize, DXGI_FORMAT format, float clearColor[4]);
	//識別番号の順番のシェーダーリソースビューを返す。
	D3D12_GPU_DESCRIPTOR_HANDLE GetSRV(int IDNum);
	//ディスクリプタヒープを返す。
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetDescHeap();
	//指定の番号のテクスチャを返す。
	Texture GetTexture(int ID);

};