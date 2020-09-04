#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include <vector>

class AppWindow : public Window
{
public:
	static AppWindow* getInstance();
	static void initialize();
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	void initializeEngine();
	void createInterface();

private:
	AppWindow();
	~AppWindow();
	AppWindow(AppWindow const&) {};             // copy constructor is private
	AppWindow& operator=(AppWindow const&) {};  // assignment operator is private*/
	static AppWindow* sharedInstance;

	SwapChain* swapChain;

	float ticks = 0.0f;
	float CHANGE_DELAY = 1.0f;

	float deltaPos = 0.0f;
	bool shouldRotate = false;

};

