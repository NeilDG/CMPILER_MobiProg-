#include "AppWindow.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "UIManager.h"
#include "Debug.h"
#include <sstream>
#include <time.h>
#include <antlr4-runtime.h>
#include "CLexer.h"
#include "CParser.h"
#include "CListener.h"

using namespace antlr4;

static float f = 0.0f;
static int counter = 0;

AppWindow* AppWindow::sharedInstance = NULL;

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
}

void AppWindow::onCreate()
{
	Window::onCreate();
	srand(time(NULL));

	std::cout << "On create \n";
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
	DeviceContext* deviceContext = graphEngine->getImmediateContext();
	deviceContext->clearRenderTargetColor(this->swapChain, 0, 0.5, 0.5, 1);

	RECT windowRect = this->getClientWindowRect();
	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;

	deviceContext->setViewportSize(width, height);

	//default updates on systems
	UIManager::getInstance()->drawAllUI();

	graphEngine->getSwapChain()->present(true); //NOTE: Called once per screen refresh.
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	this->swapChain->release();

	GraphicsEngine::destroy();
	Debug::destroy();

	// IMGUI Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	std::cout << "On destroy \n";
}

void AppWindow::initializeEngine()
{
	Debug::initialize();
	GraphicsEngine::initialize();
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

	this->swapChain = GraphicsEngine::getInstance()->getSwapChain();
	RECT windowRect = this->getClientWindowRect();
	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;
	std::cout << "Window rect width: " << width << "\n";
	std::cout << "Window rect height: " << height << "\n";

	this->swapChain->init(this->getWindowHandle(), width, height);
}

void AppWindow::createInterface()
{
	UIManager::initialize(this->windowHandle);
	std::stringstream buffer;
	buffer << "Successfully initialized MobiProg++ runtime environment! \n";
	Debug::Log(buffer.str());

	ANTLRInputStream input(buffer);
	CLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	CParser parser(&tokens);

	tree::ParseTree* tree = parser.primaryExpression();
	tree::ParseTreeWalker::DEFAULT.walk(NULL, tree);
}


AppWindow::AppWindow():Window()
{
	this->createWindow();
}

AppWindow::~AppWindow()
{
	Window::~Window();
}

