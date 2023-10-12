#pragma once

class RenderTarget
{
public:
    RenderTarget(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
    ~RenderTarget();

    void Set(Float4 clearColor = Float4(1, 1, 1, 1));

    ID3D11ShaderResourceView* GetSRV() { return srv; }

private:
    void CreateRTVTexture();
    void CreateRTV();
    void CreateSRV();
    void CreateProjection();

private:
    UINT width, height;

    ID3D11Texture2D* rtvTexture;
    ID3D11RenderTargetView* rtv;
    ID3D11ShaderResourceView* srv;

    MatrixBuffer* projectionBuffer;
};