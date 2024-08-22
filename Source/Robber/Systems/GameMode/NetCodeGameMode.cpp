#include "NetCodeGameMode.h"
#include "Robber/Entities/Player/Runtime/RuntimePlayerController.h"

ANetCodeGameMode::ANetCodeGameMode()
{
	PlayerControllerClass = ARuntimePlayerController::StaticClass();
}
