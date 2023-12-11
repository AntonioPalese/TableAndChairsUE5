#include "TableAndChairsGameModeBase.h"
#include "TCCameraController.h"


ATableAndChairsGameModeBase::ATableAndChairsGameModeBase()
{
	PlayerControllerClass = ATCCameraController::StaticClass();
}
