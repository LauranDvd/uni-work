import texttable as texttable

from src.service.service_error import MoveError


class Console:
    def __init__(self, service):
        self._service = service

    @staticmethod
    def col_no_to_char(n):
        trans = {0: 'A', 1: 'B', 2: 'C', 3: 'D', 4: 'E', 5: 'F', 6: 'G', 7: 'H'}
        return trans[n]

    def __print_board(self, cheat=False):
        table = texttable.Texttable()
        table.add_row([x for x in range(9)])
        for i in range(8):
            row = [Console.col_no_to_char(i)]
            for j in range(8):
                row.append(self._service.get_cell_nice(i, j, cheat=cheat))
            table.add_row(row)
        print(table.draw())

    def __start_game(self):
        self._service.start_game()

    def __process_command(self, cmd) -> int:  # return win/lose status
        if len(cmd) >= 4 and cmd[:4] == "warp":
            try:
                over = self._service.warp(cmd[5:])
                if over:  # gameover from warp --> lose
                    return -1
            except MoveError as e:
                print("ERROR:", e)
        elif len(cmd) >= 4 and cmd[:4] == "fire":
            try:
                over = self._service.fire(cmd[5:])
                if over:  # gameover from fire --> win
                    return 1
            except MoveError as e:
                print("ERROR:", e)
        elif cmd == "cheat":
            self.__print_board(cheat=True)
        else:
            print("ERROR: No such command")

        return 0

    @staticmethod
    def __end_game(who):
        print("Game over")
        if who == 1:
            print("You won.")
        else:
            print("You lost. There was a Blingon cruiser there")

    def run(self):
        self.__start_game()
        while True:
            self.__print_board()
            cmd = input(">")
            over_status = self.__process_command(cmd)  # it will treat the errors there
            if over_status != 0:
                Console.__end_game(over_status)
                break
