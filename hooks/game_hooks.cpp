/// This is where the magic happens; program your plug-in's core behavior here.

#include "game_hooks.h"
#include <graphics/graphics.h>
#include <SCBW/api.h>
#include <SCBW/scbwdata.h>
#include <SCBW/ExtendSightLimit.h>
#include "psi_field.h"
#include <cstdio>
#include <SCBW/UnitFinder.h>


using namespace std;

//sprawdza czy jednostka jest nieaktywnym robotnikiem
bool unitIsAnIdleWorker(const CUnit* const unit)
{
	const u16 unitId = unit->id;
	if ((unitId == UnitId::drone
		|| unitId == UnitId::probe
		|| unitId == UnitId::scv)
		&& (unit->mainOrderId == OrderId::Stop))
	{
		return true;
	}
	return false;
}



//zlicza i wyswietla nieaktywnych robotnikow
void ShowIdleWorkers(CUnit* const unit)

{
	scbw::UnitFinder IdleWorkerFinder;
	IdleWorkerFinder.search(9000, 9000, 9000, 9000);
	if (unitIsAnIdleWorker(unit))
	{
		int IdleWorkersCount = IdleWorkerFinder.getUnitCount();
		const string IdleWorkersText = to_string(IdleWorkersCount) + " nieaktywnych robotnikow";
		graphics::drawText(500, 20, IdleWorkersText,
			graphics::FONT_MEDIUM, graphics::ON_SCREEN);
		return;

	}
}

namespace hooks {

	/// This hook is called every frame; most of your plugin's logic goes here.
	bool nextFrame() {
		if (!scbw::isGamePaused()) { //If the game is not paused
			scbw::setInGameLoopState(true); //Needed for scbw::random() to work
			graphics::resetAllGraphics();
			hooks::updatePsiFieldProviders();
			
			//This block is executed once every game.
			if (*elapsedTimeFrames == 0) {
				//Write your code here

			}

			//Loop through all visible units in the game.
			for (CUnit *unit = *firstVisibleUnit; unit; unit = unit->link.next) {
				//Write your code here
				ShowIdleWorkers(unit);
			}

			scbw::setInGameLoopState(false);
		}
		return true;
	}

	bool gameOn() {
		return true;
	}

	bool gameEnd() {
		return true;
	}

} //hooks
