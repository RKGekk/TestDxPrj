#ifndef EFFECTS_H
#define EFFECTS_H

#include "d3dUtil.h"

#pragma region Effect
class Effect {
public:
	Effect(ID3D11Device* device, const std::wstring& filename, bool compile);
	virtual ~Effect();

private:
	Effect(const Effect& rhs);
	Effect& operator=(const Effect& rhs);

protected:
	ID3DX11Effect* mFX;
};
#pragma endregion

#pragma region ColorEffect
class ColorEffect : public Effect {
public:
	ColorEffect(ID3D11Device* device, const std::wstring& filename);
	~ColorEffect();

	void SetWorldViewProj(CXMMATRIX M)                  { mfxWorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }

	ID3DX11EffectTechnique* mTech;

	ID3DX11EffectMatrixVariable* mfxWorldViewProj;
};
#pragma endregion

#pragma region BasicEffect
class BasicEffect : public Effect {
public:
	BasicEffect(ID3D11Device* device, const std::wstring& filename);
	~BasicEffect();

	void SetWorldViewProj(CXMMATRIX M)                  { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(CXMMATRIX M)                          { World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(CXMMATRIX M)              { WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetEyePosW(const XMFLOAT3& v)                  { EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetDirLights(const DirectionalLight* lights)   { DirLights->SetRawValue(lights, 0, 3*sizeof(DirectionalLight)); }
	void SetSpotLights(const SpotLight& light)			{ SpotLightVar->SetRawValue(&light, 0, sizeof(SpotLight)); }
	void SetMaterial(const Material& mat)               { Mat->SetRawValue(&mat, 0, sizeof(Material)); }

	ID3DX11EffectTechnique* Light1Tech;
	ID3DX11EffectTechnique* Light2Tech;
	ID3DX11EffectTechnique* Light3Tech;

	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldInvTranspose;
	ID3DX11EffectVectorVariable* EyePosW;
	ID3DX11EffectVariable* DirLights;
	ID3DX11EffectVariable* SpotLightVar;
	ID3DX11EffectVariable* Mat;
};
#pragma endregion

#pragma region BasicEffect32
class BasicEffect32 : public Effect {
public:
	BasicEffect32(ID3D11Device* device, const std::wstring& filename);
	~BasicEffect32();

	void SetWorldViewProj(CXMMATRIX M)                  { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(CXMMATRIX M)                          { World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(CXMMATRIX M)              { WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetTexTransform(CXMMATRIX M)                   { TexTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetEyePosW(const XMFLOAT3& v)                  { EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetDirLights(const DirectionalLight* lights)   { DirLights->SetRawValue(lights, 0, 3*sizeof(DirectionalLight)); }
	void SetMaterial(const Material& mat)               { Mat->SetRawValue(&mat, 0, sizeof(Material)); }
	void SetDiffuseMap(ID3D11ShaderResourceView* tex)   { DiffuseMap->SetResource(tex); }

	ID3DX11EffectTechnique* Light1Tech;
	ID3DX11EffectTechnique* Light2Tech;
	ID3DX11EffectTechnique* Light3Tech;

	ID3DX11EffectTechnique* Light0TexTech;
	ID3DX11EffectTechnique* Light1TexTech;
	ID3DX11EffectTechnique* Light2TexTech;
	ID3DX11EffectTechnique* Light3TexTech;

	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldInvTranspose;
	ID3DX11EffectMatrixVariable* TexTransform;
	ID3DX11EffectVectorVariable* EyePosW;
	ID3DX11EffectVariable* DirLights;
	ID3DX11EffectVariable* Mat;

	ID3DX11EffectShaderResourceVariable* DiffuseMap;
};
#pragma endregion

#pragma region BasicEffect32BF
class BasicEffect32BF : public Effect {
public:
	BasicEffect32BF(ID3D11Device* device, const std::wstring& filename);
	~BasicEffect32BF();

	void SetWorldViewProj(CXMMATRIX M)                  { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(CXMMATRIX M)                          { World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(CXMMATRIX M)              { WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetTexTransform(CXMMATRIX M)                   { TexTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetEyePosW(const XMFLOAT3& v)                  { EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetFogColor(const FXMVECTOR v)                 { FogColor->SetFloatVector(reinterpret_cast<const float*>(&v)); }
	void SetFogStart(float f)                           { FogStart->SetFloat(f); }
	void SetFogRange(float f)                           { FogRange->SetFloat(f); }
	void SetDirLights(const DirectionalLight* lights)   { DirLights->SetRawValue(lights, 0, 3*sizeof(DirectionalLight)); }
	void SetMaterial(const Material& mat)               { Mat->SetRawValue(&mat, 0, sizeof(Material)); }
	void SetDiffuseMap(ID3D11ShaderResourceView* tex)   { DiffuseMap->SetResource(tex); }

	ID3DX11EffectTechnique* Light1Tech;
	ID3DX11EffectTechnique* Light2Tech;
	ID3DX11EffectTechnique* Light3Tech;

	ID3DX11EffectTechnique* Light0TexTech;
	ID3DX11EffectTechnique* Light1TexTech;
	ID3DX11EffectTechnique* Light2TexTech;
	ID3DX11EffectTechnique* Light3TexTech;

	ID3DX11EffectTechnique* Light0TexAlphaClipTech;
	ID3DX11EffectTechnique* Light1TexAlphaClipTech;
	ID3DX11EffectTechnique* Light2TexAlphaClipTech;
	ID3DX11EffectTechnique* Light3TexAlphaClipTech;

	ID3DX11EffectTechnique* Light1FogTech;
	ID3DX11EffectTechnique* Light2FogTech;
	ID3DX11EffectTechnique* Light3FogTech;

	ID3DX11EffectTechnique* Light0TexFogTech;
	ID3DX11EffectTechnique* Light1TexFogTech;
	ID3DX11EffectTechnique* Light2TexFogTech;
	ID3DX11EffectTechnique* Light3TexFogTech;

	ID3DX11EffectTechnique* Light0TexAlphaClipFogTech;
	ID3DX11EffectTechnique* Light1TexAlphaClipFogTech;
	ID3DX11EffectTechnique* Light2TexAlphaClipFogTech;
	ID3DX11EffectTechnique* Light3TexAlphaClipFogTech;

	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldInvTranspose;
	ID3DX11EffectMatrixVariable* TexTransform;
	ID3DX11EffectVectorVariable* EyePosW;
	ID3DX11EffectVectorVariable* FogColor;
	ID3DX11EffectScalarVariable* FogStart;
	ID3DX11EffectScalarVariable* FogRange;
	ID3DX11EffectVariable* DirLights;
	ID3DX11EffectVariable* Mat;

	ID3DX11EffectShaderResourceVariable* DiffuseMap;
};
#pragma endregion

#pragma region BlurEffect
class BlurEffect : public Effect {
public:
	BlurEffect(ID3D11Device* device, const std::wstring& filename);
	~BlurEffect();

	void SetWeights(const float weights[9])           { Weights->SetFloatArray(weights, 0, 9); }
	void SetInputMap(ID3D11ShaderResourceView* tex)   { InputMap->SetResource(tex); }
	void SetOutputMap(ID3D11UnorderedAccessView* tex) { OutputMap->SetUnorderedAccessView(tex); }

	ID3DX11EffectTechnique* HorzBlurTech;
	ID3DX11EffectTechnique* VertBlurTech;

	ID3DX11EffectScalarVariable* Weights;
	ID3DX11EffectShaderResourceVariable* InputMap;
	ID3DX11EffectUnorderedAccessViewVariable* OutputMap;
};
#pragma endregion

#pragma region InstancedBasicEffect
class InstancedBasicEffect : public Effect {
public:
	InstancedBasicEffect(ID3D11Device* device, const std::wstring& filename);
	~InstancedBasicEffect();

	void SetViewProj(CXMMATRIX M)                       { ViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(CXMMATRIX M)                          { World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(CXMMATRIX M)              { WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetTexTransform(CXMMATRIX M)                   { TexTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetEyePosW(const XMFLOAT3& v)                  { EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetFogColor(const FXMVECTOR v)                 { FogColor->SetFloatVector(reinterpret_cast<const float*>(&v)); }
	void SetFogStart(float f)                           { FogStart->SetFloat(f); }
	void SetFogRange(float f)                           { FogRange->SetFloat(f); }
	void SetDirLights(const DirectionalLight* lights)   { DirLights->SetRawValue(lights, 0, 3*sizeof(DirectionalLight)); }
	void SetMaterial(const Material& mat)               { Mat->SetRawValue(&mat, 0, sizeof(Material)); }
	void SetDiffuseMap(ID3D11ShaderResourceView* tex)   { DiffuseMap->SetResource(tex); }

	ID3DX11EffectTechnique* Light1Tech;
	ID3DX11EffectTechnique* Light2Tech;
	ID3DX11EffectTechnique* Light3Tech;

	ID3DX11EffectTechnique* Light0TexTech;
	ID3DX11EffectTechnique* Light1TexTech;
	ID3DX11EffectTechnique* Light2TexTech;
	ID3DX11EffectTechnique* Light3TexTech;

	ID3DX11EffectTechnique* Light0TexAlphaClipTech;
	ID3DX11EffectTechnique* Light1TexAlphaClipTech;
	ID3DX11EffectTechnique* Light2TexAlphaClipTech;
	ID3DX11EffectTechnique* Light3TexAlphaClipTech;

	ID3DX11EffectTechnique* Light1FogTech;
	ID3DX11EffectTechnique* Light2FogTech;
	ID3DX11EffectTechnique* Light3FogTech;

	ID3DX11EffectTechnique* Light0TexFogTech;
	ID3DX11EffectTechnique* Light1TexFogTech;
	ID3DX11EffectTechnique* Light2TexFogTech;
	ID3DX11EffectTechnique* Light3TexFogTech;

	ID3DX11EffectTechnique* Light0TexAlphaClipFogTech;
	ID3DX11EffectTechnique* Light1TexAlphaClipFogTech;
	ID3DX11EffectTechnique* Light2TexAlphaClipFogTech;
	ID3DX11EffectTechnique* Light3TexAlphaClipFogTech;

	ID3DX11EffectMatrixVariable* ViewProj;
	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldInvTranspose;
	ID3DX11EffectMatrixVariable* TexTransform;
	ID3DX11EffectVectorVariable* EyePosW;
	ID3DX11EffectVectorVariable* FogColor;
	ID3DX11EffectScalarVariable* FogStart;
	ID3DX11EffectScalarVariable* FogRange;
	ID3DX11EffectVariable* DirLights;
	ID3DX11EffectVariable* Mat;

	ID3DX11EffectShaderResourceVariable* DiffuseMap;
};
#pragma endregion

#pragma region Post
class PostEffect : public Effect {
public:
	PostEffect(ID3D11Device* device, const std::wstring& filename);
	~PostEffect();

	void SetWorldViewProj(CXMMATRIX M)                  { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(CXMMATRIX M)                          { World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(CXMMATRIX M)              { WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetTexTransform(CXMMATRIX M)                   { TexTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetDiffuseMap(ID3D11ShaderResourceView* tex)   { DiffuseMap->SetResource(tex); }
	void SetDiffuseMap2(ID3D11ShaderResourceView* tex)   { DiffuseMap2->SetResource(tex); }

	ID3DX11EffectTechnique* Tech1;

	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldInvTranspose;
	ID3DX11EffectMatrixVariable* TexTransform;

	ID3DX11EffectShaderResourceVariable* DiffuseMap;
	ID3DX11EffectShaderResourceVariable* DiffuseMap2;
};
#pragma endregion

#pragma region SkyEffect
class SkyEffect : public Effect {
public:
	SkyEffect(ID3D11Device* device, const std::wstring& filename);
	~SkyEffect();

	void SetWorldViewProj(CXMMATRIX M)                  { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetCubeMap(ID3D11ShaderResourceView* cubemap)  { CubeMap->SetResource(cubemap); }

	ID3DX11EffectTechnique* SkyTech;

	ID3DX11EffectMatrixVariable* WorldViewProj;

	ID3DX11EffectShaderResourceVariable* CubeMap;
};
#pragma endregion

#pragma region InstancedBasicMTREffect
class InstancedBasicMTREffect : public Effect {
public:
	InstancedBasicMTREffect(ID3D11Device* device, const std::wstring& filename);
	~InstancedBasicMTREffect();

	void SetViewProj(CXMMATRIX M)                       { ViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(CXMMATRIX M)                          { World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(CXMMATRIX M)              { WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetEyePosW(const XMFLOAT3& v)                  { EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetFogColor(const FXMVECTOR v)                 { FogColor->SetFloatVector(reinterpret_cast<const float*>(&v)); }
	void SetFogStart(float f)                           { FogStart->SetFloat(f); }
	void SetFogRange(float f)                           { FogRange->SetFloat(f); }

	ID3DX11EffectTechnique* Tech1;
	ID3DX11EffectTechnique* Tech2;

	ID3DX11EffectMatrixVariable* ViewProj;
	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldInvTranspose;
	ID3DX11EffectVectorVariable* EyePosW;
	ID3DX11EffectVectorVariable* FogColor;
	ID3DX11EffectScalarVariable* FogStart;
	ID3DX11EffectScalarVariable* FogRange;
};
#pragma endregion

#pragma region NormalMapEffect
class NormalMapEffect : public Effect {
public:
	NormalMapEffect(ID3D11Device* device, const std::wstring& filename);
	~NormalMapEffect();

	void SetWorldViewProj(CXMMATRIX M)                  { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(CXMMATRIX M)                          { World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(CXMMATRIX M)              { WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetTexTransform(CXMMATRIX M)                   { TexTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetEyePosW(const XMFLOAT3& v)                  { EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetFogColor(const FXMVECTOR v)                 { FogColor->SetFloatVector(reinterpret_cast<const float*>(&v)); }
	void SetFogStart(float f)                           { FogStart->SetFloat(f); }
	void SetFogRange(float f)                           { FogRange->SetFloat(f); }
	void SetDirLights(const DirectionalLight* lights)   { DirLights->SetRawValue(lights, 0, 3*sizeof(DirectionalLight)); }
	void SetSpotLights(const SpotLight& light)			{ SpotLightVar->SetRawValue(&light, 0, sizeof(SpotLight)); }
	void SetMaterial(const Material& mat)               { Mat->SetRawValue(&mat, 0, sizeof(Material)); }
	void SetDiffuseMap(ID3D11ShaderResourceView* tex)   { DiffuseMap->SetResource(tex); }
	void SetCubeMap(ID3D11ShaderResourceView* tex)      { CubeMap->SetResource(tex); }
	void SetNormalMap(ID3D11ShaderResourceView* tex)    { NormalMap->SetResource(tex); }

	ID3DX11EffectTechnique* Light1Tech;
	ID3DX11EffectTechnique* Light2Tech;
	ID3DX11EffectTechnique* Light3Tech;

	ID3DX11EffectTechnique* Light0TexTech;
	ID3DX11EffectTechnique* Light1TexTech;
	ID3DX11EffectTechnique* Light2TexTech;
	ID3DX11EffectTechnique* Light3TexTech;

	ID3DX11EffectTechnique* Light0TexAlphaClipTech;
	ID3DX11EffectTechnique* Light1TexAlphaClipTech;
	ID3DX11EffectTechnique* Light2TexAlphaClipTech;
	ID3DX11EffectTechnique* Light3TexAlphaClipTech;

	ID3DX11EffectTechnique* Light1FogTech;
	ID3DX11EffectTechnique* Light2FogTech;
	ID3DX11EffectTechnique* Light3FogTech;

	ID3DX11EffectTechnique* Light0TexFogTech;
	ID3DX11EffectTechnique* Light1TexFogTech;
	ID3DX11EffectTechnique* Light2TexFogTech;
	ID3DX11EffectTechnique* Light3TexFogTech;

	ID3DX11EffectTechnique* Light0TexAlphaClipFogTech;
	ID3DX11EffectTechnique* Light1TexAlphaClipFogTech;
	ID3DX11EffectTechnique* Light2TexAlphaClipFogTech;
	ID3DX11EffectTechnique* Light3TexAlphaClipFogTech;

	ID3DX11EffectTechnique* Light1ReflectTech;
	ID3DX11EffectTechnique* Light2ReflectTech;
	ID3DX11EffectTechnique* Light3ReflectTech;

	ID3DX11EffectTechnique* Light0TexReflectTech;
	ID3DX11EffectTechnique* Light1TexReflectTech;
	ID3DX11EffectTechnique* Light2TexReflectTech;
	ID3DX11EffectTechnique* Light3TexReflectTech;

	ID3DX11EffectTechnique* Light0TexAlphaClipReflectTech;
	ID3DX11EffectTechnique* Light1TexAlphaClipReflectTech;
	ID3DX11EffectTechnique* Light2TexAlphaClipReflectTech;
	ID3DX11EffectTechnique* Light3TexAlphaClipReflectTech;

	ID3DX11EffectTechnique* Light1FogReflectTech;
	ID3DX11EffectTechnique* Light2FogReflectTech;
	ID3DX11EffectTechnique* Light3FogReflectTech;

	ID3DX11EffectTechnique* Light0TexFogReflectTech;
	ID3DX11EffectTechnique* Light1TexFogReflectTech;
	ID3DX11EffectTechnique* Light2TexFogReflectTech;
	ID3DX11EffectTechnique* Light3TexFogReflectTech;

	ID3DX11EffectTechnique* Light0TexAlphaClipFogReflectTech;
	ID3DX11EffectTechnique* Light1TexAlphaClipFogReflectTech;
	ID3DX11EffectTechnique* Light2TexAlphaClipFogReflectTech;
	ID3DX11EffectTechnique* Light3TexAlphaClipFogReflectTech;

	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldInvTranspose;
	ID3DX11EffectMatrixVariable* TexTransform;
	ID3DX11EffectVectorVariable* EyePosW;
	ID3DX11EffectVectorVariable* FogColor;
	ID3DX11EffectScalarVariable* FogStart;
	ID3DX11EffectScalarVariable* FogRange;
	ID3DX11EffectVariable* DirLights;
	ID3DX11EffectVariable* SpotLightVar;
	ID3DX11EffectVariable* Mat;

	ID3DX11EffectShaderResourceVariable* DiffuseMap;
	ID3DX11EffectShaderResourceVariable* CubeMap;
	ID3DX11EffectShaderResourceVariable* NormalMap;
};
#pragma endregion

#pragma region DisplacementMapEffect
class DisplacementMapEffect : public Effect {
public:
	DisplacementMapEffect(ID3D11Device* device, const std::wstring& filename);
	~DisplacementMapEffect();

	void SetViewProj(CXMMATRIX M)                       { ViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldViewProj(CXMMATRIX M)                  { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(CXMMATRIX M)                          { World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(CXMMATRIX M)              { WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetTexTransform(CXMMATRIX M)                   { TexTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetEyePosW(const XMFLOAT3& v)                  { EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetFogColor(const FXMVECTOR v)                 { FogColor->SetFloatVector(reinterpret_cast<const float*>(&v)); }
	void SetFogStart(float f)                           { FogStart->SetFloat(f); }
	void SetFogRange(float f)                           { FogRange->SetFloat(f); }
	void SetDirLights(const DirectionalLight* lights)   { DirLights->SetRawValue(lights, 0, 3*sizeof(DirectionalLight)); }
	void SetMaterial(const Material& mat)               { Mat->SetRawValue(&mat, 0, sizeof(Material)); }
	void SetHeightScale(float f)                        { HeightScale->SetFloat(f); }
	void SetMaxTessDistance(float f)                    { MaxTessDistance->SetFloat(f); }
	void SetMinTessDistance(float f)                    { MinTessDistance->SetFloat(f); }
	void SetMinTessFactor(float f)                      { MinTessFactor->SetFloat(f); }
	void SetMaxTessFactor(float f)                      { MaxTessFactor->SetFloat(f); }

	void SetDiffuseMap(ID3D11ShaderResourceView* tex)   { DiffuseMap->SetResource(tex); }
	void SetCubeMap(ID3D11ShaderResourceView* tex)      { CubeMap->SetResource(tex); }
	void SetNormalMap(ID3D11ShaderResourceView* tex)    { NormalMap->SetResource(tex); }

	ID3DX11EffectTechnique* Light1Tech;
	ID3DX11EffectTechnique* Light2Tech;
	ID3DX11EffectTechnique* Light3Tech;

	ID3DX11EffectTechnique* Light0TexTech;
	ID3DX11EffectTechnique* Light1TexTech;
	ID3DX11EffectTechnique* Light2TexTech;
	ID3DX11EffectTechnique* Light3TexTech;

	ID3DX11EffectTechnique* Light0TexAlphaClipTech;
	ID3DX11EffectTechnique* Light1TexAlphaClipTech;
	ID3DX11EffectTechnique* Light2TexAlphaClipTech;
	ID3DX11EffectTechnique* Light3TexAlphaClipTech;

	ID3DX11EffectTechnique* Light1FogTech;
	ID3DX11EffectTechnique* Light2FogTech;
	ID3DX11EffectTechnique* Light3FogTech;

	ID3DX11EffectTechnique* Light0TexFogTech;
	ID3DX11EffectTechnique* Light1TexFogTech;
	ID3DX11EffectTechnique* Light2TexFogTech;
	ID3DX11EffectTechnique* Light3TexFogTech;

	ID3DX11EffectTechnique* Light0TexAlphaClipFogTech;
	ID3DX11EffectTechnique* Light1TexAlphaClipFogTech;
	ID3DX11EffectTechnique* Light2TexAlphaClipFogTech;
	ID3DX11EffectTechnique* Light3TexAlphaClipFogTech;

	ID3DX11EffectTechnique* Light1ReflectTech;
	ID3DX11EffectTechnique* Light2ReflectTech;
	ID3DX11EffectTechnique* Light3ReflectTech;

	ID3DX11EffectTechnique* Light0TexReflectTech;
	ID3DX11EffectTechnique* Light1TexReflectTech;
	ID3DX11EffectTechnique* Light2TexReflectTech;
	ID3DX11EffectTechnique* Light3TexReflectTech;

	ID3DX11EffectTechnique* Light0TexAlphaClipReflectTech;
	ID3DX11EffectTechnique* Light1TexAlphaClipReflectTech;
	ID3DX11EffectTechnique* Light2TexAlphaClipReflectTech;
	ID3DX11EffectTechnique* Light3TexAlphaClipReflectTech;

	ID3DX11EffectTechnique* Light1FogReflectTech;
	ID3DX11EffectTechnique* Light2FogReflectTech;
	ID3DX11EffectTechnique* Light3FogReflectTech;

	ID3DX11EffectTechnique* Light0TexFogReflectTech;
	ID3DX11EffectTechnique* Light1TexFogReflectTech;
	ID3DX11EffectTechnique* Light2TexFogReflectTech;
	ID3DX11EffectTechnique* Light3TexFogReflectTech;

	ID3DX11EffectTechnique* Light0TexAlphaClipFogReflectTech;
	ID3DX11EffectTechnique* Light1TexAlphaClipFogReflectTech;
	ID3DX11EffectTechnique* Light2TexAlphaClipFogReflectTech;
	ID3DX11EffectTechnique* Light3TexAlphaClipFogReflectTech;

	ID3DX11EffectMatrixVariable* ViewProj;
	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldInvTranspose;
	ID3DX11EffectMatrixVariable* TexTransform;
	ID3DX11EffectVectorVariable* EyePosW;
	ID3DX11EffectVectorVariable* FogColor;
	ID3DX11EffectScalarVariable* FogStart;
	ID3DX11EffectScalarVariable* FogRange;
	ID3DX11EffectVariable* DirLights;
	ID3DX11EffectVariable* Mat;
	ID3DX11EffectScalarVariable* HeightScale;
	ID3DX11EffectScalarVariable* MaxTessDistance;
	ID3DX11EffectScalarVariable* MinTessDistance;
	ID3DX11EffectScalarVariable* MinTessFactor;
	ID3DX11EffectScalarVariable* MaxTessFactor;
 
	ID3DX11EffectShaderResourceVariable* DiffuseMap;
	ID3DX11EffectShaderResourceVariable* CubeMap;
	ID3DX11EffectShaderResourceVariable* NormalMap;
};
#pragma endregion

#pragma region Effects
class Effects {
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

	static ColorEffect* ColorFX;
	static BasicEffect* BasicFX;
	static BasicEffect32* BasicFX32;
	static BasicEffect32BF* BasicFX32BF;
	static BlurEffect* BlurFX;
	static InstancedBasicEffect* InstancedBasicFX;
	static PostEffect* PostFX;
	static SkyEffect* SkyFX;
	static InstancedBasicMTREffect* InstancedBasicMTRFX;
	static NormalMapEffect* NormalMapFX;
	static DisplacementMapEffect* DisplacementMapFX;
};
#pragma endregion

#endif // EFFECTS_H