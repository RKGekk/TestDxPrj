#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <xnamath.h>
#include "xnacollision.h"
#include <iostream>
#include <d3dApp.h>
#include <d3dx11effect.h>
#include <MathHelper.h>
#include <regex>
#include <string>
#include <GeometryGenerator.h>
#include <Waves.h>
#include <LightHelper.h>
#include "Effects.h"
#include "Vertex.h"
#include "RenderStates.h"
#include "BlurFilter.h"
#include "Camera.h"
#include "Sky.h"
#include "TextUtil.h"
#include "ObjLoader.h"

using namespace std;

ostream& operator<<(ostream& os, FXMVECTOR v) {

	XMFLOAT4 dest;
	XMStoreFloat4(&dest, v);

	os << "(" << dest.x << ", " << dest.y << ", " << dest.z << ", " << dest.w << ")";

	return os;
}

ostream& operator<<(ostream& os, CXMMATRIX m) {

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			os << m(i, j) << "\t";
		}
		os << endl;
	}

	return os;
}

enum RenderOptions {
	Lighting = 0,
	Textures = 1,
	TexturesAndFog = 2
};

class BoxApp : public D3DApp {

public:
	BoxApp(HINSTANCE hInstance);
	~BoxApp();

	bool Init();

	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();

	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);

private:
	void CalculateTangentsAndNormals(std::vector<Vertex::PosNormalTexTan>& verts, std::vector<UINT>& idx);

	void UpdateWaves();
	void DrawWrapper();
	void DrawWrapper2();
	void DrawWrapper2_2();
	void DrawWrapper2_3();
	void DrawWrapper2_4();
	void DrawWrapper3();
	void DrawWrapper4();
	void DrawScreenQuad();

	void BuildCrateGeometryBuffers();
	void BuildSheepGeometryBuffers();
	void BuildTextGeometryBuffers();
	void BuildCapsuleGeometryBuffers();
	void BuildRoomGeometryBuffers();
	void BuildInstancedBuffer();
	void BuildScreenQuadGeometryBuffers();
	void BuildOffscreenViews();

	ID3D11Buffer* mLandVB;
	ID3D11Buffer* mLandIB;
	ID3D11Buffer* mInstancedBuffer;
	ID3D11Buffer* mInstancedBuffer2;
	std::vector<Instance::InstancedData> mInstancedData;
	std::vector<Instance::InstancedData> mInstancedData2;

	ID3D11Buffer* mCapsuleVB;
	ID3D11Buffer* mCapsuleIB;
	std::vector<Instance::InstancedData> mCapsuleInstancedData;
	ID3D11ShaderResourceView* mCapsuleDiffuseMapSRV;
	ID3D11ShaderResourceView* mCapsuleNormalMapSRV;
	ID3D11ShaderResourceView* mHumanShieldDiffuseMapSRV;
	ID3D11ShaderResourceView* mHumanShieldNormalMapSRV;
	ID3D11ShaderResourceView* mHosepipeDiffuseMapSRV;
	ID3D11ShaderResourceView* mHosepipeNormalMapSRV;
	ID3D11ShaderResourceView* mScuffedPlasticDiffuseMapSRV;
	ID3D11ShaderResourceView* mScuffedPlasticNormalMapSRV;
	ID3D11ShaderResourceView* mMetalGridDiffuseMapSRV;
	ID3D11ShaderResourceView* mMetalGridNormalMapSRV;
	ID3D11ShaderResourceView* mScifiFloorDiffuseMapSRV;
	ID3D11ShaderResourceView* mScifiFloorNormalMapSRV;
	ID3D11ShaderResourceView* mStorageContainerDiffuseMapSRV;
	ID3D11ShaderResourceView* mStorageContainerNormalMapSRV;
	ID3D11ShaderResourceView* mChippedPaintMetalDiffuseMapSRV;
	ID3D11ShaderResourceView* mChippedPaintMetalNormalMapSRV;
	ID3D11ShaderResourceView* mPlasticPaddedDiffuseMapSRV;
	ID3D11ShaderResourceView* mPlasticPaddedNormalMapSRV;
	ID3D11ShaderResourceView* mRustedironStreaksDiffuseMapSRV;
	ID3D11ShaderResourceView* mRustedironStreaksNormalMapSRV;
	ID3D11ShaderResourceView* mCircleMetalGridDiffuseMapSRV;
	ID3D11ShaderResourceView* mCircleMetalGridNormalMapSRV;
	ID3D11ShaderResourceView* mIronRustedDiffuseMapSRV0;
	ID3D11ShaderResourceView* mIronRustedDiffuseMapSRV1;
	ID3D11ShaderResourceView* mIronRustedDiffuseMapSRV2;
	ID3D11ShaderResourceView* mIronRustedDiffuseMapSRV3;
	ID3D11ShaderResourceView* mIronRustedNormalMapSRV;
	

	int mCapsuleIndexCount;

	ID3D11Buffer* mRoomVB;
	ID3D11Buffer* mRoomIB;
	int mRoomIndexCount;

	int mShieldingCapsuleIndexCount;
	int mShieldingCapsuleIndexLocation;
	int mCircleSupportIndexCount;
	int mCircleSupportIndexLocation;
	int mNumPadIndexCount;
	int mNumPadIndexLocation;
	int mVerticalSupportIndexCount;
	int mVerticalSupportIndexLocation;

	int mHumanShieldIndexCount;
	int mHumanShieldIndexLocation;

	int mHosepipe0IndexCount;
	int mHosepipe0IndexLocation;
	int mHosepipe1IndexCount;
	int mHosepipe1IndexLocation;
	int mHosepipe2IndexCount;
	int mHosepipe2IndexLocation;
	int mHosepipe3IndexCount;
	int mHosepipe3IndexLocation;
	int mHosepipe4IndexCount;
	int mHosepipe4IndexLocation;
	int mHosepipe5IndexCount;
	int mHosepipe5IndexLocation;
	int mHosepipe6IndexCount;
	int mHosepipe6IndexLocation;

	int mFloorIndexCount;
	int mFloorIndexLocation;

	int mBasketIndexCount;
	int mBasketIndexLocation;

	int mSideWall0IndexCount;
	int mSideWall0IndexLocation;
	int mSideWall1IndexCount;
	int mSideWall1IndexLocation;
	int mSlopeIndexCount;
	int mSlopeIndexLocation;

	int mFrontWallIndexCount;
	int mFrontWallIndexLocation;
	int mBackWallIndexCount;
	int mBackWallIndexLocation;

	int mRedPipe0IndexCount;
	int mRedPipe0IndexLocation;
	int mRedPipe1IndexCount;
	int mRedPipe1IndexLocation;
	int mRedPipe2IndexCount;
	int mRedPipe2IndexLocation;
	int mRedPipe3IndexCount;
	int mRedPipe3IndexLocation;
	int mRedPipe4IndexCount;
	int mRedPipe4IndexLocation;
	int mRedPipe5IndexCount;
	int mRedPipe5IndexLocation;
	int mRedPipe6IndexCount;
	int mRedPipe6IndexLocation;
	int mRedPipe7IndexCount;
	int mRedPipe7IndexLocation;
	
	int mRoomHosePipe0IndexCount;
	int mRoomHosePipe0IndexLocation;
	int mRoomHosePipe1IndexCount;
	int mRoomHosePipe1IndexLocation;
	int mRoomHosePipe2IndexCount;
	int mRoomHosePipe2IndexLocation;
	int mRoomHosePipe3IndexCount;
	int mRoomHosePipe3IndexLocation;
	int mRoomHosePipe4IndexCount;
	int mRoomHosePipe4IndexLocation;
	int mRoomHosePipe5IndexCount;
	int mRoomHosePipe5IndexLocation;
	
	int mCube0IndexCount;
	int mCube0IndexLocation;
	int mCube1IndexCount;
	int mCube1IndexLocation;
	int mCube2IndexCount;
	int mCube2IndexLocation;
	int mCube3IndexCount;
	int mCube3IndexLocation;

	int mSupport0IndexCount;
	int mSupport0IndexLocation;
	int mSupport1IndexCount;
	int mSupport1IndexLocation;
	int mSupport3IndexCount;
	int mSupport3IndexLocation;

	int mRoofIndexCount;
	int mRoofIndexLocation;

	int mDrawing0IndexCount;
	int mDrawing0IndexLocation;
	int mDrawing1IndexCount;
	int mDrawing1IndexLocation;
	int mDrawing2IndexCount;
	int mDrawing2IndexLocation;
	int mDrawing3IndexCount;
	int mDrawing3IndexLocation;

	ID3D11Buffer* mSheepVB;
	ID3D11Buffer* mSheepIB;
	int mSheepIndexCount;

	ID3D11Buffer* mText1VB;
	ID3D11Buffer* mText1IB;
	int mText1IndexCount;

	ID3D11Buffer* mText2VB;
	ID3D11Buffer* mText2IB;
	int mText2IndexCount;

	ID3D11Buffer* mText3VB;
	ID3D11Buffer* mText3IB;
	int mText3IndexCount;

	XNA::AxisAlignedBox mSphereBox;
	XNA::AxisAlignedBox mSheepBox;
	XNA::AxisAlignedBox mCapsuleBox;
	XNA::Frustum mCamFrustum;
	XNA::Frustum mCamFrustum2;

	UINT mVisibleObjectCount;
	UINT mVisibleObjectCount2;
	bool mFrustumCullingEnabled;

	ID3D11Buffer* mSphereVB;
	ID3D11Buffer* mSphereIB;
	int mSphereIndexCount;

	ID3D11Buffer* mSphereVB2;
	ID3D11Buffer* mSphereIB2;
	int mSphereIndexCount2;

	ID3D11Buffer* mScreenQuadVB;
	ID3D11Buffer* mScreenQuadIB;

	ID3D11ShaderResourceView* mOffscreenSRV;
	ID3D11UnorderedAccessView* mOffscreenUAV;
	ID3D11RenderTargetView* mOffscreenRTV;

	ID3D11ShaderResourceView* mOffscreenSRV2;
	ID3D11UnorderedAccessView* mOffscreenUAV2;
	ID3D11RenderTargetView* mOffscreenRTV2;

	BlurFilter mBlur;
	Sky* mSky;

	DirectionalLight mDirLights[3];
	DirectionalLight mCapsuleDirLights[3];
	PointLight mCapsulePointLight;
	SpotLight mCapsuleSpotLight;
	SpotLight mSpaceSpotLight;
	SpotLight mNoSpotLight;
	Material mSphereMat;
	Material mTextMat;
	Material mCapsuleMat;
	Material mRoomMat;

	XMFLOAT4X4 mSphereWorld;
	XMFLOAT4X4 mSphereWorld2;
	XMFLOAT4X4 mSheepWorld;
	XMFLOAT4X4 mText1World;
	XMFLOAT4X4 mText2World;
	XMFLOAT4X4 mText3World;
	XMFLOAT4X4 mCapsuleWorld;
	XMFLOAT4X4 mRoomWorld;

	RenderOptions mRenderOptions;

	Camera mCam;
	Camera mCam2;

	POINT mLastMousePos;

	int mSceneNumber;
	int mSubSceneNumber;
	float mBeatNumber;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {

#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	if(!XMVerifyCPUSupport()) {
		cout << "xna math not supported" << endl;
		return 0;
	}

	BoxApp theApp(hInstance);

	if(!theApp.Init()) {
		return 0;
	}

	return theApp.Run();
}

