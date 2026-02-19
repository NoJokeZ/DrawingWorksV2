#include "ConsoleArtLibrary.h"


std::vector<std::wstring>* ConsoleArtLibrary::MenuHeader()
{
	static std::vector<std::wstring> value{
			LR"(╔════════════════════════════════════════════════════════════════════════════════════════════╗)",
			LR"(║  ________                      .__                  __      __             __              ║)",
			LR"(║  \______ \____________ __  _  _|__| ____    ____   /  \    /  \___________|  | __  ______  ║)",
			LR"(║   |    |  \_  __ \__  \\ \/ \/ /  |/    \  / ___\  \   \/\/   /  _ \_  __ \  |/ / /  ___/  ║)",
			LR"(║   |    `   \  | \// __ \\     /|  |   |  \/ /_/  >  \        (  <_> )  | \/    <  \___ \   ║)",
			LR"(║  /_______  /__|  (____  /\/\_/ |__|___|  /\___  /    \__/\  / \____/|__|  |__|_ \/____  >  ║)",
			LR"(║          \/           \/               \//_____/          \/                   \/     \/   ║)",
			LR"(╚════════════════════════════════════════════════════════════════════════════════════════════╝)"
	};
	return &value;
}

std::vector<std::wstring>* ConsoleArtLibrary::LoadingBarEmpty()
{
	static std::vector<std::wstring> value{
			LR"(╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗)",
			LR"(║                                                                                                      ║)",
			LR"(║                                                                                                      ║)",
			LR"(║                                                                                                      ║)",
			LR"(╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝)"
	};
	return &value;
}

std::vector<std::wstring>* ConsoleArtLibrary::DrawingControls()
{
	static std::vector<std::wstring> value{
			LR"(╔══════════════════════════════════════════════════════════════════════════════╗)",
			LR"(║                                                                              ║)",
			LR"(║                              Drawing Controls                                ║)",
			LR"(║                                                                              ║)",
			LR"(╠══════════════════════════════════════════════════════════════════════════════╣)",
			LR"(║ Controls:                                                                    ║)",
			LR"(║                                                                              ║)",
			LR"(║ LeftClick               ->     Draw white square/pixel                       ║)",
			LR"(║ RightClick              ->     Draw random colored square/pixel              ║)",
			LR"(║ LeftClick + LeftAlt     ->     Draw random colored circle                    ║)",
			LR"(║ LeftClick + LeftCtrl    ->     Draw random colored X                         ║)",
			LR"(║ LeftClick + Shift       ->     Draw random colored frame                     ║)",
			LR"(║ Escape                  ->     Back to menu                                  ║)",
			LR"(║                                                                              ║)",
			LR"(║ F1                      ->     Draw controls                                 ║)",
			LR"(║ F2                      ->     Clear console                                 ║)",
			LR"(║ F3                      ->     Fullscreen                                    ║)",
			LR"(║ F4                      ->     Windowed                                      ║)",
			LR"(╚══════════════════════════════════════════════════════════════════════════════╝)"
	};
	return &value;
}

std::vector<std::wstring>* ConsoleArtLibrary::LoadingBarFillElement()
{
	static std::vector<std::wstring> value{
			LR"(░)",
			LR"(░)",
			LR"(░)",
	};
	return &value;
}

std::vector<std::wstring>* ConsoleArtLibrary::Credits()
{
	static std::vector<std::wstring> value{
		LR"(░)",
		LR"(░)",
		LR"(░)",
	};
	return &value;
}

