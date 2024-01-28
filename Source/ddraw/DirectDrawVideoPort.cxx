/*
Copyright (c) 2024 Eugene Kirian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "DirectDrawSurface.hxx"
#include "DirectDrawVideoPort.hxx"

DirectDrawVideoPort::DirectDrawVideoPort(AgentConstructorParameters(DirectDrawVideoPort))
{
    AgentConstructor();
}

DirectDrawVideoPort::~DirectDrawVideoPort()
{
    AgentDestructor();
}

HRESULT DirectDrawVideoPort::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    const HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectDrawVideoPort, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(DirectDrawVideoPort, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG DirectDrawVideoPort::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectDrawVideoPort::Release()
{
    const ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Instructs the DirectDrawVideoPort object to write the next frame of video to a new surface.
HRESULT DirectDrawVideoPort::Flip(LPDIRECTDRAWSURFACE lpDDSurface, DWORD dwFlags)
{
    AttemptAccessAgentValue(DirectDrawSurface, lpDDSurface);

    return this->State.Self->Flip(lpDDSurface, dwFlags);
}

// Retrieves the minimum required overlay zoom factors and device limitations of a video port that uses the provided output pixel format.
HRESULT DirectDrawVideoPort::GetBandwidthInfo(LPDDPIXELFORMAT lpddpfFormat, DWORD dwWidth, DWORD dwHeight, DWORD dwFlags, LPDDVIDEOPORTBANDWIDTH lpBandwidth)
{
    return this->State.Self->GetBandwidthInfo(lpddpfFormat, dwWidth, dwHeight, dwFlags, lpBandwidth);
}

// Returns the current color control settings associated with the video port.
HRESULT DirectDrawVideoPort::GetColorControls(LPDDCOLORCONTROL lpColorControl)
{
    return this->State.Self->GetColorControls(lpColorControl);
}

// Retrieves the input formats supported by the DirectDrawVideoPort object.
HRESULT DirectDrawVideoPort::GetInputFormats(LPDWORD lpNumFormats, LPDDPIXELFORMAT lpFormats, DWORD dwFlags)
{
    return this->State.Self->GetInputFormats(lpNumFormats, lpFormats, dwFlags);
}

// Retrieves a list of output formats that the DirectDrawVideoPort object supports for a specified input format.
HRESULT DirectDrawVideoPort::GetOutputFormats(LPDDPIXELFORMAT lpInputFormat, LPDWORD lpNumFormats, LPDDPIXELFORMAT lpFormats, DWORD dwFlags)
{
    return this->State.Self->GetOutputFormats(lpInputFormat, lpNumFormats, lpFormats, dwFlags);
}

// Retrieves the polarity of a video field.
HRESULT DirectDrawVideoPort::GetFieldPolarity(LPBOOL lpbFieldPolarity)
{
    return this->State.Self->GetFieldPolarity(lpbFieldPolarity);
}

// Retrieves the line of video currently being written to the frame buffer.
HRESULT DirectDrawVideoPort::GetVideoLine(LPDWORD lpdwLine)
{
    return this->State.Self->GetVideoLine(lpdwLine);
}

// Retrieves the status of the video signal currently being presented to the video port.
HRESULT DirectDrawVideoPort::GetVideoSignalStatus(LPDWORD lpdwStatus)
{
    return this->State.Self->GetVideoSignalStatus(lpdwStatus);
}

// Sets the color control settings associated with the video port.
HRESULT DirectDrawVideoPort::SetColorControls(LPDDCOLORCONTROL lpColorControl)
{
    return this->State.Self->SetColorControls(lpColorControl);
}

// Sets the DirectDraw surface object to receive the stream of live video data and/or the vertical blank interval data.
HRESULT DirectDrawVideoPort::SetTargetSurface(LPDIRECTDRAWSURFACE lpDDSurface, DWORD dwFlags)
{
    AttemptAccessAgentValue(DirectDrawSurface, lpDDSurface);

    return this->State.Self->SetTargetSurface(lpDDSurface, dwFlags);
}

// Enables the hardware video port and starts the flow of video data into the currently specified surface.
HRESULT DirectDrawVideoPort::StartVideo(LPDDVIDEOPORTINFO lpVideoInfo)
{
    return this->State.Self->StartVideo(lpVideoInfo);
}

// Stops the flow of video-port data into the frame buffer.
HRESULT DirectDrawVideoPort::StopVideo()
{
    return this->State.Self->StopVideo();
}

// Updates parameters that govern the flow of video data from the video port to the DirectDrawSurface object.
HRESULT DirectDrawVideoPort::UpdateVideo(LPDDVIDEOPORTINFO lpVideoInfo)
{
    return this->State.Self->UpdateVideo(lpVideoInfo);
}

// Waits for VSYNC or until a given scan line is being drawn.
HRESULT DirectDrawVideoPort::WaitForSync(DWORD dwFlags, DWORD dwLine, DWORD dwTimeout)
{
    return this->State.Self->WaitForSync(dwFlags, dwLine, dwTimeout);
}