BoxApp::BoxApp(HINSTANCE hInstance) : D3DApp(hInstance), mSky(0), mLandVB(0), mLandIB(0), mSphereVB(0), mSphereIB(0), mSphereVB2(0), mSphereIB2(0), mCapsuleVB(0), mCapsuleIB(0), mCapsuleDiffuseMapSRV(0), mCapsuleNormalMapSRV(0), mInstancedBuffer(0), mInstancedBuffer2(0), mCapsuleInstancedData(0), mScreenQuadVB(0), mScreenQuadIB(0), mOffscreenSRV(0), mOffscreenUAV(0), mOffscreenRTV(0), mOffscreenSRV2(0), mOffscreenUAV2(0), mOffscreenRTV2(0), mSphereIndexCount(0), mRenderOptions(RenderOptions::TexturesAndFog), mFrustumCullingEnabled(false) {
	mMainWndCaption = L"Now Loading... 1 minute 16 seconds";
	mEnable4xMsaa = false;

	mSceneNumber = 0;
	//mSceneNumber = 1;
	mSubSceneNumber = 0;
	mBeatNumber = 0.0f;

	mLastMousePos.x = 0;
	mLastMousePos.y = 0;

	mCam.SetPosition(45.0f, 21.0f, 0.0f);
	mCam.RotateY(-MathHelper::Pi + MathHelper::Pi / 2.9f);
	mCam.Pitch(MathHelper::Pi / 8.0f);

	//mCam.SetDefault();
	//mCam.SetPosition(28.0f, 15.0f, -40.0f);
	//mCam.RotateY(MathHelper::Pi);
	//mCam.Pitch(MathHelper::Pi / 2.0f);

	mCam2.SetPosition(10.0f, 0.0f, -5.0f);

	//mCam2.SetPosition(13.0f, -2.0f, 28.0f);
	//mCam2.RotateY(MathHelper::Pi / 2.0f - MathHelper::Pi / 8.0f);
	//mCam2.Pitch(-MathHelper::Pi / 8.0f);
	//mCam2.SetPosition(10.0f, 0.0f, -5.0f);
	//mCam2.RotateY(-MathHelper::Pi / 2.0f);
	

	XMMATRIX I = XMMatrixIdentity();

	XMMATRIX boxScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	XMMATRIX boxOffset = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	XMStoreFloat4x4(&mSphereWorld, XMMatrixMultiply(boxScale, boxOffset));

	XMMATRIX sheepScale = XMMatrixScaling(8.0f, 8.0f, 8.0f);
	XMMATRIX sheepOffset = XMMatrixTranslation(25.0f, 10.0f, -80.0f);
	XMStoreFloat4x4(&mSheepWorld, XMMatrixMultiply(sheepScale, sheepOffset));

	XMMATRIX text1Scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	XMMATRIX text1Offset = XMMatrixTranslation(20.0f, 12.5f, -62.0f);
	XMMATRIX text1Rotate = XMMatrixRotationX(MathHelper::Pi / -2.0f);
	XMMATRIX text1world = text1Scale * text1Rotate * text1Offset;
	XMStoreFloat4x4(&mText1World, text1world);

	XMMATRIX text2Scale = XMMatrixScaling(2.0f, 2.0f, 2.0f);
	XMMATRIX text2Offset = XMMatrixTranslation(44.0f, -20.0f, -35.0f);
	XMMATRIX text2Rotate = XMMatrixRotationX(-MathHelper::Pi);
	//XMMATRIX text2Rotate2 = XMMatrixRotationZ(-MathHelper::Pi);
	//XMMATRIX text2world = text2Scale * text2Rotate * text2Rotate2 * text2Offset;
	XMMATRIX text2world = text2Scale * text2Rotate * text2Offset;
	XMStoreFloat4x4(&mText2World, text2world);

	XMMATRIX text3Scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	XMMATRIX text3Offset = XMMatrixTranslation(6.0f, 2.0f, 13.0f);
	XMMATRIX text3Rotate = XMMatrixRotationX(-MathHelper::Pi / 2.0f);
	XMMATRIX text3Rotate2 = XMMatrixRotationY(MathHelper::Pi);
	XMMATRIX text3world = text3Scale * text3Rotate * text3Rotate2 * text3Offset;
	//XMMATRIX text3world = text3Scale * text3Offset;
	XMStoreFloat4x4(&mText3World, text3world);

	XMMATRIX capsuleScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	XMMATRIX capsuleOffset = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	XMStoreFloat4x4(&mCapsuleWorld, XMMatrixMultiply(capsuleScale, capsuleOffset));

	XMMATRIX roomScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	XMMATRIX roomOffset = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	XMStoreFloat4x4(&mRoomWorld, XMMatrixMultiply(roomScale, roomOffset));

	/*mDirLights[0].Ambient  = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	mDirLights[0].Diffuse  = XMFLOAT4(0.87f, 0.85f, 0.95f, 1.0f);
	mDirLights[0].Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 16.0f);*/
	//mDirLights[0].Direction = XMFLOAT3(0.0f, -0.707f, -0.707f);
	//mDirLights[0].Direction = XMFLOAT3(-0.57735f, -0.57735f, 0.57735f);
	mDirLights[0].Direction = XMFLOAT3(0.57735f, -0.57735f, 0.57735f);
	mDirLights[0].Ambient  = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	mDirLights[0].Diffuse  = XMFLOAT4(0.87f, 0.85f, 0.95f, 1.0f);
	mDirLights[0].Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	//mDirLights[0].Direction = XMFLOAT3(0.57735f, -0.57735f, 0.57735f);

	mDirLights[1].Ambient  = XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f);
	mDirLights[1].Diffuse  = XMFLOAT4(0.50f, 0.50f, 0.50f, 1.0f);
	mDirLights[1].Specular = XMFLOAT4(0.75f, 0.75f, 0.75f, 1.0f);
	mDirLights[1].Direction = XMFLOAT3(-0.57735f, -0.57735f, 0.57735f);

	mDirLights[2].Ambient  = XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f);
	mDirLights[2].Diffuse  = XMFLOAT4(0.85f, 0.85f, 0.85f, 1.0f);
	mDirLights[2].Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 16.0f);
	mDirLights[2].Direction = XMFLOAT3(0.0f, -0.707f, -0.707f);

	mSphereMat.Ambient  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mSphereMat.Diffuse  = XMFLOAT4(0.878f, 0.865f, 0.895f, 1.0f);
	mSphereMat.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 96.0f);
	//mSphereMat.Ambient  = XMFLOAT4(0.137f, 0.42f, 0.556f, 1.0f);
	//mSphereMat.Diffuse  = XMFLOAT4(0.137f, 0.42f, 0.556f, 1.0f);
	//mSphereMat.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 96.0f);

	mTextMat.Ambient  = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	mTextMat.Diffuse  = XMFLOAT4(0.482353f, 0.705882f, 0.811765f, 1.0f);
	mTextMat.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 96.0f);

	//mDirLights[0].Direction = XMFLOAT3(0.0f, -0.707f, -0.707f);
	//mCapsuleDirLights[0].Direction = XMFLOAT3(-0.57735f, -0.57735f, 0.57735f);
	mCapsuleDirLights[0].Direction = XMFLOAT3(0.57735f, -0.57735f, 0.57735f);
	mCapsuleDirLights[0].Ambient  = XMFLOAT4(0.001f, 0.01f, 0.01f, 1.0f);
	mCapsuleDirLights[0].Diffuse  = XMFLOAT4(0.08f, 0.08f, 0.08f, 1.0f);
	mCapsuleDirLights[0].Specular = XMFLOAT4(0.05f, 0.05f, 0.0f, 1.0f);
	//mCapsuleDirLights[0].Direction = XMFLOAT3(0.57735f, -0.57735f, 0.57735f);
	//mCapsuleDirLights[0].Ambient  = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//mCapsuleDirLights[0].Diffuse  = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//mCapsuleDirLights[0].Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	mCapsuleDirLights[1].Ambient  = XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f);
	mCapsuleDirLights[1].Diffuse  = XMFLOAT4(0.50f, 0.50f, 0.50f, 1.0f);
	mCapsuleDirLights[1].Specular = XMFLOAT4(0.75f, 0.75f, 0.75f, 1.0f);
	mCapsuleDirLights[1].Direction = XMFLOAT3(-0.57735f, -0.57735f, 0.57735f);

	mCapsuleDirLights[2].Ambient  = XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f);
	mCapsuleDirLights[2].Diffuse  = XMFLOAT4(0.85f, 0.85f, 0.85f, 1.0f);
	mCapsuleDirLights[2].Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 16.0f);
	mCapsuleDirLights[2].Direction = XMFLOAT3(0.0f, -0.707f, -0.707f);

	mCapsulePointLight.Ambient  = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	mCapsulePointLight.Diffuse  = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	mCapsulePointLight.Specular = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	mCapsulePointLight.Att      = XMFLOAT3(0.0f, 0.1f, 0.0f);
	mCapsulePointLight.Range    = 25.0f;

	// Spot light--position and direction changed every frame to animate in UpdateScene function.
	mCapsuleSpotLight.Ambient  = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mCapsuleSpotLight.Diffuse  = XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f);
	mCapsuleSpotLight.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	mCapsuleSpotLight.Att      = XMFLOAT3(0.0f, 0.15f, 0.0f);
	mCapsuleSpotLight.Spot     = 24.0f;
	mCapsuleSpotLight.Range    = 10000.0f;
	mCapsuleSpotLight.Pad = 1.0f;

	/*
	mSpaceSpotLight.Ambient  = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mSpaceSpotLight.Diffuse  = XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f);
	mSpaceSpotLight.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	mSpaceSpotLight.Att      = XMFLOAT3(0.0f, 0.15f, 0.0f);
	mSpaceSpotLight.Spot     = 24.0f;
	mSpaceSpotLight.Range    = 10000.0f;
	mSpaceSpotLight.Pad = 1.0f;*/

	mSpaceSpotLight.Ambient  = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	mSpaceSpotLight.Diffuse  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mSpaceSpotLight.Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mSpaceSpotLight.Att      = XMFLOAT3(1.0f, 0.0f, 0.0f);
	mSpaceSpotLight.Spot     = 12.0f;
	mSpaceSpotLight.Range    = 10000.0f;
	mSpaceSpotLight.Pad = 1.0f;

	mNoSpotLight.Ambient  = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mNoSpotLight.Diffuse  = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mNoSpotLight.Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mNoSpotLight.Att      = XMFLOAT3(1.0f, 0.0f, 0.0f);
	mNoSpotLight.Spot     = 48.0f;
	mNoSpotLight.Range    = 10000.0f;
	mNoSpotLight.Pad = 1.0f;

	mCapsuleMat.Ambient  = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	mCapsuleMat.Diffuse  = XMFLOAT4(0.878f, 0.865f, 0.895f, 1.0f);
	mCapsuleMat.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);

	mRoomMat.Ambient  = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	mRoomMat.Diffuse  = XMFLOAT4(0.878f, 0.865f, 0.895f, 1.0f);
	mRoomMat.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
}

BoxApp::~BoxApp() {
	md3dImmediateContext->ClearState();

	SafeDelete(mSky);

	ReleaseCOM(mLandVB);
	ReleaseCOM(mLandIB);
	ReleaseCOM(mSphereVB);
	ReleaseCOM(mSphereIB);
	ReleaseCOM(mSphereVB2);
	ReleaseCOM(mSphereIB2);
	ReleaseCOM(mRoomVB);
	ReleaseCOM(mRoomIB);
	ReleaseCOM(mScreenQuadVB);
	ReleaseCOM(mScreenQuadIB);
	ReleaseCOM(mCapsuleVB);
	ReleaseCOM(mCapsuleIB);
	ReleaseCOM(mSheepVB);
	ReleaseCOM(mSheepIB);
	ReleaseCOM(mText1VB);
	ReleaseCOM(mText1IB);
	ReleaseCOM(mText2VB);
	ReleaseCOM(mText2IB);
	ReleaseCOM(mText3VB);
	ReleaseCOM(mText3IB);
	ReleaseCOM(mCapsuleDiffuseMapSRV);
	ReleaseCOM(mCapsuleNormalMapSRV);
	ReleaseCOM(mHumanShieldDiffuseMapSRV);
	ReleaseCOM(mHumanShieldNormalMapSRV);
	ReleaseCOM(mHosepipeDiffuseMapSRV);
	ReleaseCOM(mHosepipeNormalMapSRV);
	ReleaseCOM(mScuffedPlasticDiffuseMapSRV);
	ReleaseCOM(mScuffedPlasticNormalMapSRV);
	ReleaseCOM(mMetalGridDiffuseMapSRV);
	ReleaseCOM(mMetalGridNormalMapSRV);
	ReleaseCOM(mScifiFloorDiffuseMapSRV);
	ReleaseCOM(mScifiFloorNormalMapSRV);
	ReleaseCOM(mStorageContainerDiffuseMapSRV);
	ReleaseCOM(mStorageContainerNormalMapSRV);
	ReleaseCOM(mChippedPaintMetalDiffuseMapSRV);
	ReleaseCOM(mChippedPaintMetalNormalMapSRV);
	ReleaseCOM(mPlasticPaddedDiffuseMapSRV);
	ReleaseCOM(mPlasticPaddedNormalMapSRV);
	ReleaseCOM(mRustedironStreaksDiffuseMapSRV);
	ReleaseCOM(mRustedironStreaksNormalMapSRV);
	ReleaseCOM(mCircleMetalGridDiffuseMapSRV);
	ReleaseCOM(mCircleMetalGridNormalMapSRV);
	ReleaseCOM(mIronRustedDiffuseMapSRV0);
	ReleaseCOM(mIronRustedDiffuseMapSRV1);
	ReleaseCOM(mIronRustedDiffuseMapSRV2);
	ReleaseCOM(mIronRustedDiffuseMapSRV3);
	ReleaseCOM(mIronRustedNormalMapSRV);
 
	ReleaseCOM(mOffscreenSRV);
	ReleaseCOM(mOffscreenUAV);
	ReleaseCOM(mOffscreenRTV);

	ReleaseCOM(mOffscreenSRV2);
	ReleaseCOM(mOffscreenUAV2);
	ReleaseCOM(mOffscreenRTV2);

	Effects::DestroyAll();
	InputLayouts::DestroyAll();
	RenderStates::DestroyAll();
}

bool BoxApp::Init() {
	if(!D3DApp::Init())
		return false;

	// Must init Effects first since InputLayouts depend on shader signatures.
	Effects::InitAll(md3dDevice);
	InputLayouts::InitAll(md3dDevice);
	RenderStates::InitAll(md3dDevice);

	mSky = new Sky(md3dDevice, L"10.dds", 5000.0f);

	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"greasy-metal-pan1-albedo.png", 0, 0, &mCapsuleDiffuseMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"greasy-metal-pan1-normal.png", 0, 0, &mCapsuleNormalMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"TexturesCom_DecalsLeaking0208_2_S.jpg", 0, 0, &mHumanShieldDiffuseMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"TexturesCom_DecalsLeaking0208_1_masked_S.png", 0, 0, &mHumanShieldNormalMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"synth-rubber-albedo.png", 0, 0, &mHosepipeDiffuseMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"synth-rubber-normal.png", 0, 0, &mHosepipeNormalMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"scuffed-plastic4-alb.png", 0, 0, &mScuffedPlasticDiffuseMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"scuffed-plastic-normal.png", 0, 0, &mScuffedPlasticNormalMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"metalgrid3_basecolor.png", 0, 0, &mMetalGridDiffuseMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"metalgrid3_normal-ogl.png", 0, 0, &mMetalGridNormalMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"TexturesCom_Scifi_Floor4_1K_albedo.tif", 0, 0, &mScifiFloorDiffuseMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"TexturesCom_Scifi_Floor4_1K_normal.tif", 0, 0, &mScifiFloorNormalMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"storage-container2-albedo.png", 0, 0, &mStorageContainerDiffuseMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"storage-container2-normal-ogl.png", 0, 0, &mStorageContainerNormalMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"chipped-paint-metal-albedo.png", 0, 0, &mChippedPaintMetalDiffuseMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"chipped-paint-metal-normal-ogl.png", 0, 0, &mChippedPaintMetalNormalMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"TexturesCom_Plastic_Padded_1K_albedo.tif", 0, 0, &mPlasticPaddedDiffuseMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"TexturesCom_Plastic_Padded_1K_normal.tif", 0, 0, &mPlasticPaddedNormalMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"rustediron-streaks_basecolor.png", 0, 0, &mRustedironStreaksDiffuseMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"rustediron-streaks_normal.png", 0, 0, &mRustedironStreaksNormalMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"TexturesCom_Metal_Grid_1K_albedo.tif", 0, 0, &mCircleMetalGridDiffuseMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"TexturesCom_Metal_Grid_1K_normal.tif", 0, 0, &mCircleMetalGridNormalMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"iron-rusted_sp1-basecolor.png", 0, 0, &mIronRustedDiffuseMapSRV0, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"iron-rusted_sp2-basecolor.png", 0, 0, &mIronRustedDiffuseMapSRV1, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"iron-rusted_sp3-basecolor.png", 0, 0, &mIronRustedDiffuseMapSRV2, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"iron-rusted_sp4-basecolor.png", 0, 0, &mIronRustedDiffuseMapSRV3, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, L"iron-rusted4-normal.png", 0, 0, &mIronRustedNormalMapSRV, 0));
	

	BuildCrateGeometryBuffers();
	BuildSheepGeometryBuffers();
	BuildTextGeometryBuffers();
	BuildCapsuleGeometryBuffers();
	BuildRoomGeometryBuffers();
	BuildInstancedBuffer();
	BuildScreenQuadGeometryBuffers();
	BuildOffscreenViews();

	//LPCWSTR a = L"open tlfn-rhino.mp3 type mpegvideo";
	//int error = 99;
	//error = mciSendString(a, NULL,0,0);
	//int error2;
	//LPCWSTR b = L"play tlfn-rhino.mp3";
	//error2 = mciSendString(b, NULL, 0, 0);

	return true;
}

