from domain.move_error import MoveError


class Console:
    def __init__(self, service):
        self._service = service

    def __print_board(self, is_final=False):
        if is_final:  # where there's 4 connected, write them as [x] or [0] (with brackets)
            special_print = self._service.get_special_print_cells()

        for i in range(self._service.board_lines):
            for j in range(self._service.board_cols):
                if is_final and special_print[i][j]:
                    print("[" + self._service.get_cell_value_nice(i, j) + "]", end='')
                else:
                    if j > 0:
                        before = " "
                    else:
                        before = ""
                    print(before + self._service.get_cell_value_nice(i, j), end='')
            print("")
        for i in range(self._service.board_cols):  # ___...
            print("__", end='')
        print("")
        for i in range(self._service.board_cols):  # 123...
            print(str(i + 1) + " ", end='')
        print("\n")

    def __move(self, col):
        col = int(col) - 1
        self._service.move_user(col)

    def __computer_move(self):
        self._service.computer_move()

    def __is_full(self):
        return self._service.is_full()

    def __is_winner(self):
        return self._service.is_winner()

    def __end_game(self, winner):
        self.__print_board(True)
        if winner == "user":
            print("You won!")
        elif winner == "draw":
            print("Draw")
        else:
            print("You lost")
        print("")

    def __play_game(self):
        self._service.init_board()
        while True:
            self.__print_board()
            print("Enter your next move (indexing from 1)")
            col = input("Column: ")
            try:
                self.__move(col)
            except ValueError:
                print("Please enter numbers")
            except MoveError as e:
                print(e)
            else:
                if self.__is_winner():
                    self.__end_game("user")
                    break
                if self.__is_full():
                    self.__end_game("draw")
                    break
                self.__computer_move()
                if self.__is_winner():
                    self.__end_game("computer")
                    break
                elif self.__is_full():
                    self.__end_game("draw")
                    break

    def run_main(self):
        while True:
            print("[1] New game")
            print("[2] Exit")

            opt = input(">")
            try:
                opt = int(opt)
            except ValueError:
                print("Please enter a number")
            else:
                if opt == 1:
                    self.__play_game()
                elif opt == 2:
                    break
                else:
                    print("Invalid option")
