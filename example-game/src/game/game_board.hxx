#include "game_objects/game_object.hxx"

constexpr uint8_t BOARD_WIDTH = 7;
constexpr uint8_t BOARD_HEIGHT = 7;
constexpr float BOARD_TILE_SPACE = 0.15f;
constexpr float BOARD_CENTER_OFFSET =
	BOARD_WIDTH % 2 == 0 ? (BOARD_WIDTH * BOARD_TILE_SPACE) / 2
					: (BOARD_WIDTH * BOARD_TILE_SPACE) / 2 - (BOARD_TILE_SPACE / 2);

class gem;

class game_board : public dreco::game_object
{
public:
	game_board();

	virtual void Init(dreco::game_world& _w) override;

	void CreateBoard();

private:
	gem* gems[BOARD_WIDTH][BOARD_HEIGHT] = {};
};