void BoxApp::OnResize() {
	D3DApp::OnResize();

	// Recreate the resources that depend on the client area size.
	BuildOffscreenViews();
	mBlur.Init(md3dDevice, mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM);

	mCam.SetLens(0.25f * MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
	mCam2.SetLens(0.25f * MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);

	// Build the frustum from the projection matrix in view space.
	ComputeFrustumFromProjection(&mCamFrustum, &mCam.Proj());
	ComputeFrustumFromProjection(&mCamFrustum2, &mCam2.Proj());
}

void BoxApp::UpdateScene(float dt) {
	if( GetAsyncKeyState(VK_ESCAPE) & 0x8000 ) {
		PostMessage(mhMainWnd, WM_CLOSE, 0, 0);
	}

	float run = 1.0f;

	if( GetAsyncKeyState(VK_SHIFT) & 0x8000 ) {
		run = 2.0f;
	}

	// Control the camera.
	if( GetAsyncKeyState('W') & 0x8000 ) {
		mCam.Walk(10.0f * dt * run);
		mCam2.Walk(10.0f * dt * run);
	}

	if( GetAsyncKeyState('S') & 0x8000 ) {
		mCam.Walk(-10.0f * dt * run);
		mCam2.Walk(-10.0f * dt * run);
	}

	if( GetAsyncKeyState('A') & 0x8000 ) {
		mCam.Strafe(-10.0f * dt * run);
		mCam2.Strafe(-10.0f * dt * run);
	}

	if( GetAsyncKeyState('D') & 0x8000 ) {
		mCam.Strafe(10.0f * dt * run);
		mCam2.Strafe(10.0f * dt * run);
	}

	// Switch the render mode based in key input.
	if( GetAsyncKeyState('1') & 0x8000 ) {
		mRenderOptions = RenderOptions::Lighting; 
	}

	if( GetAsyncKeyState('2') & 0x8000 ) {
		mRenderOptions = RenderOptions::Textures;
	}

	if( GetAsyncKeyState('3') & 0x8000 ) {
		mRenderOptions = RenderOptions::TexturesAndFog;
	}



	//float bpm = 132.0f;
	float bpm = 133.0f;
	float bps = bpm / 60.0f;
	float oneBeatSec = 1 / bps;
	mBeatNumber = mTimer.TotalTime() / oneBeatSec;
	{
		XMMATRIX sheepScale = XMMatrixScaling(8.0f, 8.0f, 8.0f);
		XMMATRIX sheepOffset = XMMatrixTranslation(25.0f, 10.0f, -80.0f + mTimer.TotalTime() * 2.8f);
		XMMATRIX sheepWorld = sheepScale * sheepOffset;
		XMStoreFloat4x4(&mSheepWorld, sheepWorld);
	}

	{
		/*
		XMMATRIX world = XMLoadFloat4x4(&mText1World);
		XMMATRIX boxOffset = XMMatrixTranslation(0.0f, 0.0f, mTimer.TotalTime() / 6000.0f);
		//XMMATRIX boxRotate = XMMatrixRotationY(0.0f);
		world = world * boxOffset;
		XMStoreFloat4x4(&mText1World, world);*/
		XMMATRIX text1Scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
		XMMATRIX text1Offset = XMMatrixTranslation(31.0f, 13.f, -61.0f);
		XMMATRIX text1Offset2 = XMMatrixTranslation(4.5f, 0.0f, 0.0f);
		XMMATRIX text1Rotate = XMMatrixRotationX(MathHelper::Pi / -2.0f);
		XMMATRIX text1Rotate2 = XMMatrixRotationY(-MathHelper::Pi / 4.0f + MathHelper::Pi / (mTimer.TotalTime() + 1.5f));
		XMMATRIX text1world = text1Scale * text1Rotate * text1Offset2 * text1Rotate2 * text1Offset;
		XMStoreFloat4x4(&mText1World, text1world);
	}

	{
		XMMATRIX boxScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
		XMMATRIX boxOffset = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
		XMMATRIX boxRotate = XMMatrixRotationY(-mTimer.TotalTime() * 2.0f);
		XMMATRIX world = boxScale * boxRotate * boxOffset;
		XMStoreFloat4x4(&mSphereWorld, world);
	}

	{
		XMMATRIX boxScale = XMMatrixScaling(10.0f, 10.0f, 10.0f);
		XMMATRIX boxOffset = XMMatrixTranslation(0.0f, -10.0f, 0.0f);
		XMMATRIX boxRotate = XMMatrixIdentity();
		XMMATRIX world = boxScale * boxRotate * boxOffset;
		XMStoreFloat4x4(&mSphereWorld2, world);
	}

	
	//mSubSceneNumber = 1;
	//mSceneNumber = 1;
	//mCam2.SetDefault();
	//mCam2.SetPosition(10.0f, 0.0f, -5.0f);
	//mCam2.SetDefault();
	//mCam2.SetPosition(0.0f, -10.0f, 35.0f);
	//mCam2.RotateY(MathHelper::Pi / 2.0f);
	//mCam2.Pitch(MathHelper::Pi / 8.0f);
	{

		if(mBeatNumber >= 0.0f && mBeatNumber < 16.0f) {
			mCam.SetDefault();
			mCam.SetPosition(27.0f, 11.0f, -50.0f);
			mCam.RotateY(MathHelper::Pi - MathHelper::Pi / 16);
			mCam.Pitch(-MathHelper::Pi / 16.0f);
		}
		else if(mBeatNumber >= 16.0f && mBeatNumber < 32.0f) {
			mSubSceneNumber = 1;
			mCam.SetDefault();
			mCam.SetPosition(28.0f, 15.0f, -40.0f);
			mCam.RotateY(MathHelper::Pi);
			mCam.Pitch(MathHelper::Pi / 2.0f);
		}
		else if(mBeatNumber >= 32.0f && mBeatNumber < 48.0f) {
			mCam.SetDefault();
			mCam.SetPosition(45.0f, 21.0f, 0.0f);
			mCam.RotateY(-MathHelper::Pi + MathHelper::Pi / 3.0f);
			mCam.Pitch(MathHelper::Pi / 8.0f);
		}
		else if(mBeatNumber >= 48.0f && mBeatNumber < 64.0f) {
			mSceneNumber = 1;
			float start = 48.0f * oneBeatSec;
			float tt = mTimer.TotalTime();
			float yy = (tt - start) * 1.4f;
			mCam2.SetDefault();
			//mCam2.SetPosition(13.0f, -2.0f, 28.0f - mTimer.TotalTime() - co);
			mCam2.SetPosition(12.5f, -2.0f, 27.5f - yy);
			mCam2.RotateY(MathHelper::Pi / 2.0f - MathHelper::Pi / 16.0f);
			mCam2.Pitch(-MathHelper::Pi / 8.0f);
		}
		else if(mBeatNumber >= 64.0f && mBeatNumber < 80.0f) {
			mSceneNumber = 1;
			float start = 64.0f * oneBeatSec;
			float tt = mTimer.TotalTime();
			float yy = tt - start;
			mCam2.SetDefault();
			//mCam2.SetPosition(10.0f, 0.0f, -5.0f + mTimer.TotalTime() - co);
			mCam2.SetPosition(10.0f, -1.0f, -5.0f + yy);
			mCam2.RotateY(-MathHelper::Pi / 2.0f);
			mCam2.Pitch(-MathHelper::Pi / 16.0f);
		}
		else if(mBeatNumber >= 80 && mBeatNumber < 96.0f) {
			mSceneNumber = 1;
			float start = 80.0f * oneBeatSec;
			float startPrev = 64.0f * oneBeatSec;
			float tt = mTimer.TotalTime();
			float yy = (tt - start) * 20.0f;
			float yy2 = (tt - start) * 0.125f;
			float yyPrev = tt - startPrev;
			mCam2.SetDefault();
			mCam2.SetPosition(10.0f, -1.0f, -5.0f + yyPrev + yy);
			mCam2.RotateY(-MathHelper::Pi / 2.0f + MathHelper::Pi * yy2);
			mCam2.Pitch(-MathHelper::Pi / 16.0f);
		}
		else if(mBeatNumber >= 96 && mBeatNumber < 112.0f) {
			mSceneNumber = 1;
			mSubSceneNumber = 2;
			float start = 96.0f * oneBeatSec;
			float tt = mTimer.TotalTime();
			float yy = tt - start;
			mCam2.SetDefault();
			//mCam2.SetPosition(10.0f, 0.0f, -5.0f + mTimer.TotalTime() - co);
			mCam2.SetPosition(10.0f, 0.0f, -5.0f + yy);
			//mCam2.RotateY(MathHelper::Pi);
		}
		else {
			mCam2.SetPosition(0.0f, 0.0f, -5.0f);
			mCam.SetDefault();
			mCam.SetPosition(45.0f, 21.0f, 0.0f);
			mCam.RotateY(-MathHelper::Pi + MathHelper::Pi / 3.0f);
			mCam.Pitch(MathHelper::Pi / 8.0f);
			PostMessage(mhMainWnd, WM_CLOSE, 0, 0);
		}
	}

	XMFLOAT3 pos = mCam2.GetPosition();
	if(pos.z > 43.0f) {
		pos.z -= 43.0f;
		mCam2.SetPosition(pos);
	}

	// Perform frustum culling.
	mVisibleObjectCount = 0;
	mCam.UpdateViewMatrix();
	mCam2.UpdateViewMatrix();

	if(mFrustumCullingEnabled) {
		XMVECTOR detView = XMMatrixDeterminant(mCam.View());
		XMMATRIX invView = XMMatrixInverse(&detView, mCam.View());
	
		D3D11_MAPPED_SUBRESOURCE mappedData; 
		md3dImmediateContext->Map(mInstancedBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);

		Instance::InstancedData* dataView = reinterpret_cast<Instance::InstancedData*>(mappedData.pData);

		for(UINT i = 0; i < mInstancedData.size(); ++i) {
			XMMATRIX W = XMLoadFloat4x4(&mInstancedData[i].World);
			XMMATRIX invWorld = XMMatrixInverse(&XMMatrixDeterminant(W), W);

			// View space to the object's local space.
			XMMATRIX toLocal = XMMatrixMultiply(invView, invWorld);
		
			// Decompose the matrix into its individual parts.
			XMVECTOR scale;
			XMVECTOR rotQuat;
			XMVECTOR translation;
			XMMatrixDecompose(&scale, &rotQuat, &translation, toLocal);

			// Transform the camera frustum from view space to the object's local space.
			XNA::Frustum localspaceFrustum;
			XNA::TransformFrustum(&localspaceFrustum, &mCamFrustum, XMVectorGetX(scale), rotQuat, translation);

			// Perform the box/frustum intersection test in local space.
			if(XNA::IntersectAxisAlignedBoxFrustum(&mSphereBox, &localspaceFrustum) != 0) {
				// Write the instance data to dynamic VB of the visible objects.
				dataView[mVisibleObjectCount++] = mInstancedData[i];
			}
		}

		md3dImmediateContext->Unmap(mInstancedBuffer, 0);
	}
	else { // No culling enabled, draw all objects.

		/*
		D3D11_MAPPED_SUBRESOURCE mappedData; 
		md3dImmediateContext->Map(mInstancedBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);

		Instance::InstancedData* dataView = reinterpret_cast<Instance::InstancedData*>(mappedData.pData);

		for(UINT i = 0; i < mInstancedData.size(); ++i) {
			dataView[mVisibleObjectCount++] = mInstancedData[i];
		}

		md3dImmediateContext->Unmap(mInstancedBuffer, 0);*/
		mVisibleObjectCount = mInstancedData.size();
		mVisibleObjectCount2 = mInstancedData2.size();
	}

	mCapsuleSpotLight.Position = mCam2.GetPosition();
	mCapsuleSpotLight.Direction = mCam2.GetLook();
	if(mSceneNumber == 0) {
		mSpaceSpotLight.Position = mCam.GetPosition();
		mSpaceSpotLight.Direction = mCam.GetLook();
	}
	if(mSceneNumber == 1) {
		mSpaceSpotLight.Position = mCam2.GetPosition();
		mSpaceSpotLight.Direction = mCam2.GetLook();
	}

	/*XMFLOAT3 pos = mCam2.GetPosition();
	if(pos.z > 43.0f) {
		pos.z -= 43.0f;
		mCam2.SetPosition(pos);
	}*/

	//mCapsuleSpotLight.Position = XMFLOAT3(0.0f, 0.0f, -5.0f);
	//mCapsuleSpotLight.Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);

	//std::wostringstream outs;
	//outs.precision(6);
	//outs << L"    " << mVisibleObjectCount << L" objects drawn " << mCam2.GetPosition().x << " " << mCam2.GetPosition().y << " " << mCam2.GetPosition().z;
	//mMainWndCaption = outs.str();
}

void BoxApp::DrawScene() {
	// Render to our offscreen texture.  Note that we can use the same depth/stencil buffer
	// we normally use since our offscreen texture matches the dimensions.

	if(mSceneNumber == 0) {
		
		ID3D11RenderTargetView* renderTargets[2] = {mOffscreenRTV2, mOffscreenRTV};
		md3dImmediateContext->OMSetRenderTargets(2, renderTargets, mDepthStencilView);

		md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Black2));
		md3dImmediateContext->ClearRenderTargetView(mOffscreenRTV, reinterpret_cast<const float*>(&Colors::Black2));
		md3dImmediateContext->ClearRenderTargetView(mOffscreenRTV2, reinterpret_cast<const float*>(&Colors::Black2));
		md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

		// Draw the scene to the offscreen texture
		DrawWrapper2();
		if(mSubSceneNumber == 0) {
			DrawWrapper2_2();
		}
		if(mSubSceneNumber == 1) {
			DrawWrapper2_3();
		}
		DrawWrapper();

		mSky->Draw(md3dImmediateContext, mCam);

		// Restore the back buffer.  The offscreen render target will serve as an input into
		// the compute shader for blurring, so we must unbind it from the OM stage before we
		// can use it as an input into the compute shader.
		renderTargets[0] = mRenderTargetView;
		md3dImmediateContext->OMSetRenderTargets(1, renderTargets, mDepthStencilView);

		mBlur.BlurInPlace(md3dImmediateContext, mOffscreenSRV, mOffscreenUAV, 8);

		// Draw fullscreen quad with texture of blurred scene on it.
		md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::DarkDirtyGreen2));
		md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

		DrawScreenQuad();
	}

	if(mSceneNumber == 1) {
		
		ID3D11RenderTargetView* renderTargets[1] = {mRenderTargetView};
		md3dImmediateContext->OMSetRenderTargets(1, renderTargets, mDepthStencilView);
		
		md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::DarkDirtyGreen));
		md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

		// Draw the scene to the offscreen texture
		DrawWrapper3();
		DrawWrapper4();
		if(mSubSceneNumber == 2) {
			DrawWrapper2_4();
		}
	}

	HR(mSwapChain->Present(0, 0));
}

