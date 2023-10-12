#include "Framework.h"

Particle::Particle(string file)
{
    LoadData(file);

    instanceBuffer = new VertexBuffer(instances.data(),
        sizeof(InstanceData), data.count);
}

Particle::~Particle()
{
    delete quad;
    delete instanceBuffer;
}

void Particle::Update()
{
    if (!isPlay) return;

    lifeTime += DELTA;

    color.x = Lerp(data.startColor.x, data.endColor.x, lifeTime / data.duration);
    color.y = Lerp(data.startColor.y, data.endColor.y, lifeTime / data.duration);
    color.z = Lerp(data.startColor.z, data.endColor.z, lifeTime / data.duration);
    color.w = Lerp(data.startColor.w, data.endColor.w, lifeTime / data.duration);

    for (UINT i = 0; i < data.count; i++)
    {
        if (particleInfos[i].startTime > lifeTime)
        {
            transforms[i].Scale() = { 0, 0 };
            transforms[i].UpdateWorld();
            instances[i].transform = XMMatrixTranspose(transforms[i].GetWorld());
            continue;
        }

        particleInfos[i].velocity += particleInfos[i].accelation * DELTA;
        transforms[i].Pos() += particleInfos[i].velocity * particleInfos[i].speed * DELTA;
        transforms[i].Rot().z += particleInfos[i].angularVelocity * DELTA;          
        transforms[i].UpdateWorld();

        instances[i].transform = XMMatrixTranspose(transforms[i].GetWorld());
    }

    quad->GetColor() = color;
    instanceBuffer->Update(instances.data(), instances.size());

    if (lifeTime > data.duration)
        Stop();

    quad->UpdateWorld();
}

void Particle::Render()
{
    if (!isPlay) return;

    instanceBuffer->Set(1);

    quad->SetRender();

    DC->DrawIndexedInstanced(6, instances.size(), 0, 0, 0);
}

void Particle::Play(Vector2 pos)
{
    quad->Pos() = pos;
    UpdateParticleInfo();

    isPlay = true;
}

void Particle::Stop()
{
    isPlay = false;
}

void Particle::UpdateParticleInfo()
{
    color = data.startColor;
    lifeTime = 0.0f;

    for (UINT i = 0 ; i < data.count ; i++)
    {
        particleInfos[i].velocity = Random(data.minVelocity, data.maxVelocity);
        particleInfos[i].accelation = Random(data.minAccelation, data.maxAccelation);
        particleInfos[i].angularVelocity = Random(data.minAngularVelocity, data.maxAngularVelocity);
        particleInfos[i].speed = Random(data.minSpeed, data.maxSpeed);
        particleInfos[i].startTime = Random(data.minStartTime, data.maxStartTime);            
        particleInfos[i].velocity.Normalize();

        transforms[i].Pos() = { 0, 0 };
        transforms[i].Rot() = { 0, 0, 0 };
        transforms[i].Scale() = Random(data.minScale, data.maxScale);
    }
}

void Particle::LoadData(string file)
{
    BinaryReader* reader = new BinaryReader(file);

    wstring textureFile = reader->WString();
    quad = new Quad(textureFile);
    quad->SetVertexShader(L"Instancing.hlsl");
    quad->SetPixelShader(L"Instancing.hlsl");

    ParticleData* particleData = new ParticleData();
    reader->Byte((void**)&particleData, sizeof(ParticleData));

    data = *particleData;

    instances.resize(data.count);
    particleInfos.resize(data.count);
    transforms.resize(data.count);

    delete reader;
}
