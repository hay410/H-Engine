#include "FbxModel.h"
#include "DirectXBase.h"

void FbxModel::CreateBuffers(ComPtr<ID3D12Device> dev)
{
	HRESULT result;
	//頂点データの全体サイズ
	UINT sizeVB = static_cast<UINT>(sizeof(VertexFbx) * vertices.size());
	
	//頂点バッファの生成
	result = DirectXBase::Instance()->dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);

	//頂点バッファへのデータ転送
	VertexFbx* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		copy(vertices.begin(), vertices.end(), vertMap);
		vertBuff->Unmap(0, nullptr);
	}

	//頂点バッファビュー(VBV)の作成
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(vertices[0]);

	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices.size());
	
	//インデックスバッファの設定
	result = DirectXBase::Instance()->dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff)
	);

	//インデックスバッファへのデータ転送
	unsigned short* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);

	if (SUCCEEDED(result))
	{
		copy(indices.begin(), indices.end(), indexMap);
	}
	//マップを解除
	indexBuff->Unmap(0, nullptr);

	//インデックスバッファビューの設定
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;

	//テクスチャ画像データ
	const Image* img = scratchImg.GetImage(0, 0, 0);//生データ抽出
	assert(img);
	
	//リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels
	);

	//テクスチャ用バッファの読み取り
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texbuff)
	);

	//データ転送
	result = texbuff->WriteToSubresource(
		0,
		nullptr,		//全領域へコピー
		img->pixels,		//元データアドレス
		(UINT)img->rowPitch,		//1ラインサイズ
		(UINT)img->slicePitch		//全サイズ
	);

	//SRV用デスクリプタヒープを生成
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	descHeapDesc.NumDescriptors = 1;
	result = dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeapSRV));

	//シェーダーリソースビュー作成
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//設定構造体
	D3D12_RESOURCE_DESC resDesc = texbuff->GetDesc();

	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	dev->CreateShaderResourceView(
		texbuff.Get(),
		&srvDesc,
		descHeapSRV->GetCPUDescriptorHandleForHeapStart()
	);


}

FbxModel::~FbxModel()
{
	//FBXシーン解放
	fbxScene->Destroy();
}

void FbxModel::Draw()
{
	//頂点バッファをセット
	DirectXBase::Instance()->cmdList->IASetVertexBuffers(0, 1, &vbView);
	//インデックスバッファをセット
	DirectXBase::Instance()->cmdList->IASetIndexBuffer(&ibView);

	//デスクリプタヒープのセット
	ID3D12DescriptorHeap* ppHeaps[] = { descHeapSRV.Get() };
	DirectXBase::Instance()->cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	//シェーダーリソースビューをセット
	DirectXBase::Instance()->cmdList->SetGraphicsRootDescriptorTable(1, descHeapSRV->GetGPUDescriptorHandleForHeapStart());

	//描画コマンド
	DirectXBase::Instance()->cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);
}