void BoxApp::OnMouseDown(WPARAM btnState, int x, int y) {
	mLastMousePos.x = x;
	mLastMousePos.y = y;

	SetCapture(mhMainWnd);
}

void BoxApp::OnMouseUp(WPARAM btnState, int x, int y) {
	ReleaseCapture();
}

void BoxApp::OnMouseMove(WPARAM btnState, int x, int y) {
	if( (btnState & MK_LBUTTON) != 0 ) {
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f * static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f * static_cast<float>(y - mLastMousePos.y));

		mCam.Pitch(dy);
		mCam.RotateY(dx);
		mCam2.Pitch(dy);
		mCam2.RotateY(dx);
	}

	mLastMousePos.x = x;
	mLastMousePos.y = y;
}

void BoxApp::DrawWrapper() {
	float blendFactor[] = {0.0f, 0.0f, 0.0f, 0.0f};

	md3dImmediateContext->IASetInputLayout(InputLayouts::InstancedMTR);
    md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
 
	UINT stride[2] = {sizeof(Vertex::Position), sizeof(Instance::InstancedData)};
    UINT offset[2] = {0, 0};

	ID3D11Buffer* vbs[2] = {mSphereVB, mInstancedBuffer};
 
	XMMATRIX view     = mCam.View();
	XMMATRIX proj     = mCam.Proj();
	XMMATRIX viewProj = mCam.ViewProj();
	XMMATRIX identity = XMMatrixIdentity();

	// Set per frame constants.
	Effects::InstancedBasicMTRFX->SetEyePosW(mCam.GetPosition());
	Effects::InstancedBasicMTRFX->SetFogColor(Colors::Silver);
	Effects::InstancedBasicMTRFX->SetFogStart(5.0f);
	Effects::InstancedBasicMTRFX->SetFogRange(100.0f);
 
	ID3DX11EffectTechnique* activeTech = Effects::InstancedBasicMTRFX->Tech1;
	 
    D3DX11_TECHNIQUE_DESC techDesc;
    activeTech->GetDesc( &techDesc );
	for(UINT p = 0; p < techDesc.Passes; ++p) {
		md3dImmediateContext->IASetVertexBuffers(0, 2, vbs, stride, offset);
		md3dImmediateContext->IASetIndexBuffer(mSphereIB, DXGI_FORMAT_R32_UINT, 0);

		XMMATRIX world = XMLoadFloat4x4(&mSphereWorld);
		XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);

		Effects::InstancedBasicMTRFX->SetWorld(world);
		Effects::InstancedBasicMTRFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::InstancedBasicMTRFX->SetViewProj(viewProj);

		//activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		//md3dImmediateContext->DrawIndexed(mSphereIndexCount, 0, 0);

		md3dImmediateContext->OMSetBlendState(RenderStates::NormalDoubleBS, blendFactor, 0xffffffff);

		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexedInstanced(mSphereIndexCount, mVisibleObjectCount, 0, 0, 0);

		vbs[0] = mSphereVB2;
		vbs[1] = mInstancedBuffer2;
		md3dImmediateContext->IASetVertexBuffers(0, 2, vbs, stride, offset);
		md3dImmediateContext->IASetIndexBuffer(mSphereIB2, DXGI_FORMAT_R32_UINT, 0);

		world = XMLoadFloat4x4(&mSphereWorld2);
		worldInvTranspose = MathHelper::InverseTranspose(world);

		Effects::InstancedBasicMTRFX->SetWorld(world);
		Effects::InstancedBasicMTRFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::InstancedBasicMTRFX->SetViewProj(viewProj);

		//activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		//md3dImmediateContext->DrawIndexed(mSphereIndexCount, 0, 0);

		md3dImmediateContext->OMSetBlendState(RenderStates::NormalDoubleBS, blendFactor, 0xffffffff);

		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexedInstanced(mSphereIndexCount2, mVisibleObjectCount2, 0, 0, 0);



		md3dImmediateContext->OMSetBlendState(0, blendFactor, 0xffffffff);
		md3dImmediateContext->RSSetState(0);
	}




	

	ID3D11ShaderResourceView* nullSRV[1] = { 0 };
	Effects::InstancedBasicFX->SetDiffuseMap(nullSRV[0]);
	activeTech->GetPassByIndex(0)->Apply(0, md3dImmediateContext);
}

void BoxApp::DrawWrapper2() {

	md3dImmediateContext->IASetInputLayout(InputLayouts::PosNormal);
    md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	UINT stride = sizeof(Vertex::PosNormal);
    UINT offset = 0;

	XMMATRIX view     = mCam.View();
	XMMATRIX proj     = mCam.Proj();
	XMMATRIX viewProj = mCam.ViewProj();
	XMMATRIX identity = XMMatrixIdentity();
 
	// Set per frame constants.
	Effects::BasicFX->SetDirLights(mDirLights);
	Effects::BasicFX->SetSpotLights(mNoSpotLight);
	Effects::BasicFX->SetEyePosW(mCam.GetPosition());
	Effects::BasicFX->SetEyePosW(mCam.GetPosition());
 
	// Figure out which technique to use.
	ID3DX11EffectTechnique* activeTech = Effects::BasicFX->Light1Tech;
    D3DX11_TECHNIQUE_DESC techDesc;
    activeTech->GetDesc(&techDesc);
    for(UINT p = 0; p < techDesc.Passes; ++p) {
		md3dImmediateContext->IASetVertexBuffers(0, 1, &mSheepVB, &stride, &offset);
		md3dImmediateContext->IASetIndexBuffer(mSheepIB, DXGI_FORMAT_R32_UINT, 0);

		XMMATRIX world = XMLoadFloat4x4(&mSheepWorld);
		XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
		XMMATRIX worldViewProj = world * view * proj;

		Effects::BasicFX->SetWorld(world);
		Effects::BasicFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::BasicFX->SetWorldViewProj(worldViewProj);
		Effects::BasicFX->SetMaterial(mSphereMat);

		//md3dImmediateContext->RSSetState(RenderStates::NoCullRS);

		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mSheepIndexCount, 0, 0);

		//md3dImmediateContext->RSSetState(0);

		/*
		if(mSubSceneNumber == 0) {

			md3dImmediateContext->IASetVertexBuffers(0, 1, &mText1VB, &stride, &offset);
			md3dImmediateContext->IASetIndexBuffer(mText1IB, DXGI_FORMAT_R32_UINT, 0);

			Effects::BasicFX->SetSpotLights(mSpaceSpotLight);

			world = XMLoadFloat4x4(&mText1World);
			worldInvTranspose = MathHelper::InverseTranspose(world);
			worldViewProj = world * view * proj;

			Effects::BasicFX->SetWorld(world);
			Effects::BasicFX->SetWorldInvTranspose(worldInvTranspose);
			Effects::BasicFX->SetWorldViewProj(worldViewProj);
			Effects::BasicFX->SetMaterial(mTextMat);

			//md3dImmediateContext->RSSetState(RenderStates::NoCullRS);

			activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
			md3dImmediateContext->DrawIndexed(mText1IndexCount, 0, 0);

			//md3dImmediateContext->RSSetState(0);
		}*/
    }
}

void BoxApp::DrawWrapper2_2() {

	md3dImmediateContext->IASetInputLayout(InputLayouts::PosNormal);
    md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	UINT stride = sizeof(Vertex::PosNormal);
    UINT offset = 0;

	XMMATRIX view     = mCam.View();
	XMMATRIX proj     = mCam.Proj();
	XMMATRIX viewProj = mCam.ViewProj();
	XMMATRIX identity = XMMatrixIdentity();
 
	// Set per frame constants.
	Effects::BasicFX->SetDirLights(mDirLights);
	Effects::BasicFX->SetSpotLights(mSpaceSpotLight);
	Effects::BasicFX->SetEyePosW(mCam.GetPosition());
 
	// Figure out which technique to use.
	ID3DX11EffectTechnique* activeTech = Effects::BasicFX->Light1Tech;
    D3DX11_TECHNIQUE_DESC techDesc;
    activeTech->GetDesc(&techDesc);
    for(UINT p = 0; p < techDesc.Passes; ++p) {
		md3dImmediateContext->IASetVertexBuffers(0, 1, &mText1VB, &stride, &offset);
		md3dImmediateContext->IASetIndexBuffer(mText1IB, DXGI_FORMAT_R32_UINT, 0);

		XMMATRIX world = XMLoadFloat4x4(&mText1World);
		XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
		XMMATRIX worldViewProj = world * view * proj;

		Effects::BasicFX->SetWorld(world);
		Effects::BasicFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::BasicFX->SetWorldViewProj(worldViewProj);
		Effects::BasicFX->SetMaterial(mTextMat);

		//md3dImmediateContext->RSSetState(RenderStates::NoCullRS);

		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mText1IndexCount, 0, 0);

		//md3dImmediateContext->RSSetState(0);
    }
}

void BoxApp::DrawWrapper2_3() {

	md3dImmediateContext->IASetInputLayout(InputLayouts::PosNormal);
    md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	UINT stride = sizeof(Vertex::PosNormal);
    UINT offset = 0;

	XMMATRIX view     = mCam.View();
	XMMATRIX proj     = mCam.Proj();
	XMMATRIX viewProj = mCam.ViewProj();
	XMMATRIX identity = XMMatrixIdentity();
 
	// Set per frame constants.
	Effects::BasicFX->SetDirLights(mDirLights);
	Effects::BasicFX->SetSpotLights(mSpaceSpotLight);
	Effects::BasicFX->SetEyePosW(mCam.GetPosition());
 
	// Figure out which technique to use.
	ID3DX11EffectTechnique* activeTech = Effects::BasicFX->Light1Tech;
    D3DX11_TECHNIQUE_DESC techDesc;
    activeTech->GetDesc(&techDesc);
    for(UINT p = 0; p < techDesc.Passes; ++p) {
		md3dImmediateContext->IASetVertexBuffers(0, 1, &mText2VB, &stride, &offset);
		md3dImmediateContext->IASetIndexBuffer(mText2IB, DXGI_FORMAT_R32_UINT, 0);

		XMMATRIX world = XMLoadFloat4x4(&mText2World);
		XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
		XMMATRIX worldViewProj = world * view * proj;

		Effects::BasicFX->SetWorld(world);
		Effects::BasicFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::BasicFX->SetWorldViewProj(worldViewProj);
		Effects::BasicFX->SetMaterial(mTextMat);

		//md3dImmediateContext->RSSetState(RenderStates::NoCullRS);

		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mText2IndexCount, 0, 0);

		//md3dImmediateContext->RSSetState(0);
    }
}

void BoxApp::DrawWrapper2_4() {

	md3dImmediateContext->IASetInputLayout(InputLayouts::PosNormal);
    md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	UINT stride = sizeof(Vertex::PosNormal);
    UINT offset = 0;

	XMMATRIX view     = mCam2.View();
	XMMATRIX proj     = mCam2.Proj();
	XMMATRIX viewProj = mCam2.ViewProj();
	XMMATRIX identity = XMMatrixIdentity();
 
	// Set per frame constants.
	Effects::BasicFX->SetDirLights(mDirLights);
	Effects::BasicFX->SetSpotLights(mSpaceSpotLight);
	Effects::BasicFX->SetEyePosW(mCam2.GetPosition());
 
	// Figure out which technique to use.
	ID3DX11EffectTechnique* activeTech = Effects::BasicFX->Light1Tech;
    D3DX11_TECHNIQUE_DESC techDesc;
    activeTech->GetDesc(&techDesc);
    for(UINT p = 0; p < techDesc.Passes; ++p) {
		md3dImmediateContext->IASetVertexBuffers(0, 1, &mText3VB, &stride, &offset);
		md3dImmediateContext->IASetIndexBuffer(mText3IB, DXGI_FORMAT_R32_UINT, 0);

		XMMATRIX world = XMLoadFloat4x4(&mText3World);
		XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
		XMMATRIX worldViewProj = world * view * proj;

		Effects::BasicFX->SetWorld(world);
		Effects::BasicFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::BasicFX->SetWorldViewProj(worldViewProj);
		Effects::BasicFX->SetMaterial(mTextMat);

		//md3dImmediateContext->RSSetState(RenderStates::NoCullRS);
		//md3dImmediateContext->OMSetBlendState(RenderStates::NormalDoubleBS, blendFactor, 0xffffffff);

		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mText3IndexCount, 0, 0);

		//md3dImmediateContext->RSSetState(0);
    }
}

