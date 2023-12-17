#include <random>
#include <vector>

class game {
    private:
        int dimensions; // default game is 4x4, we can make it larger if wanted
        std::vector<std::vector<int>> gameBoard; // [[a_11,a_12,...,a_1n],...,[a_n1,a_n2,...a_nn]], inner arrays are HORIZONTAL
        std::random_device rd; // Non-deterministic random number generator (used once to seed mt19937)
        std::mt19937 g;       // Pseudo-random number generator

    public:
        explicit game(int default_dim = 4);

        ~game();
        game(const game & other);

        int get_dimensions() const;
        std::vector<std::vector<int>> get_board() const;
        bool compare_board(std::vector<std::vector<int>> board1, std::vector<std::vector<int>>board2);

        // order for each turn: spawn_block, game_over?, up/down/left/right
        void spawn_block(); // blocks spawn randomly (first turn spawn 2, other turns spawn 1, block value = 2,4)
        bool game_over(); // no possible moves

        std::vector<int> merge_single_line(const std::vector<int> & line);

        bool up();
        bool down();
        bool left();
        bool right();
};

std::ostream & operator<<(std::ostream & out, const game & game);
//friend std::istream & opeartor>>(std::istream & in, game & game); // input format [[a_11,a_12,...,a_1n],...,[a_n1,a_n2,...a_nn]]
bool operator !=(const game & game1, const game & game2); // MUST HAVE SAME DIMENSIONS
