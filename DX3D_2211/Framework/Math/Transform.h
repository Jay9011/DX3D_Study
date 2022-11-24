#pragma once

class Transform
{ 
public:    
    string tag;
    bool isActive;

    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

protected:
    Vector3 pivot;

    Matrix world;
    Matrix* parent;    

    Vector3 globalPosition;
    Vector3 globalRotation;
    Vector3 globalScale;
public:
    Transform();
    virtual ~Transform();

    void UpdateWorld();    

    void PostRender();

    Vector3 Right();
    Vector3 Up();
    Vector3 Forward();

    Vector3 GlobalPos() { return globalPosition; }
    Vector3 GlobalRot() { return globalRotation; }
    Vector3 GlobalScale () { return globalScale; }

    Matrix& GetWorld() { return world; }

    void SetParent(Matrix* parent) { this->parent = parent; }
    void SetParent(Transform* transform) { parent = &transform->GetWorld(); }

    void SetPivot(float x, float y, float z) { pivot = { x, y, z }; }

    void Save();
    void Load();
};