void BoxApp::DrawWrapper3() {

	float blendFactor[] = {0.0f, 0.0f, 0.0f, 0.0f};

	md3dImmediateContext->IASetInputLayout(InputLayouts::PosNormalTexTan);
    md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	UINT stride = sizeof(Vertex::PosNormalTexTan);
    UINT offset = 0;

	XMMATRIX view     = mCam2.View();
	XMMATRIX proj     = mCam2.Proj();
	XMMATRIX viewProj = mCam2.ViewProj();
	XMMATRIX identity = XMMatrixIdentity();
 
	// Set per frame constants.
	Effects::NormalMapFX->SetDirLights(mCapsuleDirLights);
	Effects::NormalMapFX->SetSpotLights(mCapsuleSpotLight);
	Effects::NormalMapFX->SetFogColor(Colors::DarkDirtyGreen);
	Effects::NormalMapFX->SetFogStart(0.0f);
	Effects::NormalMapFX->SetFogRange(25.0f);
	Effects::NormalMapFX->SetEyePosW(mCam2.GetPosition());
 
	// Figure out which technique to use.
	ID3DX11EffectTechnique* activeTech = Effects::NormalMapFX->Light1TexFogTech;
    D3DX11_TECHNIQUE_DESC techDesc;
    activeTech->GetDesc(&techDesc);
    for(UINT p = 0; p < techDesc.Passes; ++p) {
		md3dImmediateContext->IASetVertexBuffers(0, 1, &mCapsuleVB, &stride, &offset);
		md3dImmediateContext->IASetIndexBuffer(mCapsuleIB, DXGI_FORMAT_R32_UINT, 0);

		XMMATRIX world = XMLoadFloat4x4(&mCapsuleWorld);
		XMMATRIX boxOffset = identity;
		world = world * boxOffset;

		XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
		XMMATRIX worldViewProj = world * view * proj;

		Effects::NormalMapFX->SetWorld(world);
		Effects::NormalMapFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::NormalMapFX->SetWorldViewProj(worldViewProj);
		Effects::NormalMapFX->SetTexTransform(XMMatrixScaling(1.0f, 1.0f, 1.0f));
		Effects::NormalMapFX->SetMaterial(mCapsuleMat);
		Effects::NormalMapFX->SetDiffuseMap(mCapsuleDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mCapsuleNormalMapSRV);
		

		//md3dImmediateContext->RSSetState(RenderStates::NoCullRS);

		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mShieldingCapsuleIndexCount, mShieldingCapsuleIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mCircleSupportIndexCount, mCircleSupportIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mNumPadIndexCount, mNumPadIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mVerticalSupportIndexCount, mVerticalSupportIndexLocation, 0);
		//md3dImmediateContext->DrawIndexed(mCapsuleIndexCount, 0, 0);

		Effects::NormalMapFX->SetDiffuseMap(mHumanShieldDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mHumanShieldNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mHumanShieldIndexCount, mHumanShieldIndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mHosepipeDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mHosepipeNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mHosepipe0IndexCount, mHosepipe0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe1IndexCount, mHosepipe1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe2IndexCount, mHosepipe2IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe3IndexCount, mHosepipe3IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe4IndexCount, mHosepipe4IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe5IndexCount, mHosepipe5IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe6IndexCount, mHosepipe6IndexLocation, 0);

		//md3dImmediateContext->RSSetState(0);

		world = XMLoadFloat4x4(&mCapsuleWorld);
		boxOffset = XMMatrixTranslation(0.0f, 0.0f, -4.0f);
		world = world * boxOffset;

		worldInvTranspose = MathHelper::InverseTranspose(world);
		worldViewProj = world * view * proj;

		Effects::NormalMapFX->SetWorld(world);
		Effects::NormalMapFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::NormalMapFX->SetWorldViewProj(worldViewProj);

		Effects::NormalMapFX->SetDiffuseMap(mCapsuleDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mCapsuleNormalMapSRV);

		//md3dImmediateContext->RSSetState(RenderStates::NoCullRS);

		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mShieldingCapsuleIndexCount, mShieldingCapsuleIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mCircleSupportIndexCount, mCircleSupportIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mNumPadIndexCount, mNumPadIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mVerticalSupportIndexCount, mVerticalSupportIndexLocation, 0);
		//md3dImmediateContext->DrawIndexed(mCapsuleIndexCount, 0, 0);

		Effects::NormalMapFX->SetDiffuseMap(mHumanShieldDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mHumanShieldNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mHumanShieldIndexCount, mHumanShieldIndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mHosepipeDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mHosepipeNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mHosepipe0IndexCount, mHosepipe0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe1IndexCount, mHosepipe1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe2IndexCount, mHosepipe2IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe3IndexCount, mHosepipe3IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe4IndexCount, mHosepipe4IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe5IndexCount, mHosepipe5IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe6IndexCount, mHosepipe6IndexLocation, 0);

		//md3dImmediateContext->RSSetState(0);

		world = XMLoadFloat4x4(&mCapsuleWorld);
		boxOffset = XMMatrixTranslation(0.0f, 0.0f, -8.0f);
		world = world * boxOffset;

		worldInvTranspose = MathHelper::InverseTranspose(world);
		worldViewProj = world * view * proj;

		Effects::NormalMapFX->SetWorld(world);
		Effects::NormalMapFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::NormalMapFX->SetWorldViewProj(worldViewProj);

		Effects::NormalMapFX->SetDiffuseMap(mCapsuleDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mCapsuleNormalMapSRV);

		//md3dImmediateContext->RSSetState(RenderStates::NoCullRS);

		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mShieldingCapsuleIndexCount, mShieldingCapsuleIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mCircleSupportIndexCount, mCircleSupportIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mNumPadIndexCount, mNumPadIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mVerticalSupportIndexCount, mVerticalSupportIndexLocation, 0);
		//md3dImmediateContext->DrawIndexed(mCapsuleIndexCount, 0, 0);

		Effects::NormalMapFX->SetDiffuseMap(mHumanShieldDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mHumanShieldNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mHumanShieldIndexCount, mHumanShieldIndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mHosepipeDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mHosepipeNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mHosepipe0IndexCount, mHosepipe0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe1IndexCount, mHosepipe1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe2IndexCount, mHosepipe2IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe3IndexCount, mHosepipe3IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe4IndexCount, mHosepipe4IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe5IndexCount, mHosepipe5IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe6IndexCount, mHosepipe6IndexLocation, 0);

		//md3dImmediateContext->RSSetState(0);

		world = XMLoadFloat4x4(&mCapsuleWorld);
		boxOffset = XMMatrixTranslation(0.0f, 0.0f, 43.0f);
		world = world * boxOffset;

		worldInvTranspose = MathHelper::InverseTranspose(world);
		worldViewProj = world * view * proj;

		Effects::NormalMapFX->SetWorld(world);
		Effects::NormalMapFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::NormalMapFX->SetWorldViewProj(worldViewProj);

		Effects::NormalMapFX->SetDiffuseMap(mCapsuleDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mCapsuleNormalMapSRV);

		//md3dImmediateContext->RSSetState(RenderStates::NoCullRS);

		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mShieldingCapsuleIndexCount, mShieldingCapsuleIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mCircleSupportIndexCount, mCircleSupportIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mNumPadIndexCount, mNumPadIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mVerticalSupportIndexCount, mVerticalSupportIndexLocation, 0);
		//md3dImmediateContext->DrawIndexed(mCapsuleIndexCount, 0, 0);

		Effects::NormalMapFX->SetDiffuseMap(mHumanShieldDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mHumanShieldNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mHumanShieldIndexCount, mHumanShieldIndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mHosepipeDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mHosepipeNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mHosepipe0IndexCount, mHosepipe0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe1IndexCount, mHosepipe1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe2IndexCount, mHosepipe2IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe3IndexCount, mHosepipe3IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe4IndexCount, mHosepipe4IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe5IndexCount, mHosepipe5IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe6IndexCount, mHosepipe6IndexLocation, 0);

		//md3dImmediateContext->RSSetState(0);

		world = XMLoadFloat4x4(&mCapsuleWorld);
		boxOffset = XMMatrixTranslation(0.0f, 0.0f, 39.0f);
		world = world * boxOffset;

		worldInvTranspose = MathHelper::InverseTranspose(world);
		worldViewProj = world * view * proj;

		Effects::NormalMapFX->SetWorld(world);
		Effects::NormalMapFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::NormalMapFX->SetWorldViewProj(worldViewProj);

		Effects::NormalMapFX->SetDiffuseMap(mCapsuleDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mCapsuleNormalMapSRV);

		//md3dImmediateContext->RSSetState(RenderStates::NoCullRS);

		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mShieldingCapsuleIndexCount, mShieldingCapsuleIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mCircleSupportIndexCount, mCircleSupportIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mNumPadIndexCount, mNumPadIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mVerticalSupportIndexCount, mVerticalSupportIndexLocation, 0);
		//md3dImmediateContext->DrawIndexed(mCapsuleIndexCount, 0, 0);

		Effects::NormalMapFX->SetDiffuseMap(mHumanShieldDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mHumanShieldNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mHumanShieldIndexCount, mHumanShieldIndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mHosepipeDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mHosepipeNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mHosepipe0IndexCount, mHosepipe0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe1IndexCount, mHosepipe1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe2IndexCount, mHosepipe2IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe3IndexCount, mHosepipe3IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe4IndexCount, mHosepipe4IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe5IndexCount, mHosepipe5IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe6IndexCount, mHosepipe6IndexLocation, 0);

		//md3dImmediateContext->RSSetState(0);

		world = XMLoadFloat4x4(&mCapsuleWorld);
		boxOffset = XMMatrixTranslation(0.0f, 0.0f, 35.0f);
		world = world * boxOffset;

		worldInvTranspose = MathHelper::InverseTranspose(world);
		worldViewProj = world * view * proj;

		Effects::NormalMapFX->SetWorld(world);
		Effects::NormalMapFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::NormalMapFX->SetWorldViewProj(worldViewProj);

		Effects::NormalMapFX->SetDiffuseMap(mCapsuleDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mCapsuleNormalMapSRV);

		//md3dImmediateContext->RSSetState(RenderStates::NoCullRS);

		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mShieldingCapsuleIndexCount, mShieldingCapsuleIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mCircleSupportIndexCount, mCircleSupportIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mNumPadIndexCount, mNumPadIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mVerticalSupportIndexCount, mVerticalSupportIndexLocation, 0);
		//md3dImmediateContext->DrawIndexed(mCapsuleIndexCount, 0, 0);

		Effects::NormalMapFX->SetDiffuseMap(mHumanShieldDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mHumanShieldNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mHumanShieldIndexCount, mHumanShieldIndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mHosepipeDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mHosepipeNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mHosepipe0IndexCount, mHosepipe0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe1IndexCount, mHosepipe1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe2IndexCount, mHosepipe2IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe3IndexCount, mHosepipe3IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe4IndexCount, mHosepipe4IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe5IndexCount, mHosepipe5IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mHosepipe6IndexCount, mHosepipe6IndexLocation, 0);

		//md3dImmediateContext->RSSetState(0);
    }
}

