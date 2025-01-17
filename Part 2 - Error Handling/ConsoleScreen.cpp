#include "ConsoleScreen.h"
#include <sstream>
void ConsoleScreen::appendText(String text)
{
	std::stringstream buffer;
	buffer << this->lineCount << " " << text << '\n';

	this->textLog->appendf(buffer.str().c_str());
	this->lineCount++;
}

ConsoleScreen::ConsoleScreen(): AUIScreen("ConsoleScreen")
{
	this->textLog = new ImGuiTextBuffer();
}

ConsoleScreen::~ConsoleScreen()
{
	delete this->textLog;
}

void ConsoleScreen::drawUI()
{
	ImGui::Begin("Console", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(1400, 890));
	if (ImGui::Button("Clear")) { this->textLog->clear(); this->lineCount = 0; }
	ImGui::TextUnformatted(this->textLog->begin(), this->textLog->end());
	ImGui::End();
}
