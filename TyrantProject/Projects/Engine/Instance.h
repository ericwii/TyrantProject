#pragma once
#include "../CommonUtilities/GrowingArray.h"

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

	inline const CU::Matrix44<float>& GetOrientation() const;
	inline Vector3<float> GetPosition() const;

	void AddChild(Instance* anInstance);
	void AddChild(Text* aText);

	void RemoveChild(Instance* anInstance);
	void RemoveChild(Text* aText);

private:
	Model* myModel;
	CU::GrowingArray<Instance*> myInstances;
	CU::GrowingArray<Text*> myTexts;
	CU::Matrix44<float> myOrientation;
};


inline const CU::Matrix44<float>& Instance::GetOrientation() const
{
	return myOrientation;
}

inline Vector3<float> Instance::GetPosition() const
{
	return myOrientation.GetPosition();
}