void BoxApp::DrawWrapper4() {

	float blendFactor[] = {0.0f, 0.0f, 0.0f, 0.0f};

	md3dImmediateContext->IASetInputLayout(InputLayouts::PosNormalTexTan);
    md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	UINT stride = sizeof(Vertex::PosNormalTexTan);
    UINT offset = 0;

	XMMATRIX view     = mCam2.View();
	XMMATRIX proj     = mCam2.Proj();
	XMMATRIX viewProj = mCam2.ViewProj();
	XMMATRIX identity = XMMatrixIdentity();
 
	// Set per frame constants.
	Effects::NormalMapFX->SetDirLights(mCapsuleDirLights);
	Effects::NormalMapFX->SetSpotLights(mCapsuleSpotLight);
	Effects::NormalMapFX->SetFogColor(Colors::DarkDirtyGreen);
	Effects::NormalMapFX->SetFogStart(0.0f);
	Effects::NormalMapFX->SetFogRange(25.0f);
	Effects::NormalMapFX->SetEyePosW(mCam2.GetPosition());
 
	// Figure out which technique to use.
	ID3DX11EffectTechnique* activeTech = Effects::NormalMapFX->Light1TexFogTech;
    D3DX11_TECHNIQUE_DESC techDesc;
    activeTech->GetDesc(&techDesc);
    for(UINT p = 0; p < techDesc.Passes; ++p) {
		md3dImmediateContext->IASetVertexBuffers(0, 1, &mRoomVB, &stride, &offset);
		md3dImmediateContext->IASetIndexBuffer(mRoomIB, DXGI_FORMAT_R32_UINT, 0);

		XMMATRIX world = XMLoadFloat4x4(&mRoomWorld);
		XMMATRIX boxOffset = identity;
		world = world * boxOffset;

		XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
		XMMATRIX worldViewProj = world * view * proj;

		Effects::NormalMapFX->SetWorld(world);
		Effects::NormalMapFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::NormalMapFX->SetWorldViewProj(worldViewProj);
		Effects::NormalMapFX->SetTexTransform(XMMatrixScaling(1.0f, 1.0f, 1.0f));
		Effects::NormalMapFX->SetMaterial(mRoomMat);

		//md3dImmediateContext->RSSetState(RenderStates::NoCullRS);

		Effects::NormalMapFX->SetDiffuseMap(mMetalGridDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mMetalGridNormalMapSRV);

		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mFloorIndexCount, mFloorIndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mScifiFloorDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mScifiFloorNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mBasketIndexCount, mBasketIndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mStorageContainerDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mStorageContainerNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mSideWall0IndexCount, mSideWall0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mSideWall1IndexCount, mSideWall1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mSlopeIndexCount, mSlopeIndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mPlasticPaddedDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mPlasticPaddedNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mFrontWallIndexCount, mFrontWallIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mBackWallIndexCount, mBackWallIndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mScuffedPlasticDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mScuffedPlasticNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mRedPipe0IndexCount, mRedPipe0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRedPipe1IndexCount, mRedPipe1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRedPipe2IndexCount, mRedPipe2IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRedPipe3IndexCount, mRedPipe3IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRedPipe4IndexCount, mRedPipe4IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRedPipe5IndexCount, mRedPipe5IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRedPipe6IndexCount, mRedPipe6IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRedPipe7IndexCount, mRedPipe7IndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mHosepipeDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mHosepipeNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mRoomHosePipe0IndexCount, mRoomHosePipe0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRoomHosePipe1IndexCount, mRoomHosePipe1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRoomHosePipe2IndexCount, mRoomHosePipe2IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRoomHosePipe3IndexCount, mRoomHosePipe3IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRoomHosePipe4IndexCount, mRoomHosePipe4IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRoomHosePipe5IndexCount, mRoomHosePipe5IndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mChippedPaintMetalDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mChippedPaintMetalNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mCube0IndexCount, mCube0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mCube1IndexCount, mCube1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mCube2IndexCount, mCube2IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mCube3IndexCount, mCube3IndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mRustedironStreaksDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mRustedironStreaksNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mSupport0IndexCount, mSupport0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mSupport1IndexCount, mSupport1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mSupport3IndexCount, mSupport3IndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mCircleMetalGridDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mCircleMetalGridNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mRoofIndexCount, mRoofIndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mIronRustedDiffuseMapSRV0);
		Effects::NormalMapFX->SetNormalMap(mIronRustedNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mDrawing0IndexCount, mDrawing0IndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mIronRustedDiffuseMapSRV1);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mDrawing1IndexCount, mDrawing1IndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mIronRustedDiffuseMapSRV2);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mDrawing2IndexCount, mDrawing2IndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mIronRustedDiffuseMapSRV3);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mDrawing3IndexCount, mDrawing3IndexLocation, 0);

		//md3dImmediateContext->RSSetState(0);





		world = XMLoadFloat4x4(&mRoomWorld);
		boxOffset = XMMatrixTranslation(0.0f, 0.0f, 43.0f);
		world = world * boxOffset;

		worldInvTranspose = MathHelper::InverseTranspose(world);
		worldViewProj = world * view * proj;

		Effects::NormalMapFX->SetWorld(world);
		Effects::NormalMapFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::NormalMapFX->SetWorldViewProj(worldViewProj);

		//md3dImmediateContext->RSSetState(RenderStates::NoCullRS);

		Effects::NormalMapFX->SetDiffuseMap(mMetalGridDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mMetalGridNormalMapSRV);

		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mFloorIndexCount, mFloorIndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mScifiFloorDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mScifiFloorNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mBasketIndexCount, mBasketIndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mStorageContainerDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mStorageContainerNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mSideWall0IndexCount, mSideWall0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mSideWall1IndexCount, mSideWall1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mSlopeIndexCount, mSlopeIndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mPlasticPaddedDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mPlasticPaddedNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mFrontWallIndexCount, mFrontWallIndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mBackWallIndexCount, mBackWallIndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mScuffedPlasticDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mScuffedPlasticNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mRedPipe0IndexCount, mRedPipe0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRedPipe1IndexCount, mRedPipe1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRedPipe2IndexCount, mRedPipe2IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRedPipe3IndexCount, mRedPipe3IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRedPipe4IndexCount, mRedPipe4IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRedPipe5IndexCount, mRedPipe5IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRedPipe6IndexCount, mRedPipe6IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRedPipe7IndexCount, mRedPipe7IndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mHosepipeDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mHosepipeNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mRoomHosePipe0IndexCount, mRoomHosePipe0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRoomHosePipe1IndexCount, mRoomHosePipe1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRoomHosePipe2IndexCount, mRoomHosePipe2IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRoomHosePipe3IndexCount, mRoomHosePipe3IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRoomHosePipe4IndexCount, mRoomHosePipe4IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mRoomHosePipe5IndexCount, mRoomHosePipe5IndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mChippedPaintMetalDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mChippedPaintMetalNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mCube0IndexCount, mCube0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mCube1IndexCount, mCube1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mCube2IndexCount, mCube2IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mCube3IndexCount, mCube3IndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mRustedironStreaksDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mRustedironStreaksNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mSupport0IndexCount, mSupport0IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mSupport1IndexCount, mSupport1IndexLocation, 0);
		md3dImmediateContext->DrawIndexed(mSupport3IndexCount, mSupport3IndexLocation, 0);

		Effects::NormalMapFX->SetDiffuseMap(mCircleMetalGridDiffuseMapSRV);
		Effects::NormalMapFX->SetNormalMap(mCircleMetalGridNormalMapSRV);
		activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mRoofIndexCount, mRoofIndexLocation, 0);

		//md3dImmediateContext->RSSetState(0);
    }
}

void BoxApp::DrawScreenQuad() {
	md3dImmediateContext->IASetInputLayout(InputLayouts::Post);
    md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
 
	UINT stride = sizeof(Vertex::Post);
    UINT offset = 0;
 
	XMMATRIX identity = XMMatrixIdentity();
 
	ID3DX11EffectTechnique* texOnlyTech = Effects::PostFX->Tech1;
	D3DX11_TECHNIQUE_DESC techDesc;

	texOnlyTech->GetDesc(&techDesc);
	for(UINT p = 0; p < techDesc.Passes; ++p) {
		md3dImmediateContext->IASetVertexBuffers(0, 1, &mScreenQuadVB, &stride, &offset);
		md3dImmediateContext->IASetIndexBuffer(mScreenQuadIB, DXGI_FORMAT_R32_UINT, 0);

		Effects::PostFX->SetWorld(identity);
		Effects::PostFX->SetWorldInvTranspose(identity);
		Effects::PostFX->SetWorldViewProj(identity);
		Effects::PostFX->SetTexTransform(identity);
		//Effects::PostFX->SetDiffuseMap(mBlur.GetBlurredOutput());
		//Effects::PostFX->SetDiffuseMap2(mBlur.GetBlurredOutput());
		Effects::PostFX->SetDiffuseMap(mOffscreenSRV);
		Effects::PostFX->SetDiffuseMap2(mOffscreenSRV2);

		texOnlyTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(6, 0, 0);
    }

	ID3D11ShaderResourceView* nullSRV[1] = { 0 };
	Effects::PostFX->SetDiffuseMap(nullSRV[0]);
	Effects::PostFX->SetDiffuseMap2(nullSRV[0]);
	texOnlyTech->GetPassByIndex(0)->Apply(0, md3dImmediateContext);
}

void BoxApp::BuildSheepGeometryBuffers() {

	ObjLoader loader = ObjLoader(std::string("sheep.obj"));

	std::vector<Vertex::PosNormal> vertices;
	std::vector<int> indices;
	mSheepIndexCount = loader.Groups[0].Faces.size() * 3;

	XMFLOAT3 vMinf3(+MathHelper::Infinity, +MathHelper::Infinity, +MathHelper::Infinity);
	XMFLOAT3 vMaxf3(-MathHelper::Infinity, -MathHelper::Infinity, -MathHelper::Infinity);

	XMVECTOR vMin = XMLoadFloat3(&vMinf3);
	XMVECTOR vMax = XMLoadFloat3(&vMaxf3);

	int cc = 0;
	for(UINT i = 0; i < loader.Faces.size(); ++i) {
		ObjLoader::Face f = loader.Faces[i];
		for(UINT j = 0; j < f.vertices.size(); ++j) {
			ObjLoader::FaceVertex fv = f.vertices[j];
			Vertex::PosNormal v;
			v.Pos = loader.Vertices[fv.VertexIndex - 1].Pos;
			v.Normal = loader.Normals[fv.NormalIndex - 1];
			vertices.push_back(v);
			indices.push_back(cc++);

			XMVECTOR P = XMLoadFloat3(&v.Pos);

			vMin = XMVectorMin(vMin, P);
			vMax = XMVectorMax(vMax, P);
		}
	}

	XMStoreFloat3(&mSheepBox.Center, 0.5f * (vMin + vMax));
	XMStoreFloat3(&mSheepBox.Extents, 0.5f * (vMax - vMin));

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex::PosNormal) * vertices.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices.data();

	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mSheepVB));

	// Pack the indices of all the meshes into one index buffer.
	D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * mSheepIndexCount;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &indices[0];
    HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mSheepIB));
}

void BoxApp::BuildTextGeometryBuffers() {

	ObjLoader loader1 = ObjLoader(std::string("Text1.obj"));

	std::vector<Vertex::PosNormal> vertices1;
	std::vector<int> indices1;
	mText1IndexCount = loader1.Groups[0].Faces.size() * 3;

	int cc = 0;
	for(UINT i = 0; i < loader1.Faces.size(); ++i) {
		ObjLoader::Face f = loader1.Faces[i];
		for(UINT j = 0; j < f.vertices.size(); ++j) {
			ObjLoader::FaceVertex fv = f.vertices[j];
			Vertex::PosNormal v;
			v.Pos = loader1.Vertices[fv.VertexIndex - 1].Pos;
			v.Normal = loader1.Normals[fv.NormalIndex - 1];
			v.Normal.x *= -1.0f;
			v.Normal.y *= -1.0f;
			v.Normal.z *= -1.0f;
			vertices1.push_back(v);
			indices1.push_back(cc++);
		}
	}

	D3D11_BUFFER_DESC vbd1;
	vbd1.Usage = D3D11_USAGE_IMMUTABLE;
	vbd1.ByteWidth = sizeof(Vertex::PosNormal) * vertices1.size();
	vbd1.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd1.CPUAccessFlags = 0;
	vbd1.MiscFlags = 0;
	vbd1.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA vinitData1;
	vinitData1.pSysMem = vertices1.data();

	HR(md3dDevice->CreateBuffer(&vbd1, &vinitData1, &mText1VB));

	// Pack the indices of all the meshes into one index buffer.
	D3D11_BUFFER_DESC ibd1;
    ibd1.Usage = D3D11_USAGE_IMMUTABLE;
	ibd1.ByteWidth = sizeof(UINT) * mText1IndexCount;
    ibd1.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd1.CPUAccessFlags = 0;
    ibd1.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA iinitData1;
	iinitData1.pSysMem = &indices1[0];
    HR(md3dDevice->CreateBuffer(&ibd1, &iinitData1, &mText1IB));




	ObjLoader loader2 = ObjLoader(std::string("Text2.obj"));

	std::vector<Vertex::PosNormal> vertices2;
	std::vector<int> indices2;
	mText2IndexCount = loader2.Groups[0].Faces.size() * 3;

	cc = 0;
	for(UINT i = 0; i < loader2.Faces.size(); ++i) {
		ObjLoader::Face f = loader2.Faces[i];
		for(UINT j = 0; j < f.vertices.size(); ++j) {
			ObjLoader::FaceVertex fv = f.vertices[j];
			Vertex::PosNormal v;
			v.Pos = loader2.Vertices[fv.VertexIndex - 1].Pos;
			v.Normal = loader2.Normals[fv.NormalIndex - 1];
			v.Normal.x *= -1.0f;
			v.Normal.y *= -1.0f;
			v.Normal.z *= -1.0f;
			vertices2.push_back(v);
			indices2.push_back(cc++);
		}
	}

	D3D11_BUFFER_DESC vbd2;
	vbd2.Usage = D3D11_USAGE_IMMUTABLE;
	vbd2.ByteWidth = sizeof(Vertex::PosNormal) * vertices2.size();
	vbd2.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd2.CPUAccessFlags = 0;
	vbd2.MiscFlags = 0;
	vbd2.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA vinitData2;
	vinitData2.pSysMem = vertices2.data();

	HR(md3dDevice->CreateBuffer(&vbd2, &vinitData2, &mText2VB));

	// Pack the indices of all the meshes into one index buffer.
	D3D11_BUFFER_DESC ibd2;
    ibd2.Usage = D3D11_USAGE_IMMUTABLE;
	ibd2.ByteWidth = sizeof(UINT) * mText2IndexCount;
    ibd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd2.CPUAccessFlags = 0;
    ibd2.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA iinitData2;
	iinitData2.pSysMem = &indices2[0];
    HR(md3dDevice->CreateBuffer(&ibd2, &iinitData2, &mText2IB));






	ObjLoader loader3 = ObjLoader(std::string("Text3.obj"));

	std::vector<Vertex::PosNormal> vertices3;
	std::vector<int> indices3;
	mText3IndexCount = loader3.Indices.size();

	cc = 0;
	for(UINT i = 0; i < loader3.Faces.size(); ++i) {
		ObjLoader::Face f = loader3.Faces[i];
		for(UINT j = 0; j < f.vertices.size(); ++j) {
			ObjLoader::FaceVertex fv = f.vertices[j];
			Vertex::PosNormal v;
			v.Pos = loader3.Vertices[fv.VertexIndex - 1].Pos;
			v.Normal = loader3.Normals[fv.NormalIndex - 1];
			v.Normal.x *= -1.0f;
			v.Normal.y *= -1.0f;
			v.Normal.z *= -1.0f;
			vertices3.push_back(v);
			indices3.push_back(cc++);
		}
	}

	D3D11_BUFFER_DESC vbd3;
	vbd3.Usage = D3D11_USAGE_IMMUTABLE;
	vbd3.ByteWidth = sizeof(Vertex::PosNormal) * vertices3.size();
	vbd3.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd3.CPUAccessFlags = 0;
	vbd3.MiscFlags = 0;
	vbd3.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA vinitData3;
	vinitData3.pSysMem = vertices3.data();

	HR(md3dDevice->CreateBuffer(&vbd3, &vinitData3, &mText3VB));

	// Pack the indices of all the meshes into one index buffer.
	D3D11_BUFFER_DESC ibd3;
    ibd3.Usage = D3D11_USAGE_IMMUTABLE;
	ibd3.ByteWidth = sizeof(UINT) * mText3IndexCount;
    ibd3.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd3.CPUAccessFlags = 0;
    ibd3.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA iinitData3;
	iinitData3.pSysMem = &indices3[0];
    HR(md3dDevice->CreateBuffer(&ibd3, &iinitData3, &mText3IB));
}

