#pragma once
class GLWindowInterface
{
public:
	GLWindowInterface();
	virtual ~GLWindowInterface();
	virtual void SetTitle(const char * title) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual int Execute() = 0;

};

