#include "DirectXBase.h"
#include <cassert>
#include "struct.h"
#include "Input.h"


WindowsAPI DirectXBase::windowsAPI{};
ComPtr<ID3D12Debug> DirectXBase::debugController{};
ComPtr<ID3D12Device5> DirectXBase::dev{};
ComPtr<IDXGIFactory6> DirectXBase::dxgiFactory{};
vector<ComPtr<IDXGIAdapter1>> DirectXBase::adapters{};
ComPtr<IDXGIAdapter1> DirectXBase::tmpAdapter{};
vector<D3D_FEATURE_LEVEL> DirectXBase::levels{};
D3D_FEATURE_LEVEL DirectXBase::featureLevel{};
ComPtr<IDXGISwapChain4> DirectXBase::swapchain{};
ComPtr<ID3D12CommandAllocator> DirectXBase::cmdAllocator{};
ComPtr<ID3D12GraphicsCommandList4> DirectXBase::cmdList{};
ComPtr<ID3D12CommandQueue> DirectXBase::cmdQueue{};
ComPtr<ID3D12DescriptorHeap> DirectXBase::rtvHeaps{};
ComPtr<ID3D12Resource> DirectXBase::depthBuffer{};
ComPtr<ID3D12DescriptorHeap> DirectXBase::dsvHeap{};
vector<ComPtr<ID3D12Resource>> DirectXBase::backBuffers{};
D3D12_DESCRIPTOR_HEAP_DESC DirectXBase::heapDesc{};
ComPtr<ID3D12Fence> DirectXBase::fence{};
UINT64 DirectXBase::fenceVal{};
IDirectInput8* DirectXBase::dinput{};
IDirectInputDevice8* DirectXBase::devkeybord{};
IDirectInputDevice8* DirectXBase::devmouse{};

DirectXBase::DirectXBase() {
	backBuffers.resize(2);
}

