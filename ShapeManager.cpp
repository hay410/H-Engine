//#include"ShapeManager.h"
//
//ShapeManager::ShapeManager()
//{
//	objectData = {};
//}
//
//void ShapeManager::LoadObject(int dataID, Object3D& objectBuff, const char* fileName)
//{
//	//�}�`�������ς݂��ǂ������m�F����
//	bool isLoad = false;
//	int dataNum = 0;
//	for (int i = 0; i < objectData.size(); ++i)
//	{
//		if (objectData.at(i).dataID == dataID)
//		{
//			isLoad = true;
//			dataNum = i;
//		}
//	}
//
//	if (isLoad == false)
//	{
//		switch (dataID)
//		{
//		case SHAPE_DATA_OBJECT:
//			CreateObject(fileName, objectBuff);
//			break;
//		case SHAPE_DATA_CONE:
//			CreateCone(objectBuff);
//			break;
//		case SHAPE_DATA_CYLINDER:
//			CreateCylinder(objectBuff);
//			break;
//		case SHAPE_DATA_SPHERE:
//			CreateSphere(objectBuff);
//			break;
//		default:
//			break;
//		}
//	}
//	else
//	{
//		for (int i = 0; i < objectData.at(dataNum).indices.size(); ++i)
//		{
//			objectBuff.indices.push_back(objectData.at(dataNum).indices.at(i));
//		}
//		for (int i = 0; i < objectData.at(dataNum).vertices.size(); ++i)
//		{
//			objectBuff.vertices.push_back(objectData.at(dataNum).vertices.at(i));
//		}
//	}
//}
//
//void ShapeManager::CreateObject(const char* fileName,Object3D& objectBuff)
//{
//	objectData.push_back({});
//	objectData.at(objectData.size() - 1).dataID = SHAPE_DATA_CONE;
//	//�t�@�C���X�g���[��
//	ifstream file;
//	//obj�t�@�C�����J��
//	file.open(fileName);
//	//�t�@�C���I�[�v�����s���`�F�b�N
//	if (file.fail())assert(0);
//
//	vector<XMFLOAT3> positions;
//	vector<XMFLOAT3> normals;
//	vector<XMFLOAT2> uv;
//
//	//1�s���ǂݍ���
//	string line;
//	while (getline(file,line))
//	{
//		//��s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
//		istringstream line_stream(line);
//		//���p�X�y�[�X��؂�ōs�̐擪��������擾
//		string key;
//		getline(line_stream, key, ' '); 
//
//		/*--------���_���̓ǂݍ���--------*/
//
//		//�擪������v�Ȃ璸�_
//		if (key == "v")
//		{
//			XMFLOAT3 position{};
//			line_stream >> position.x;
//			line_stream >> position.y;
//			line_stream >> position.z;
//			positions.push_back(position);
//			//���W�f�[�^�ɒǉ�
//			//vertices vertices;
//			//vertices.pos = position;
//			//sprite.vertices.push_back(vertices);
//		}
//
//		//�擪������vt�Ȃ�e�N�X�`��
//		if (key == "vt")
//		{
//			//U,V�����ǂݍ���
//			XMFLOAT2 texcoord{};
//			line_stream >> texcoord.x;
//			line_stream >> texcoord.y;
//			//V�������]
//			texcoord.y = 1.0f - texcoord.y;
//			//�e�N�X�`�����W�f�[�^�ɒǉ�
//			uv.push_back(texcoord);
//		}
//
//		//�擪������vn�Ȃ�@���x�N�g��
//		if (key == "vn")
//		{
//			//xyz�����ǂݍ���
//			XMFLOAT3 normal{};
//			line_stream >> normal.x;
//			line_stream >> normal.y;
//			line_stream >> normal.z;
//			//�@���x�N�g���Ƀf�[�^�ǉ�
//			normals.push_back(normal);
//		}
//
//		//�擪������f�Ȃ�C���f�b�N�X
//		if (key == "f")
//		{
//			//���p�X�y�[�X��؂�ōs�̑�����ǂݎ��
//			string indices_string;
//
//			while (getline(line_stream, indices_string, ' '))
//			{
//				//���_�C���f�b�N�X����̕�������X�g���[���ɕϊ����ĉ�͂��₷������
//				istringstream indices_stream(indices_string);
//				unsigned short indicesPos, indicesUv, IndicesNormal;
//				indices_stream >> indicesPos;
//				indices_stream.seekg(1, ios_base::cur);
//				indices_stream >> indicesUv;
//				indices_stream.seekg(1, ios_base::cur);
//				indices_stream >> IndicesNormal;
//				Vertex vertices{};
//				vertices.pos = positions[indicesPos - 1];
//				vertices.normal = normals[IndicesNormal - 1];
//				vertices.uv = uv[indicesUv - 1];
//				objectBuff.vertices.push_back(vertices);
//				objectData.at(objectData.size() - 1).vertices.push_back(vertices);
//				//�C���f�b�N�X�f�[�^�̒ǉ�
//				objectBuff.indices.push_back((unsigned short)objectBuff.indices.size());
//				objectData.at(objectData.size() - 1).indices.push_back((unsigned short)objectBuff.indices.size());
//			}
//		}
//	}
//	//�t�@�C�������
//	file.close();
//}
//
//void ShapeManager::CreateCone(Object3D& objectBuff)
//{
//	//objectData�𐶐�
//	objectData.push_back({});
//	objectData.at(objectData.size() - 1).dataID = SHAPE_DATA_CONE;
//
//	int verticesCount = 30;			//���_��
//	//��ʂ̒��S�ȊO�̍��W���v�Z
//	for (int i = 0; i < verticesCount - 2; ++i)
//	{
//		Vertex pos;
//		pos.pos = XMFLOAT3(1 * sinf(XM_2PI / (verticesCount - 2) * i),
//			1 * (cosf(XM_2PI / (verticesCount - 2) * i)),
//			0);
//		pos.uv = XMFLOAT2(0, 0);
//		objectData.at(objectData.size() - 1).vertices.push_back(pos);
//		objectBuff.vertices.push_back(pos);
//	}
//
//	//��ʂ̒��S
//	Vertex circleCenterPos{};
//	circleCenterPos.pos = XMFLOAT3(0, 0, 0);
//	circleCenterPos.uv = XMFLOAT2(0, 0);
//
//	objectData.at(objectData.size() - 1).vertices.push_back(circleCenterPos);
//	objectBuff.vertices.push_back(circleCenterPos);
//
//	//���_
//	Vertex topHeightPos{};
//	topHeightPos.pos = XMFLOAT3(0, 0, -5);
//	topHeightPos.uv = XMFLOAT2(0, 0);
//
//	objectData.at(objectData.size() - 1).vertices.push_back(topHeightPos);
//
//	objectBuff.vertices.push_back(topHeightPos);
//
//	//��ʂ̃C���f�b�N�X�̐ݒ�
//	int i = 0;
//	for (; i < verticesCount - 3; ++i) {
//		objectData.at(objectData.size() - 1).indices.push_back(i);
//		objectData.at(objectData.size() - 1).indices.push_back(verticesCount - 2);
//		objectData.at(objectData.size() - 1).indices.push_back(i + 1);
//
//		objectBuff.indices.push_back(i);
//		objectBuff.indices.push_back(verticesCount - 2);
//		objectBuff.indices.push_back(i + 1);
//	}
//
//	objectData.at(objectData.size() - 1).indices.push_back(i);
//	objectData.at(objectData.size() - 1).indices.push_back(verticesCount - 2);
//	objectData.at(objectData.size() - 1).indices.push_back(0);
//
//	objectBuff.indices.push_back(i);
//	objectBuff.indices.push_back(verticesCount - 2);
//	objectBuff.indices.push_back(0);
//
//	//���ʂ̃C���f�b�N�X�̐ݒ�
//	i = 0;
//	for (; i < verticesCount - 3; ++i) {
//		objectData.at(objectData.size() - 1).indices.push_back(i);
//		objectData.at(objectData.size() - 1).indices.push_back(i + 1);
//		objectData.at(objectData.size() - 1).indices.push_back(verticesCount - 1);
//
//		objectBuff.indices.push_back(i);
//		objectBuff.indices.push_back(i + 1);
//		objectBuff.indices.push_back(verticesCount - 1);
//	}
//
//	objectData.at(objectData.size() - 1).indices.push_back(i);
//	objectData.at(objectData.size() - 1).indices.push_back(0);
//	objectData.at(objectData.size() - 1).indices.push_back(verticesCount - 1);
//
//	objectBuff.indices.push_back(i);
//	objectBuff.indices.push_back(0);
//	objectBuff.indices.push_back(verticesCount - 1);
//
//	//�@���x�N�g���̌v�Z
//	for (int i = 0; i < objectBuff.indices.size() / 3; ++i) {
//		//�O�p�`�ЂƂЂƂv�Z���Ă���
//		//�O�p�`�̃C���f�b�N�X�����o���āA�ꎞ�I�ȕϐ��ɓ����
//		unsigned short index0 = objectBuff.indices.at(i * 3 + 0);
//		unsigned short index1 = objectBuff.indices.at(i * 3 + 1);
//		unsigned short index2 = objectBuff.indices.at(i * 3 + 2);
//		//�O�p�`���\�����钸�_���W���x�N�g���ɑ��
//		XMVECTOR p0 = XMLoadFloat3(&objectBuff.vertices.at(index0).pos);
//		XMVECTOR p1 = XMLoadFloat3(&objectBuff.vertices.at(index1).pos);
//		XMVECTOR p2 = XMLoadFloat3(&objectBuff.vertices.at(index2).pos);
//		//p0->p1�x�N�g��,p0->p2�x�N�g�����v�Z
//		XMVECTOR v1 = XMVectorSubtract(p1, p0);
//		XMVECTOR v2 = XMVectorSubtract(p2, p0);
//		//�O�ʂ͗������琂���ȃx�N�g��
//		XMVECTOR normal = XMVector3Cross(v1, v2);
//		//���K��
//		normal = XMVector3Normalize(normal);
//		//���߂��@���𒸓_�f�[�^�ɑ��
//		//objectData�֕ۑ�
//		XMStoreFloat3(&objectData.at(objectData.size() - 1).vertices.at(index0).normal, normal);
//		XMStoreFloat3(&objectData.at(objectData.size() - 1).vertices.at(index1).normal, normal);
//		XMStoreFloat3(&objectData.at(objectData.size() - 1).vertices.at(index2).normal, normal);
//		//sprite�ւ̃R�s�[���s��
//		XMStoreFloat3(&objectBuff.vertices.at(index0).normal, normal);
//		XMStoreFloat3(&objectBuff.vertices.at(index1).normal, normal);
//		XMStoreFloat3(&objectBuff.vertices.at(index2).normal, normal);
//	}
//}
//
//void ShapeManager::CreateCylinder(Object3D& objectBuff)
//{
//	//objectData�𐶐�
//	objectData.push_back({});
//	objectData.at(objectData.size() - 1).dataID = SHAPE_DATA_CYLINDER;
//	//���_�o�b�t�@�̐���
//	int verticesCount = 30;			//���_��
//	//��ʂ̍��W���v�Z
//	for (int i = 0; i < verticesCount / 2 - 1; ++i) {
//		Vertex pos;
//		pos.pos = XMFLOAT3(1 * sinf(XM_2PI / (verticesCount / 2 - 1) * i),
//			1 * (cosf(XM_2PI / (verticesCount / 2 - 1) * i)),
//			0);
//		pos.uv = XMFLOAT2(0, 0);
//		//objectData�֕ۑ�
//		objectData.at(objectData.size() - 1).vertices.push_back(pos);
//		//sprite�ւ̃f�[�^�R�s�[���s��
//		objectBuff.vertices.push_back(pos);
//	}
//	Vertex circleCenterPos{};
//	circleCenterPos.pos = XMFLOAT3(0, 0, 0);
//	circleCenterPos.uv = XMFLOAT2(0, 0);
//	//objectData�֕ۑ�
//	objectData.at(objectData.size() - 1).vertices.push_back(circleCenterPos);
//	//sprite�ւ̃f�[�^�R�s�[���s��
//	objectBuff.vertices.push_back(circleCenterPos);
//	//�V�ʂ̍��W���v�Z
//	for (int i = 0; i < verticesCount / 2 - 1; ++i) {
//		Vertex pos;
//		pos.pos = XMFLOAT3(1 * sinf(XM_2PI / (verticesCount / 2 - 1) * i),
//			1 * (cosf(XM_2PI / (verticesCount / 2 - 1) * i)),
//			-1);
//		pos.uv = XMFLOAT2(0, 0);
//		//objectData�֕ۑ�
//		objectData.at(objectData.size() - 1).vertices.push_back(pos);
//		//sprite�ւ̃f�[�^�R�s�[���s��
//		objectBuff.vertices.push_back(pos);
//	}
//	Vertex topHeightPos{};
//	topHeightPos.pos = XMFLOAT3(0, 0, -1);
//	topHeightPos.uv = XMFLOAT2(0, 0);
//	//objectData�֕ۑ�
//	objectData.at(objectData.size() - 1).vertices.push_back(topHeightPos);
//	//sprite�ւ̃f�[�^�R�s�[���s��
//	objectBuff.vertices.push_back(topHeightPos);
//
//	//��ʂ̃C���f�b�N�X�̐ݒ�
//	int i = 0;
//	for (; i < verticesCount / 2 - 2; ++i) {
//		//objectData�֕ۑ�
//		objectData.at(objectData.size() - 1).indices.push_back(i);
//		objectData.at(objectData.size() - 1).indices.push_back(verticesCount / 2 - 1);
//		objectData.at(objectData.size() - 1).indices.push_back(i + 1);
//		//sprite�ւ̃f�[�^�R�s�[���s��
//		objectBuff.indices.push_back(i);
//		objectBuff.indices.push_back(verticesCount / 2 - 1);
//		objectBuff.indices.push_back(i + 1);
//	}
//	//objectData�֕ۑ�
//	objectData.at(objectData.size() - 1).indices.push_back(i);
//	objectData.at(objectData.size() - 1).indices.push_back(verticesCount / 2 - 1);
//	objectData.at(objectData.size() - 1).indices.push_back(0);
//	//sprite�ւ̃f�[�^�R�s�[���s��
//	objectBuff.indices.push_back(i);
//	objectBuff.indices.push_back(verticesCount / 2 - 1);
//	objectBuff.indices.push_back(0);
//	//�V�ʂ̃C���f�b�N�X�̐ݒ�
//	i = 0;
//	for (; i < verticesCount / 2 - 2; ++i) {
//		//objectData�֕ۑ�
//		objectData.at(objectData.size() - 1).indices.push_back(i + verticesCount / 2);
//		objectData.at(objectData.size() - 1).indices.push_back(i + 1 + verticesCount / 2);
//		objectData.at(objectData.size() - 1).indices.push_back(verticesCount - 1);
//		//sprite�ւ̃f�[�^�R�s�[���s��
//		objectBuff.indices.push_back(i + verticesCount / 2);
//		objectBuff.indices.push_back(i + 1 + verticesCount / 2);
//		objectBuff.indices.push_back(verticesCount - 1);
//	}
//	//objectData�֕ۑ�
//	objectData.at(objectData.size() - 1).indices.push_back(i + verticesCount / 2);
//	objectData.at(objectData.size() - 1).indices.push_back(verticesCount / 2);
//	objectData.at(objectData.size() - 1).indices.push_back(verticesCount - 1);
//	//sprite�ւ̃f�[�^�R�s�[���s��
//	objectBuff.indices.push_back(i + verticesCount / 2);
//	objectBuff.indices.push_back(verticesCount / 2);
//	objectBuff.indices.push_back(verticesCount - 1);
//	//���ʂ̃C���f�b�N�X�̐ݒ�
//	i = 0;
//	for (; i < verticesCount / 2 - 2; ++i) {
//		//objectData�֕ۑ�
//		objectData.at(objectData.size() - 1).indices.push_back(i);
//		objectData.at(objectData.size() - 1).indices.push_back(i + 1);
//		objectData.at(objectData.size() - 1).indices.push_back(i + verticesCount / 2);
//		objectData.at(objectData.size() - 1).indices.push_back(i + 1);
//		objectData.at(objectData.size() - 1).indices.push_back(i + 1 + verticesCount / 2);
//		objectData.at(objectData.size() - 1).indices.push_back(i + verticesCount / 2);
//		//sprite�ւ̃f�[�^�R�s�[���s��
//		objectBuff.indices.push_back(i);
//		objectBuff.indices.push_back(i + 1);
//		objectBuff.indices.push_back(i + verticesCount / 2);
//		objectBuff.indices.push_back(i + 1);
//		objectBuff.indices.push_back(i + 1 + verticesCount / 2);
//		objectBuff.indices.push_back(i + verticesCount / 2);
//	}
//	//objectData�֕ۑ�
//	objectData.at(objectData.size() - 1).indices.push_back(i);
//	objectData.at(objectData.size() - 1).indices.push_back(0);
//	objectData.at(objectData.size() - 1).indices.push_back(i + verticesCount / 2);
//	objectData.at(objectData.size() - 1).indices.push_back(0);
//	objectData.at(objectData.size() - 1).indices.push_back(verticesCount / 2);
//	objectData.at(objectData.size() - 1).indices.push_back(i + verticesCount / 2);
//	//sprite�ւ̃f�[�^�R�s�[���s��
//	objectBuff.indices.push_back(i);
//	objectBuff.indices.push_back(0);
//	objectBuff.indices.push_back(i + verticesCount / 2);
//	objectBuff.indices.push_back(0);
//	objectBuff.indices.push_back(verticesCount / 2);
//	objectBuff.indices.push_back(i + verticesCount / 2);
//
//	//�@���x�N�g���̌v�Z
//	for (int i = 0; i < objectBuff.indices.size() / 3; ++i) {
//		//�O�p�`�ЂƂЂƂv�Z���Ă���
//		//�O�p�`�̃C���f�b�N�X�����o���āA�ꎞ�I�ȕϐ��ɓ����
//		unsigned short indices0 = objectBuff.indices.at(i * 3 + 0);
//		unsigned short indices1 = objectBuff.indices.at(i * 3 + 1);
//		unsigned short indices2 = objectBuff.indices.at(i * 3 + 2);
//		//�O�p�`���\�����钸�_���W���x�N�g���ɑ��
//		XMVECTOR p0 = XMLoadFloat3(&objectBuff.vertices.at(indices0).pos);
//		XMVECTOR p1 = XMLoadFloat3(&objectBuff.vertices.at(indices1).pos);
//		XMVECTOR p2 = XMLoadFloat3(&objectBuff.vertices.at(indices2).pos);
//		//p0->p1�x�N�g��,p0->p2�x�N�g�����v�Z
//		XMVECTOR v1 = XMVectorSubtract(p1, p0);
//		XMVECTOR v2 = XMVectorSubtract(p2, p0);
//		//�O�ʂ͗������琂���ȃx�N�g��
//		XMVECTOR normal = XMVector3Cross(v1, v2);
//		//���K��
//		normal = XMVector3Normalize(normal);
//		//���߂��@���𒸓_�f�[�^�ɑ��
//		//objectData�֕ۑ�
//		XMStoreFloat3(&objectData.at(objectData.size() - 1).vertices.at(indices0).normal, normal);
//		XMStoreFloat3(&objectData.at(objectData.size() - 1).vertices.at(indices1).normal, normal);
//		XMStoreFloat3(&objectData.at(objectData.size() - 1).vertices.at(indices2).normal, normal);
//		//sprite�ւ̃f�[�^�R�s�[���s��
//		XMStoreFloat3(&objectBuff.vertices.at(indices0).normal, normal);
//		XMStoreFloat3(&objectBuff.vertices.at(indices1).normal, normal);
//		XMStoreFloat3(&objectBuff.vertices.at(indices2).normal, normal);
//	}
//}
//
//void ShapeManager::CreateSphere(Object3D& objectBuff)
//{
//	//objectData�𐶐�
//	objectData.push_back({});
//	objectData.at(objectData.size() - 1).dataID = SHAPE_DATA_SPHERE;
//	//���_�o�b�t�@�̐���
//	int vertexCount = 30;			//���_��
//	Vertex pos;
//	//��ʂ̍��W
//	pos.pos = XMFLOAT3(0, 0, -1);
//	pos.uv = XMFLOAT2(0, 0);
//	//objectData�ɕۑ�
//	objectData.at(objectData.size() - 1).vertices.push_back(pos);
//	//sprite�ɂ��f�[�^���R�s�[
//	objectBuff.vertices.push_back(pos);
//	//���ʂ̍��W�̌v�Z
//	for (int i = 1; i < vertexCount; ++i) {
//		for (int j = 0; j < vertexCount; ++j) {
//			float circleRadius = (1 * sinf(XM_PI / vertexCount * i));
//			pos.pos = XMFLOAT3(circleRadius * sinf(XM_2PI / vertexCount * j),
//				circleRadius * (cosf(XM_2PI / vertexCount * j)),
//				-1 * (cosf((XM_PI / vertexCount * i)))
//			);
//			pos.uv = XMFLOAT2(0, 0);
//			//objectData�ɕۑ�
//			objectData.at(objectData.size() - 1).vertices.push_back(pos);
//			//sprite�ɂ��f�[�^���R�s�[
//			objectBuff.vertices.push_back(pos);
//		}
//	}
//	//�V�ʂ̍��W
//	pos.pos = XMFLOAT3(0, 0, 1);
//	pos.uv = XMFLOAT2(0, 0);
//	//objectData�ɕۑ�
//	objectData.at(objectData.size() - 1).vertices.push_back(pos);
//	//sprite�ɂ��f�[�^���R�s�[
//	objectBuff.vertices.push_back(pos);
//
//	//��ʂ̃C���f�b�N�X�̐ݒ�
//	int buff = 1;
//	for (int i = 0; i < vertexCount - 1; ++i) {
//		//objectData�ɕۑ�
//		objectData.at(objectData.size() - 1).indices.push_back(buff);
//		objectData.at(objectData.size() - 1).indices.push_back(buff + 1);
//		objectData.at(objectData.size() - 1).indices.push_back(0);
//		//sprite�ɂ��f�[�^���R�s�[
//		objectBuff.indices.push_back(buff);
//		objectBuff.indices.push_back(buff + 1);
//		objectBuff.indices.push_back(0);
//		buff++;
//	}
//	//objectData�ɕۑ�
//	objectData.at(objectData.size() - 1).indices.push_back(buff);
//	objectData.at(objectData.size() - 1).indices.push_back(1);
//	objectData.at(objectData.size() - 1).indices.push_back(0);
//	//sprite�ɂ��f�[�^���R�s�[
//	objectBuff.indices.push_back(buff);
//	objectBuff.indices.push_back(1);
//	objectBuff.indices.push_back(0);
//	buff++;
//	//���ʂ̃C���f�b�N�X�̐ݒ�
//	for (int i = 0; i < vertexCount - 2; ++i) {
//		for (int j = 0; j < vertexCount - 1; ++j) {
//			//objectData�ɕۑ�
//			objectData.at(objectData.size() - 1).indices.push_back(buff);
//			objectData.at(objectData.size() - 1).indices.push_back(buff + 1);
//			objectData.at(objectData.size() - 1).indices.push_back(buff - (vertexCount - 1));
//			objectData.at(objectData.size() - 1).indices.push_back(buff);
//			objectData.at(objectData.size() - 1).indices.push_back(buff - (vertexCount - 1));
//			objectData.at(objectData.size() - 1).indices.push_back(buff - vertexCount);
//			//sprite�ɂ��f�[�^���R�s�[
//			objectBuff.indices.push_back(buff);
//			objectBuff.indices.push_back(buff + 1);
//			objectBuff.indices.push_back(buff - (vertexCount - 1));
//			objectBuff.indices.push_back(buff);
//			objectBuff.indices.push_back(buff - (vertexCount - 1));
//			objectBuff.indices.push_back(buff - vertexCount);
//			buff++;
//		}
//		//objectData�ɕۑ�
//		objectData.at(objectData.size() - 1).indices.push_back(buff);
//		objectData.at(objectData.size() - 1).indices.push_back(buff - (vertexCount - 1));
//		objectData.at(objectData.size() - 1).indices.push_back(buff - (vertexCount - 1) - vertexCount);
//		objectData.at(objectData.size() - 1).indices.push_back(buff);
//		objectData.at(objectData.size() - 1).indices.push_back(buff - (vertexCount - 1) - vertexCount);
//		objectData.at(objectData.size() - 1).indices.push_back(buff - vertexCount);
//		//sprite�ɂ��f�[�^���R�s�[
//		objectBuff.indices.push_back(buff);
//		objectBuff.indices.push_back(buff - (vertexCount - 1));
//		objectBuff.indices.push_back(buff - (vertexCount - 1) - vertexCount);
//		objectBuff.indices.push_back(buff);
//		objectBuff.indices.push_back(buff - (vertexCount - 1) - vertexCount);
//		objectBuff.indices.push_back(buff - vertexCount);
//		buff++;
//	}
//	//�V�ʂ̃C���f�b�N�X�̐ݒ�
//	for (int i = vertexCount - 1; i > 0; --i) {
//		//objectData�ɕۑ�
//		objectData.at(objectData.size() - 1).indices.push_back(objectBuff.vertices.size() - 1 - i);
//		objectData.at(objectData.size() - 1).indices.push_back(objectBuff.vertices.size() - 1 - i - 1);
//		objectData.at(objectData.size() - 1).indices.push_back(objectBuff.vertices.size() - 1);
//		//sprite�ɂ��f�[�^���R�s�[
//		objectBuff.indices.push_back(objectBuff.vertices.size() - 1 - i);
//		objectBuff.indices.push_back(objectBuff.vertices.size() - 1 - i - 1);
//		objectBuff.indices.push_back(objectBuff.vertices.size() - 1);
//	}
//	//objectData�ɕۑ�
//	objectData.at(objectData.size() - 1).indices.push_back(objectBuff.vertices.size() - 1 - 1);
//	objectData.at(objectData.size() - 1).indices.push_back(objectBuff.vertices.size() - 1);
//	objectData.at(objectData.size() - 1).indices.push_back(objectBuff.vertices.size() - 1 - vertexCount);
//	//sprite�ɂ��f�[�^���R�s�[
//	objectBuff.indices.push_back(objectBuff.vertices.size() - 1 - 1);
//	objectBuff.indices.push_back(objectBuff.vertices.size() - 1);
//	objectBuff.indices.push_back(objectBuff.vertices.size() - 1 - vertexCount);
//
//	//�@���x�N�g���̌v�Z
//	for (int i = 0; i < objectBuff.indices.size() / 3; ++i) {
//		//�O�p�`�ЂƂЂƂv�Z���Ă���
//		//�O�p�`�̃C���f�b�N�X�����o���āA�ꎞ�I�ȕϐ��ɓ����
//		unsigned short index0 = objectBuff.indices.at(i * 3 + 0);
//		unsigned short index1 = objectBuff.indices.at(i * 3 + 1);
//		unsigned short index2 = objectBuff.indices.at(i * 3 + 2);
//		//�O�p�`���\�����钸�_���W���x�N�g���ɑ��
//		XMVECTOR p0 = XMLoadFloat3(&objectBuff.vertices.at(index0).pos);
//		XMVECTOR p1 = XMLoadFloat3(&objectBuff.vertices.at(index1).pos);
//		XMVECTOR p2 = XMLoadFloat3(&objectBuff.vertices.at(index2).pos);
//		//p0->p1�x�N�g��,p0->p2�x�N�g�����v�Z
//		XMVECTOR v1 = XMVectorSubtract(p1, p0);
//		XMVECTOR v2 = XMVectorSubtract(p2, p0);
//		//�O�ʂ͗������琂���ȃx�N�g��
//		XMVECTOR normal = XMVector3Cross(v1, v2);
//		//���K��
//		normal = XMVector3Normalize(normal);
//		//���߂��@���𒸓_�f�[�^�ɑ��
//		//objectData�ɕۑ�
//		XMStoreFloat3(&objectData.at(objectData.size() - 1).vertices.at(index0).normal, normal);
//		XMStoreFloat3(&objectData.at(objectData.size() - 1).vertices.at(index1).normal, normal);
//		XMStoreFloat3(&objectData.at(objectData.size() - 1).vertices.at(index2).normal, normal);
//		//sprite�ɂ��f�[�^���R�s�[
//		XMStoreFloat3(&objectBuff.vertices.at(index0).normal, normal);
//		XMStoreFloat3(&objectBuff.vertices.at(index1).normal, normal);
//		XMStoreFloat3(&objectBuff.vertices.at(index2).normal, normal);
//	}
//}