void BoxApp::BuildCrateGeometryBuffers() {
	GeometryGenerator::MeshData sphere;

	GeometryGenerator geoGen;
	geoGen.CreateGeosphere(0.3f, 1, sphere);

	// Extract the vertex elements we are interested in and pack the
	// vertices of all the meshes into one vertex buffer.
	std::vector<Vertex::Position> vertices(sphere.Vertices.size());
	mSphereIndexCount = sphere.Indices.size();

	XMFLOAT3 vMinf3(+MathHelper::Infinity, +MathHelper::Infinity, +MathHelper::Infinity);
	XMFLOAT3 vMaxf3(-MathHelper::Infinity, -MathHelper::Infinity, -MathHelper::Infinity);

	XMVECTOR vMin = XMLoadFloat3(&vMinf3);
	XMVECTOR vMax = XMLoadFloat3(&vMaxf3);

	for(UINT i = 0; i < sphere.Vertices.size(); ++i) {
		vertices[i].Pos    = sphere.Vertices[i].Position;

		XMVECTOR P = XMLoadFloat3(&vertices[i].Pos);

		vMin = XMVectorMin(vMin, P);
		vMax = XMVectorMax(vMax, P);
	}

	XMStoreFloat3(&mSphereBox.Center, 0.5f * (vMin + vMax));
	XMStoreFloat3(&mSphereBox.Extents, 0.5f * (vMax - vMin));

    D3D11_BUFFER_DESC vbd;
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = sizeof(Vertex::Position) * sphere.Vertices.size();
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = &vertices[0];
    HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mSphereVB));

	// Pack the indices of all the meshes into one index buffer.
	D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * sphere.Indices.size();
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;
    D3D11_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = &sphere.Indices[0];
    HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mSphereIB));






	GeometryGenerator::MeshData sphere2;

	geoGen.CreateGeosphere(1.0f, 16, sphere2);

	// Extract the vertex elements we are interested in and pack the
	// vertices of all the meshes into one vertex buffer.
	std::vector<Vertex::Position> vertices2(sphere2.Vertices.size());
	mSphereIndexCount2 = sphere2.Indices.size();

	for(UINT i = 0; i < sphere2.Vertices.size(); ++i) {
		vertices2[i].Pos    = sphere2.Vertices[i].Position;
	}

    D3D11_BUFFER_DESC vbd2;
    vbd2.Usage = D3D11_USAGE_IMMUTABLE;
    vbd2.ByteWidth = sizeof(Vertex::Position) * sphere2.Vertices.size();
    vbd2.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd2.CPUAccessFlags = 0;
    vbd2.MiscFlags = 0;
    D3D11_SUBRESOURCE_DATA vinitData2;
    vinitData2.pSysMem = &vertices2[0];
    HR(md3dDevice->CreateBuffer(&vbd2, &vinitData2, &mSphereVB2));

	// Pack the indices of all the meshes into one index buffer.
	D3D11_BUFFER_DESC ibd2;
    ibd2.Usage = D3D11_USAGE_IMMUTABLE;
	ibd2.ByteWidth = sizeof(UINT) * sphere2.Indices.size();
    ibd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd2.CPUAccessFlags = 0;
    ibd2.MiscFlags = 0;
    D3D11_SUBRESOURCE_DATA iinitData2;
    iinitData2.pSysMem = &sphere2.Indices[0];
    HR(md3dDevice->CreateBuffer(&ibd2, &iinitData2, &mSphereIB2));
}

void BoxApp::BuildCapsuleGeometryBuffers() {
	ObjLoader loader = ObjLoader(std::string("cryo8.obj"));

	std::vector<Vertex::PosNormalTexTan> vertices;
	std::vector<UINT> indices;
	mCapsuleIndexCount = loader.Indices.size();

	XMFLOAT3 vMinf3(+MathHelper::Infinity, +MathHelper::Infinity, +MathHelper::Infinity);
	XMFLOAT3 vMaxf3(-MathHelper::Infinity, -MathHelper::Infinity, -MathHelper::Infinity);

	XMVECTOR vMin = XMLoadFloat3(&vMinf3);
	XMVECTOR vMax = XMLoadFloat3(&vMaxf3);

	int cc = 0;
	for(UINT i = 0; i < loader.Groups.size(); ++i) {
		ObjLoader::Group g = loader.Groups[i];
		if(g.Name == "ShieldingCapsule_ShieldingCapsuleMesh") {
			mShieldingCapsuleIndexCount = g.Faces.size() * 3;
			mShieldingCapsuleIndexLocation = cc;
		}
		if(g.Name == "CircleSupport_CircleSupportMesh") {
			mCircleSupportIndexCount = g.Faces.size() * 3;
			mCircleSupportIndexLocation = cc;
		}
		if(g.Name == "NumPad_NumPadMesh") {
			mNumPadIndexCount = g.Faces.size() * 3;
			mNumPadIndexLocation = cc;
		}
		if(g.Name == "VerticalSupport") {
			mVerticalSupportIndexCount = g.Faces.size() * 3;
			mVerticalSupportIndexLocation = cc;
		}
		if(g.Name == "HumanShield_HumanShieldMesh") {
			mHumanShieldIndexCount = g.Faces.size() * 3;
			mHumanShieldIndexLocation = cc;
		}
		if(g.Name == "Hosepipe0_HosepipeMesh0") {
			mHosepipe0IndexCount = g.Faces.size() * 3;
			mHosepipe0IndexLocation = cc;
		}
		if(g.Name == "Hosepipe1_HosepipeMesh1") {
			mHosepipe1IndexCount = g.Faces.size() * 3;
			mHosepipe1IndexLocation = cc;
		}
		if(g.Name == "Hosepipe2_HosepipeMesh2") {
			mHosepipe2IndexCount = g.Faces.size() * 3;
			mHosepipe2IndexLocation = cc;
		}
		if(g.Name == "Hosepipe3_HosepipeMesh3") {
			mHosepipe3IndexCount = g.Faces.size() * 3;
			mHosepipe3IndexLocation = cc;
		}
		if(g.Name == "Hosepipe4_HosepipeMesh4") {
			mHosepipe4IndexCount = g.Faces.size() * 3;
			mHosepipe4IndexLocation = cc;
		}
		if(g.Name == "Hosepipe5_HosepipeMesh5") {
			mHosepipe5IndexCount = g.Faces.size() * 3;
			mHosepipe5IndexLocation = cc;
		}
		if(g.Name == "Hosepipe6_HosepipeMesh6") {
			mHosepipe6IndexCount = g.Faces.size() * 3;
			mHosepipe6IndexLocation = cc;
		}
		for(UINT k = 0; k < g.Faces.size(); ++k) {
			ObjLoader::Face f = g.Faces[k];
			for(UINT j = 0; j < f.vertices.size(); ++j) {
				ObjLoader::FaceVertex fv = f.vertices[j];
				Vertex::PosNormalTexTan v;
				v.Pos = loader.Vertices[fv.VertexIndex - 1].Pos;
				v.Normal = loader.Normals[fv.NormalIndex - 1];
				v.Tex = loader.Textures[fv.TextureIndex - 1];
				vertices.push_back(v);
				indices.push_back(cc++);

				XMVECTOR P = XMLoadFloat3(&v.Pos);

				vMin = XMVectorMin(vMin, P);
				vMax = XMVectorMax(vMax, P);
			}
		}
	}

	CalculateTangentsAndNormals(vertices, indices);

	XMStoreFloat3(&mCapsuleBox.Center, 0.5f * (vMin + vMax));
	XMStoreFloat3(&mCapsuleBox.Extents, 0.5f * (vMax - vMin));

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex::PosNormalTexTan) * vertices.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices.data();

	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mCapsuleVB));

	// Pack the indices of all the meshes into one index buffer.
	D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * mCapsuleIndexCount;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &indices[0];
    HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mCapsuleIB));
}

void BoxApp::BuildRoomGeometryBuffers() {
	ObjLoader loader = ObjLoader(std::string("cryoRoom2.obj"));

	std::vector<Vertex::PosNormalTexTan> vertices;
	std::vector<UINT> indices;
	mRoomIndexCount = loader.Indices.size();

	XMFLOAT3 vMinf3(+MathHelper::Infinity, +MathHelper::Infinity, +MathHelper::Infinity);
	XMFLOAT3 vMaxf3(-MathHelper::Infinity, -MathHelper::Infinity, -MathHelper::Infinity);

	XMVECTOR vMin = XMLoadFloat3(&vMinf3);
	XMVECTOR vMax = XMLoadFloat3(&vMaxf3);

	int cc = 0;
	for(UINT i = 0; i < loader.Groups.size(); ++i) {
		ObjLoader::Group g = loader.Groups[i];
		if(g.Name == "Floor_FloorMesh") {
			mFloorIndexCount = g.Faces.size() * 3;
			mFloorIndexLocation = cc;
		}
		if(g.Name == "Basket_BasketMesh") {
			mBasketIndexCount = g.Faces.size() * 3;
			mBasketIndexLocation = cc;
		}
		if(g.Name == "SideWall1_SideWall1Mesh") {
			mSideWall1IndexCount = g.Faces.size() * 3;
			mSideWall1IndexLocation = cc;
		}
		if(g.Name == "RedPipe1_RedPipe1Mesh") {
			mRedPipe1IndexCount = g.Faces.size() * 3;
			mRedPipe1IndexLocation = cc;
		}
		if(g.Name == "RedPipe0_RedPipe0Mesh") {
			mRedPipe0IndexCount = g.Faces.size() * 3;
			mRedPipe0IndexLocation = cc;
		}
		if(g.Name == "HosePipe4_HosePipe4Mesh") {
			mRoomHosePipe4IndexCount = g.Faces.size() * 3;
			mRoomHosePipe4IndexLocation = cc;
		}
		if(g.Name == "HosePipe5_Hosepipe5Mesh") {
			mRoomHosePipe5IndexCount = g.Faces.size() * 3;
			mRoomHosePipe5IndexLocation = cc;
		}
		if(g.Name == "Hosepipe3_Hosepipe3Mesh") {
			mRoomHosePipe3IndexCount = g.Faces.size() * 3;
			mRoomHosePipe3IndexLocation = cc;
		}
		if(g.Name == "Hosepipe0_Hosepipe0Mesh") {
			mRoomHosePipe0IndexCount = g.Faces.size() * 3;
			mRoomHosePipe0IndexLocation = cc;
		}
		if(g.Name == "Cube1_Cube1Mesh") {
			mCube1IndexCount = g.Faces.size() * 3;
			mCube1IndexLocation = cc;
		}
		if(g.Name == "Hosepipe2_Hosepipe2Mesh") {
			mRoomHosePipe2IndexCount = g.Faces.size() * 3;
			mRoomHosePipe2IndexLocation = cc;
		}
		if(g.Name == "Cube2_Cube2Mesh") {
			mCube2IndexCount = g.Faces.size() * 3;
			mCube2IndexLocation = cc;
		}
		if(g.Name == "Hosepipe1_Hosepipe1Mesh") {
			mRoomHosePipe1IndexCount = g.Faces.size() * 3;
			mRoomHosePipe1IndexLocation = cc;
		}
		if(g.Name == "Slope_SlopeMesh") {
			mSlopeIndexCount = g.Faces.size() * 3;
			mSlopeIndexLocation = cc;
		}
		if(g.Name == "Support3_Support3Mesh") {
			mSupport3IndexCount = g.Faces.size() * 3;
			mSupport3IndexLocation = cc;
		}
		if(g.Name == "Support0_Support0Mesh") {
			mSupport0IndexCount = g.Faces.size() * 3;
			mSupport0IndexLocation = cc;
		}
		if(g.Name == "Roof_RoofMesh") {
			mRoofIndexCount = g.Faces.size() * 3;
			mRoofIndexLocation = cc;
		}
		if(g.Name == "SideWall0_SideWall0Mesh") {
			mSideWall0IndexCount = g.Faces.size() * 3;
			mSideWall0IndexLocation = cc;
		}
		if(g.Name == "Support1_Support1Mesh") {
			mSupport1IndexCount = g.Faces.size() * 3;
			mSupport1IndexLocation = cc;
		}
		if(g.Name == "RedPipe5_RedPipe5Mesh") {
			mRedPipe5IndexCount = g.Faces.size() * 3;
			mRedPipe5IndexLocation = cc;
		}
		if(g.Name == "RedPipe4_RedPipe4Mesh") {
			mRedPipe4IndexCount = g.Faces.size() * 3;
			mRedPipe4IndexLocation = cc;
		}
		if(g.Name == "RedPipe3_RedPipe3Mesh") {
			mRedPipe3IndexCount = g.Faces.size() * 3;
			mRedPipe3IndexLocation = cc;
		}
		if(g.Name == "RedPipe6_RedPipe6Mesh") {
			mRedPipe6IndexCount = g.Faces.size() * 3;
			mRedPipe6IndexLocation = cc;
		}
		if(g.Name == "RedPipe7_RedPipe7Mesh") {
			mRedPipe7IndexCount = g.Faces.size() * 3;
			mRedPipe7IndexLocation = cc;
		}
		if(g.Name == "Cube3_Cube3Mesh") {
			mCube3IndexCount = g.Faces.size() * 3;
			mCube3IndexLocation = cc;
		}
		if(g.Name == "FrontWall_FrontWallMesh") {
			mFrontWallIndexCount = g.Faces.size() * 3;
			mFrontWallIndexLocation = cc;
		}
		if(g.Name == "RedPipe2_RedPipe2Mesh") {
			mRedPipe2IndexCount = g.Faces.size() * 3;
			mRedPipe2IndexLocation = cc;
		}
		if(g.Name == "BackWall_BackWallMesh") {
			mBackWallIndexCount = g.Faces.size() * 3;
			mBackWallIndexLocation = cc;
		}
		if(g.Name == "Cube0_Cube0Mesh") {
			mCube0IndexCount = g.Faces.size() * 3;
			mCube0IndexLocation = cc;
		}
		if(g.Name == "Drawing0_Drawing0Mesh") {
			mDrawing0IndexCount = g.Faces.size() * 3;
			mDrawing0IndexLocation = cc;
		}
		if(g.Name == "Drawing1_Drawing1Mesh") {
			mDrawing1IndexCount = g.Faces.size() * 3;
			mDrawing1IndexLocation = cc;
		}
		if(g.Name == "Drawing2_Drawing2Mesh") {
			mDrawing2IndexCount = g.Faces.size() * 3;
			mDrawing2IndexLocation = cc;
		}
		if(g.Name == "Drawing3_Drawing3Mesh") {
			mDrawing3IndexCount = g.Faces.size() * 3;
			mDrawing3IndexLocation = cc;
		}
		for(UINT k = 0; k < g.Faces.size(); ++k) {
			ObjLoader::Face f = g.Faces[k];
			for(UINT j = 0; j < f.vertices.size(); ++j) {
				ObjLoader::FaceVertex fv = f.vertices[j];
				Vertex::PosNormalTexTan v;
				v.Pos = loader.Vertices[fv.VertexIndex - 1].Pos;
				v.Normal = loader.Normals[fv.NormalIndex - 1];
				XMFLOAT2 ttx = loader.Textures[fv.TextureIndex - 1];
				v.Tex = XMFLOAT2(-1.0f * ttx.x, -1.0f * ttx.y);
				vertices.push_back(v);
				indices.push_back(cc++);

				XMVECTOR P = XMLoadFloat3(&v.Pos);

				vMin = XMVectorMin(vMin, P);
				vMax = XMVectorMax(vMax, P);
			}
		}
	}

	CalculateTangentsAndNormals(vertices, indices);

	XMStoreFloat3(&mCapsuleBox.Center, 0.5f * (vMin + vMax));
	XMStoreFloat3(&mCapsuleBox.Extents, 0.5f * (vMax - vMin));

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex::PosNormalTexTan) * vertices.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices.data();

	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mRoomVB));

	// Pack the indices of all the meshes into one index buffer.
	D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * mRoomIndexCount;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &indices[0];
    HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mRoomIB));
}