void DirectXBase::Init() {
#ifdef _DEBUG
	//�f�o�b�O���C���[�̗L����
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
#endif

	//�E�B���h�E������
	windowsAPI.Init();

	//DXGI�t�@�N�g���[�̐���
	HRESULT result = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));

	//�O���t�B�b�N�X�A�_�v�^�[�̑I��
	ComPtr<IDXGIAdapter1> tmpAdapter = nullptr;
	for (int i = 0;
		dxgiFactory->EnumAdapters1(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND;
		i++)
	{
		adapters.push_back(tmpAdapter);						//���I�z��ɒǉ�����
	}
	//�ǉ����ꂽ�A�_�v�^�[�I�u�W�F�N�g���d������
	for (int i = 0; i < adapters.size(); i++)
	{
		DXGI_ADAPTER_DESC1 adesc;
		adapters[i]->GetDesc1(&adesc);						//�A�_�v�^�[�̏����擾
		// �\�t�g�E�F�A�f�o�C�X�����
		if (adesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
			continue;
		}
		wstring strDesc = adesc.Description;				//�A�_�v�^�[��
		// Intel UHD Graphics�i�I���{�[�h�O���t�B�b�N�j�����
		if (strDesc.find(L"Intel") == wstring::npos)
		{
			tmpAdapter = adapters[i];						//�̗p
			break;
		}
	}

	//�f�o�C�X�̐���
	//levels.push_back(D3D_FEATURE_LEVEL_12_1);
	levels.push_back(D3D_FEATURE_LEVEL_12_0);
	levels.push_back(D3D_FEATURE_LEVEL_11_1);
	levels.push_back(D3D_FEATURE_LEVEL_11_0);
	for (int i = 0; i < levels.size(); i++)
	{
		//�̗p�����A�_�v�^�[�Ńf�o�C�X�𐶐�
		result = D3D12CreateDevice(tmpAdapter.Get(), levels[i], IID_PPV_ARGS(&dev));
		if (result == S_OK)
		{
			//�f�o�C�X�𐶐��ł������_�Ń��[�v�𔲂���
			featureLevel = levels[i];
			break;
		}
	}

	//�R�}���h�A���P�[�^�̐���
	result = dev->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&cmdAllocator));

	//�R�}���h���X�g�̐���
	result = dev->CreateCommandList(0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		cmdAllocator.Get(), nullptr,
		IID_PPV_ARGS(&cmdList));

	//�R�}���h�L���[�̐���
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc{};
	result = dev->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&cmdQueue));

	//�X���b�v�`�F�[���̐���
	ComPtr<IDXGISwapChain1> swapChain1;
	DXGI_SWAP_CHAIN_DESC1 swapchainDesc{};
	swapchainDesc.Width = 1280;
	swapchainDesc.Height = 720;
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;			//�F���̏���
	swapchainDesc.SampleDesc.Count = 1;							//�}���`�T���v�����Ȃ�
	swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;			//�o�b�N�o�b�t�@�p
	swapchainDesc.BufferCount = 2;								//�o�b�t�@�����Q�ɐݒ�
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;	//�t���b�v��͔j��
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	result = dxgiFactory->CreateSwapChainForHwnd(
		cmdQueue.Get(),
		windowsAPI.hwnd,
		&swapchainDesc,
		nullptr,
		nullptr,
		&swapChain1);
	//��������IDXGISwapChain1�̃I�u�W�F�N�g��ϊ�����
	swapChain1.As(&swapchain);

	//�����_�[�^�[�Q�b�g�r���[�̐���
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;				//�����_�[�^�[�Q�b�g�r���[
	heapDesc.NumDescriptors = 2;								//���\�̂Q��
	dev->CreateDescriptorHeap(&heapDesc,
		IID_PPV_ARGS(&rtvHeaps));
	//�����_�[�^�[�Q�b�g�r���[�𗠕\2������
	for (int i = 0; i < 2; i++)
	{
		// �X���b�v�`�F�[������o�b�t�@���擾
		result = swapchain->GetBuffer(i, IID_PPV_ARGS(&backBuffers[i]));
		// �f�X�N���v�^�q�[�v�̃n���h�����擾
		CD3DX12_CPU_DESCRIPTOR_HANDLE handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
			rtvHeaps->GetCPUDescriptorHandleForHeapStart(), i, dev->GetDescriptorHandleIncrementSize(heapDesc.Type));
		// �����_�[�^�[�Q�b�g�r���[�̐���
		dev->CreateRenderTargetView(
			backBuffers[i].Get(),
			nullptr,
			handle);
	}

	//���\�[�X����
	CD3DX12_RESOURCE_DESC depthResDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_D32_FLOAT,
		window_width,
		window_height,
		1, 0,
		1, 0,
		D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
	);
	//���\�[�X����
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&depthResDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1, 0.0f),
		IID_PPV_ARGS(&depthBuffer)
	);

	//�[�x�o�b�t�@�r���[����
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	result = dev->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dev->CreateDepthStencilView(
		depthBuffer.Get(),
		&dsvDesc,
		dsvHeap->GetCPUDescriptorHandleForHeapStart()
	);

	//�t�F���X�̐���
	result = dev->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));

	//DirectInput�I�u�W�F�N�g�̐���
	result = DirectInput8Create(
		windowsAPI.windowClass.hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);

	//�L�[�{�[�h�f�o�C�X�̐���
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeybord, NULL);

	//���̓f�[�^�̌`���Z�b�g
	result = devkeybord->SetDataFormat(&c_dfDIKeyboard);

	//�r�����䃌�x���̃Z�b�g
	result = devkeybord->SetCooperativeLevel(
		windowsAPI.hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

	//�}�E�X�f�o�C�X�̐���
	result = dinput->CreateDevice(GUID_SysMouse, &devmouse, NULL);

	//���̓f�[�^�̌`���Z�b�g
	result = devmouse->SetDataFormat(&c_dfDIMouse);

	//�r�����䃌�x���̃Z�b�g
	result = devmouse->SetCooperativeLevel(
		windowsAPI.hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

}

void DirectXBase::BeforeDrawing() {
	//���b�Z�[�W�m�F
	if (PeekMessage(&windowsAPI.msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&windowsAPI.msg);	//�L�[���̓��b�Z�[�W�̏���
		DispatchMessage(&windowsAPI.msg);	//�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
	}
	//?�{�^���ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
	if (windowsAPI.msg.message == WM_QUIT) {
		exit(true);
	}

	//�S�L�[�̓��͏�Ԃ��擾����
	Input::Instance()->Update(devkeybord, devmouse);

	//�����_�[�^�[�Q�b�g�̃��\�[�X�o���A�ύX
	UINT bbIndex = swapchain->GetCurrentBackBufferIndex();
	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(backBuffers[bbIndex].Get(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	//�����_�[�^�[�Q�b�g�̐ݒ�
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		rtvHeaps->GetCPUDescriptorHandleForHeapStart(), bbIndex, dev->GetDescriptorHandleIncrementSize(heapDesc.Type));

	//�[�x�o�b�t�@�p�̃f�B�X�N���v�^�q�[�v�̐擪�A�h���X���擾
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH = dsvHeap->GetCPUDescriptorHandleForHeapStart();
	cmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);

	//��ʃN���A
	//�������F
	float clearColor[] = { 0.35f,0.3f,0.2f,0.0f };
	for (int i = 0; i < 4; ++i) {
		clearColor[i] = clearColor[i] / 255.0f;
	}
	cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);

	//�[�x�o�b�t�@�̃N���A�R�}���h
	cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	//�r���[�|�[�g�ݒ�
	cmdList->RSSetViewports(1, &CD3DX12_VIEWPORT(0.0f, 0.0f, window_width, window_height));

	//�V�U�����O��`�ݒ�
	cmdList->RSSetScissorRects(1, &CD3DX12_RECT(0, 0, window_width, window_height));

}

