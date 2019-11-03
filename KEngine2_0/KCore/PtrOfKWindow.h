#pragma once





class KWindow;
class PtrOfKWindow
{
protected:
	PtrOfKWindow() : pKWindow(nullptr){};
	PtrOfKWindow(const PtrOfKWindow& _Other) = delete;
	PtrOfKWindow(const PtrOfKWindow&& _Other) = delete;
	void operator=(const PtrOfKWindow& _Other) = delete;
	~PtrOfKWindow() {};



private:
	KWindow* pKWindow;

public:
	inline KWindow* kwindow()
	{
		return pKWindow;
	}

	inline void kwindow(KWindow* _Other)
	{
		pKWindow = _Other;
	}

};

