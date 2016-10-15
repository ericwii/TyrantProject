#pragma once

class Model;

class Instance
{
public:
	Instance();
	Instance(Model* aModel, CU::Matrix44<float> anOrientation = CU::Matrix44<float>());
	~Instance();

	void Init(Model* aModel, CU::Matrix44<float> anOrientation = CU::Matrix44<float>());
	void Render();

	inline void SetPosition(Vector3<float> aPosition);
	inline void SetOrientation(CU::Matrix44<float> anOrientation);

	inline const CU::Matrix44<float>& GetOrientation() const;
	inline Vector3<float> GetPosition() const;

private:
	Model* myModel;
	CU::Matrix44<float> myOrientation;
};


inline void Instance::SetPosition(Vector3<float> aPosition)
{
	myOrientation.SetPosition(aPosition);
}

inline void Instance::SetOrientation(CU::Matrix44<float> anOrientation)
{
	myOrientation = anOrientation;
}


inline const CU::Matrix44<float>& Instance::GetOrientation() const
{
	return myOrientation;
}

inline Vector3<float> Instance::GetPosition() const
{
	return myOrientation.GetPosition();
}