void DirectXBase::AfterDrawing() {

	//�����_�[�^�[�Q�b�g�̃��\�[�X�o���A�ύX
	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(backBuffers[swapchain->GetCurrentBackBufferIndex()].Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	//�O���t�B�b�N�R�}���h���X�g�̃N���[�Y
	cmdList->Close();

	//�O���t�B�b�N�R�}���h���X�g�̎��s
	ID3D12CommandList* cmdLists[] = { cmdList.Get() }; //�R�}���h���X�g�̔z��
	cmdQueue->ExecuteCommandLists(1, cmdLists);

	//��ʃo�b�t�@���t���b�v
	swapchain->Present(1, 0);

	//�O���t�B�b�N�R�}���h���X�g�̊����҂�
	cmdQueue->Signal(fence.Get(), ++fenceVal);
	if (fence->GetCompletedValue() != fenceVal) {
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		fence->SetEventOnCompletion(fenceVal, event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}

	//�R�}���h�A���P�[�^�̃��Z�b�g
	cmdAllocator->Reset();						//�L���[���N���A

	//�R�}���h���X�g�̃��Z�b�g
	cmdList->Reset(cmdAllocator.Get(), nullptr);		//�ĂуR�}���h���X�g�𒙂߂鏀��
}

void DirectXBase::SetRenderTarget()
{
	//�����_�[�^�[�Q�b�g�̃��\�[�X�o���A�ύX
	UINT bbIndex = swapchain->GetCurrentBackBufferIndex();
	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(backBuffers[bbIndex].Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(backBuffers[bbIndex].Get(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
	//�����_�[�^�[�Q�b�g�̐ݒ�
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		rtvHeaps->GetCPUDescriptorHandleForHeapStart(), bbIndex, dev->GetDescriptorHandleIncrementSize(heapDesc.Type));
	cmdList->OMSetRenderTargets(1, &CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeaps->GetCPUDescriptorHandleForHeapStart(),
		swapchain->GetCurrentBackBufferIndex(), dev->GetDescriptorHandleIncrementSize(heapDesc.Type)), false, &dsvHeap->GetCPUDescriptorHandleForHeapStart());
	//�����_�[�^�[�Q�b�g�̃N���A
	float clearColor[] = { 0.5f,0.5f,0.5f,0.0f };
	cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	//�[�x�o�b�t�@�̃N���A�R�}���h
	cmdList->ClearDepthStencilView(dsvHeap->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void DirectXBase::ResourceBarrierAfter()
{
	//�����_�[�^�[�Q�b�g�̃��\�[�X�o���A�ύX
	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(backBuffers[swapchain->GetCurrentBackBufferIndex()].Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
}

ComPtr<ID3D12DescriptorHeap> DirectXBase::CreateDescriptorHeaoForImgui()
{
	ComPtr<ID3D12DescriptorHeap> ret;

	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	desc.NodeMask = 0;
	desc.NumDescriptors = 1;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	dev->CreateDescriptorHeap(&desc, IID_PPV_ARGS(ret.ReleaseAndGetAddressOf()));

	return ret;
}