void BoxApp::BuildInstancedBuffer() {
	const int n = 20;
	mInstancedData.resize(n * n * n);
	
	float width = 20.0f;
	float height = 15.0f;
	float depth = 20.0f;
	
	float sqize = 0.25f;

	float x = -0.5f * width;
	float y = -0.5f * height * sqize;
	float z = -0.5f * depth;
	float dx = width / (n - 1);
	float dy = height / (n - 1) * sqize;
	float dz = depth / (n - 1);

	for(int k = 0; k < n; ++k) {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				// Position instanced along a 3D grid.
				float scale = MathHelper::RandF(0.025f, 0.15f);
				float cx = x + j * dx;
				float cy = y + i * dy;
				float cz = z + k * dz;
				XMVECTOR point = XMVectorSet(cx, cy, cz, 1.0f);
				XMVECTOR len = XMVector3Length(point);
				XMFLOAT4 lenf;
				XMStoreFloat4(&lenf, len);
				float grouping = lenf.x / 10.0f;
				grouping *= grouping * MathHelper::RandF(0.95f, 1.0f);
				XMMATRIX world(
					scale,	0.0f,	0.0f,	0.0f,
					0.0f,	scale,	0.0f,	0.0f,
					0.0f,	0.0f,	scale,	0.0f,
					cx * grouping,		cy * grouping,		cz * grouping,		1.0f
				);
				XMMATRIX rot = XMMatrixRotationY(MathHelper::Pi / 180.0f * lenf.x * 20.0f * MathHelper::RandF(0.765f, 0.965f));
				world = XMMatrixMultiply(world, rot);

				XMStoreFloat4x4(&mInstancedData[k * n * n + i * n + j].World, world);

				// Random color.
				mInstancedData[k * n * n + i * n + j].Color.x = MathHelper::RandF(0.865f, 0.985f);
				mInstancedData[k * n * n + i * n + j].Color.y = MathHelper::RandF(0.865f, 0.985f);
				mInstancedData[k * n * n + i * n + j].Color.z = MathHelper::RandF(0.898f + grouping, 0.996f);
				mInstancedData[k * n * n + i * n + j].Color.w = 1.0f;
			}
		}
	}
	
	D3D11_BUFFER_DESC vbd;
    //vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Instance::InstancedData) * mInstancedData.size();
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    //vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = &mInstancedData[0];
	
    HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mInstancedBuffer));



	mInstancedData2.resize(1);
	float scale2 = 1.0f;
	XMMATRIX world2(
		scale2,	0.0f,	0.0f,	0.0f,
		0.0f,	scale2,	0.0f,	0.0f,
		0.0f,	0.0f,	scale2,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f
	);
	XMMATRIX trans2 = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	world2 = XMMatrixMultiply(world2, trans2);
	XMStoreFloat4x4(&mInstancedData2[0].World, world2);

	mInstancedData2[0].Color.x = 0.1f;
	mInstancedData2[0].Color.y = 0.1f;
	mInstancedData2[0].Color.z = 0.1f;
	mInstancedData2[0].Color.w = 1.0f;
	
	D3D11_BUFFER_DESC vbd2;
    //vbd2.Usage = D3D11_USAGE_DYNAMIC;
	vbd2.Usage = D3D11_USAGE_IMMUTABLE;
	vbd2.ByteWidth = sizeof(Instance::InstancedData) * mInstancedData2.size();
    vbd2.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    //vbd2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd2.CPUAccessFlags = 0;
    vbd2.MiscFlags = 0;
	vbd2.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vinitData2;
    vinitData2.pSysMem = &mInstancedData2[0];
	
    HR(md3dDevice->CreateBuffer(&vbd2, &vinitData2, &mInstancedBuffer2));
}

void BoxApp::BuildScreenQuadGeometryBuffers() {
	GeometryGenerator::MeshData quad;

	GeometryGenerator geoGen;
	geoGen.CreateFullscreenQuad(quad);

	// Extract the vertex elements we are interested in and pack the
	// vertices of all the meshes into one vertex buffer.
	std::vector<Vertex::Post> vertices(quad.Vertices.size());

	for(UINT i = 0; i < quad.Vertices.size(); ++i) {
		vertices[i].Pos    = quad.Vertices[i].Position;
		vertices[i].Tex    = quad.Vertices[i].TexC;
	}

    D3D11_BUFFER_DESC vbd;
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = sizeof(Vertex::Post) * quad.Vertices.size();
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = &vertices[0];
    HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mScreenQuadVB));

	// Pack the indices of all the meshes into one index buffer.
	D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * quad.Indices.size();
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;
    D3D11_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = &quad.Indices[0];
    HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mScreenQuadIB));
}

void BoxApp::BuildOffscreenViews() {
	// We call this function everytime the window is resized so that the render target is a quarter
	// the client area dimensions.  So Release the previous views before we create new ones.
	ReleaseCOM(mOffscreenSRV);
	ReleaseCOM(mOffscreenRTV);
	ReleaseCOM(mOffscreenUAV);

	D3D11_TEXTURE2D_DESC texDesc;
	
	texDesc.Width     = mClientWidth;
	texDesc.Height    = mClientHeight;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.SampleDesc.Count   = 1;  
	texDesc.SampleDesc.Quality = 0;  
	texDesc.Usage          = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags      = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	texDesc.CPUAccessFlags = 0; 
	texDesc.MiscFlags      = 0;

	ID3D11Texture2D* offscreenTex = 0;
	HR(md3dDevice->CreateTexture2D(&texDesc, 0, &offscreenTex));

	// Null description means to create a view to all mipmap levels using 
	// the format the texture was created with.
	HR(md3dDevice->CreateShaderResourceView(offscreenTex, 0, &mOffscreenSRV));
	HR(md3dDevice->CreateRenderTargetView(offscreenTex, 0, &mOffscreenRTV));
	HR(md3dDevice->CreateUnorderedAccessView(offscreenTex, 0, &mOffscreenUAV));

	// View saves a reference to the texture so we can release our reference.
	ReleaseCOM(offscreenTex);

	// We call this function everytime the window is resized so that the render target is a quarter
	// the client area dimensions.  So Release the previous views before we create new ones.
	ReleaseCOM(mOffscreenSRV2);
	ReleaseCOM(mOffscreenRTV2);
	ReleaseCOM(mOffscreenUAV2);

	D3D11_TEXTURE2D_DESC texDesc2;
	
	texDesc2.Width     = mClientWidth;
	texDesc2.Height    = mClientHeight;
	texDesc2.MipLevels = 0;
	texDesc2.ArraySize = 1;
	texDesc2.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc2.SampleDesc.Count   = 1;  
	texDesc2.SampleDesc.Quality = 0;  
	texDesc2.Usage          = D3D11_USAGE_DEFAULT;
	texDesc2.BindFlags      = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	texDesc2.CPUAccessFlags = 0; 
	texDesc2.MiscFlags      = 0;

	ID3D11Texture2D* offscreenTex2 = 0;
	HR(md3dDevice->CreateTexture2D(&texDesc2, 0, &offscreenTex2));

	// Null description means to create a view to all mipmap levels using 
	// the format the texture was created with.
	HR(md3dDevice->CreateShaderResourceView(offscreenTex2, 0, &mOffscreenSRV2));
	HR(md3dDevice->CreateRenderTargetView(offscreenTex2, 0, &mOffscreenRTV2));
	HR(md3dDevice->CreateUnorderedAccessView(offscreenTex2, 0, &mOffscreenUAV2));

	// View saves a reference to the texture so we can release our reference.
	ReleaseCOM(offscreenTex2);
}

void BoxApp::CalculateTangentsAndNormals(std::vector<Vertex::PosNormalTexTan>& verts, std::vector<UINT>& idx) {
	// Computing Tangent Space Basis Vectors for an Arbitrary Mesh
	XMFLOAT3 zero(0.0f, 0.0f, 0.0f);
    const XMVECTOR NullVector = XMLoadFloat4(&XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f));
    const XMVECTOR W_Null = XMLoadFloat4(&XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f));
    const XMVECTOR signature = XMLoadFloat4(&XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f));
    XMMATRIX st(NullVector, NullVector, NullVector, NullVector);

	const UINT NumberOfVertices = (UINT)verts.size();
	std::vector<XMFLOAT3> vTangents;
	std::vector<XMFLOAT3> vBitangents;
    //std::vector<XMVECTOR> vTangents(NumberOfVertices);
	//std::vector<XMVECTOR> vBitangents(NumberOfVertices);

    vTangents.resize(NumberOfVertices, zero);
    vBitangents.resize(NumberOfVertices, zero);

    const UINT NumberOfIndices = (UINT)idx.size();
    for (UINT i = 0; i < NumberOfIndices; ++i) {
        const UINT i0 = idx[i];
        const UINT i1 = idx[++i];
        const UINT i2 = idx[++i];

        const XMVECTOR v0 = XMLoadFloat3(&verts[i0].Pos);
        const XMVECTOR v1 = XMLoadFloat3(&verts[i1].Pos);
        const XMVECTOR v2 = XMLoadFloat3(&verts[i2].Pos);

        const XMVECTOR e0 = XMVectorMultiply(v1 - v0, W_Null);
        const XMVECTOR e1 = XMVectorMultiply(v2 - v0, W_Null);

        const XMMATRIX e01(e0, e1, NullVector, NullVector);
        /*      | e0.x e0.y e0.z 0 |
                | e1.x e1.y e1.z 0 |
        e01 =   | 0    0    0    0 |
                | 0    0    0    0 |
        */
        const XMVECTOR t0 = XMLoadFloat2(&verts[i0].Tex);
        const XMVECTOR t1 = XMLoadFloat2(&verts[i1].Tex);
        const XMVECTOR t2 = XMLoadFloat2(&verts[i2].Tex);

        XMVECTOR s = XMVectorMergeXY(t1 - t0, t2 - t0); // s = (t1x - t0x, t2x - t0x, t1y - t0y, t2y - t0y)

        XMFLOAT4 d;
        XMStoreFloat4(&d, s);

        const float DetInv = 1.0f/(d.x * d.w - d.z * d.y);

        s *= DetInv;
        s = XMVectorMultiply(s, signature); // s = (sx, -sy, -sz, sw)

        const UINT *const pSrc = reinterpret_cast<const UINT *const>(&s);
        UINT* pDst = reinterpret_cast<UINT*>(&st.r[0]);
        pDst[0] = pSrc[3];  // _00 = sw
        pDst[1] = pSrc[2];  // _01 = -sz
        pDst = reinterpret_cast<UINT*>(&st.r[1]);
        pDst[0] = pSrc[1];  // _10 = -sy
        pDst[1] = pSrc[0];  // _11 = sz

        /*      | sw  -sz 0 0 |
                | -sy sx  0 0 |
        st =    | 0    0  0 0 |*DetInv
                | 0    0  0 0 |
        */

        const XMMATRIX uv(XMMatrixMultiply(st, e01));

		XMVECTOR vt0 = XMLoadFloat3(&vTangents[i0]);
        XMVECTOR vt1 = XMLoadFloat3(&vTangents[i1]);
        XMVECTOR vt2 = XMLoadFloat3(&vTangents[i2]);
		vt0 += uv.r[0];
		vt1 += uv.r[0];
		vt2 += uv.r[0];
		XMStoreFloat3(&vTangents[i0], vt0);
		XMStoreFloat3(&vTangents[i1], vt1);
		XMStoreFloat3(&vTangents[i2], vt1);

		XMVECTOR vbt0 = XMLoadFloat3(&vBitangents[i0]);
        XMVECTOR vbt1 = XMLoadFloat3(&vBitangents[i1]);
        XMVECTOR vbt2 = XMLoadFloat3(&vBitangents[i2]);
		vbt0 += uv.r[1];
		vbt1 += uv.r[1];
		vbt2 += uv.r[1];
		XMStoreFloat3(&vBitangents[i0], vbt0);
		XMStoreFloat3(&vBitangents[i1], vbt1);
		XMStoreFloat3(&vBitangents[i2], vbt1);
    }

    // orthogonalize normals and tangents
    for ( UINT i = 0; i < NumberOfVertices; ++i ) {
        const XMVECTOR normal = XMVector3Normalize(XMLoadFloat3(&verts[i].Normal));
		XMVECTOR vt = XMLoadFloat3(&vTangents[i]);
		XMVECTOR vbt = XMLoadFloat3(&vBitangents[i]);

        // normalize tangents and orthogonalize TBN
        XMVECTOR n0 = XMVector3Normalize(vt - XMVector3Dot(normal, vt) * normal);

        //calculate handedness
        const XMVECTOR n1 = XMVector3Cross(normal, vt);
        const float w = (XMVector3Less(XMVector3Dot(n1, vbt), NullVector)) ? -1.0f : 1.0f;

        n0 = XMVectorSetW(n0, w);
        XMStoreFloat3(&verts[i].TangentU, n0);
    }
}