#include "AstroidFighter.h"
//#include "MessageMinesweeper.h"


using namespace std;


int main(int argc, char* argv[])
{
	game::AstroidFighter astroidFighterGame;
	astroidFighterGame.Start();
	/*bool playing = true;
	while (playing) {
		game::MessageMinesweeper mms;
		playing = mms.Start();
		std::cout << "returned";
	}
	*/
	return 0;
}
