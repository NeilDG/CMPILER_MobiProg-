#include "MenuScreen.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <iostream>
#include "GraphicsEngine.h"
#include "VertexShader.h"

MenuScreen::MenuScreen(): AUIScreen("MenuScreen")
{
	this->openSceneDialog = new ImGui::FileBrowser();
	this->openSceneDialog->SetTitle("Open File");
	this->openSceneDialog->SetTypeFilters({ ".mobiprog"});

	this->saveSceneDialog = new ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);
	this->saveSceneDialog->SetTitle("Save File");
	this->saveSceneDialog->SetTypeFilters({ ".mobiprog" });
}

MenuScreen::~MenuScreen()
{
	delete this->openSceneDialog;
	delete this->saveSceneDialog;
}

void MenuScreen::drawUI()
{

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open..", "Ctrl+O")) {
				this->openSceneDialog->Open();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) {
				this->saveSceneDialog->Open();
			}
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {
				this->saveSceneDialog->Open();
			}
			if (ImGui::MenuItem("Exit Editor", "Ctrl+W")) {/*Do something */ }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	this->openSceneDialog->Display();
	this->saveSceneDialog->Display();

	if (this->saveSceneDialog->HasSelected())
	{
		
		this->saveSceneDialog->ClearSelected();
		this->saveSceneDialog->Close();
	}
	
	else if (this->openSceneDialog->HasSelected()) {

		this->openSceneDialog->ClearSelected();
		this->openSceneDialog->Close();
	}
}
