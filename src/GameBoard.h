#include <array>
#include <string>

namespace TicTacToe {

enum class PlayerToken { One, Two };

class GameBoard {
public:
  enum class Cell { Empty, PlayerOneToken, PlayTwoToken };

  void PlaceToken(PlayerToken p, int row, int col);

  bool IsPositionOpen(int row, int col);
  bool IsBoardFull();
  int GetTokenCountInRow(PlayerToken p, int row);
  int GetTokenCountInCol(PlayerToken p, int col);
  int GetTokenCountInDiag(PlayerToken p, bool topLeftBottomRightDiag);
  std::string ToString();

private:
  std::string CellToString(int row, int col);

  std::array<std::array<Cell, 3>, 3> m_board{};
  int m_playCount{};
};

} // namespace TicTacToe
