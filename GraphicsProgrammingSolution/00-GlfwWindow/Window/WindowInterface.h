#pragma once
class WindowInterface
{
public:
	WindowInterface();
	virtual ~WindowInterface();
	virtual void SetTitle(const char * title) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual int Execute() = 0;
protected:
	virtual void SwapBuffers() = 0;
};

