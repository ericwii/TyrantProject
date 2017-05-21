#pragma once

class Text3D;
class Model;

class Instance
{
public:
	Instance();
	Instance(Model* aModel, CU::Matrix44<float> anOrientation = CU::Matrix44<float>());
	~Instance();

	void Init(Model* aModel, CU::Matrix44<float> anOrientation = CU::Matrix44<float>());
	void Init(Model* aModel, CU::GrowingArray<Instance*> someInstaceChildren, CU::Matrix44<float> anOrientation = CU::Matrix44<float>());
	void Render(bool aRenderChildren = true, unsigned int aPassIndex = 0);

	void SetPosition(Vector3<float> aPosition);
	void SetOrientation(CU::Matrix44<float> anOrientation);
	void SetAlpha(float alpha);


	inline CU::Matrix44<float>& GetOrientation();
	inline const CU::Matrix44<float>& GetOriginalOrientation() const;
	inline Vector3<float> GetPosition() const;
	inline void SetCurrentOrientationAsOriginal();

	void AddChild(Instance* anInstance);
	void AddChild(Text3D* aText);
	void SetChildPosition(Instance* aChild, Vector3<float> aPosition);
	void SetChildPosition(Text3D* aChild, Vector3<float> aPosition);

	void RemoveChild(Instance* anInstance);
	void RemoveChild(Text3D* aText);

private:
	Model* myModel;
	CU::GrowingArray<Instance*> myInstances;
	CU::GrowingArray<Text3D*> myTexts;
	CU::Matrix44<float> myOrientation;
	CU::Matrix44<float> myOriginalOrientation;
};

inline void Instance::SetCurrentOrientationAsOriginal()
{
	myOriginalOrientation = myOrientation;
}

inline CU::Matrix44<float>& Instance::GetOrientation()
{
	return myOrientation;
}

inline const CU::Matrix44<float>& Instance::GetOriginalOrientation() const
{
	return myOriginalOrientation;
}

inline Vector3<float> Instance::GetPosition() const
{
	return myOrientation.GetPosition();
}