import sys
from collections import deque

RIGHT = ">"
DOWN = "v"
LEFT = "<"
UP = "^"

MAZE_RIGHT_HANDED = "R"
MAZE_LEFT_HANDED = "L"

class Cell:
    def __init__(self, h, w, value):
        self.h = h
        self.w = w
        self.value = value
        self.stepped_on_count = 0

    def step_on(self):
        self.stepped_on_count += 1

    def total_steps(self):
        return self.stepped_on_count

    def current_position_delta(self, dh=0, dw=0):
        return "{0} {1}".format(self.h + dh, self.w + dw)


class Cursor:
    def __init__(self, start_pos, facing):
        self.current_pos = start_pos
        self.finish_line = start_pos
        self.facing = facing
        self.arrived = False
        self.maze_side = None
        self.first_move = True

    def set_maze_side(self, side):
        self.maze_side = side

    def complete_maze(self):
        global game_map
        while True:
            if self.move_onto_next() == "Trapped":
                return
            if self.arrived:
                return

            game_map[self.current_pos].step_on()
            self.first_move = False

    def move_onto_next(self):
        if self.current_pos == self.finish_line and not self.first_move:
            self.arrived = True
            return

        if self.facing == RIGHT:
            if self.maze_side == MAZE_RIGHT_HANDED:
                return self.move_onto_next_right_handed(0)
            elif self.maze_side == MAZE_LEFT_HANDED:
                return self.move_onto_next_left_handed(0)
        elif self.facing == DOWN:
            if self.maze_side == MAZE_RIGHT_HANDED:
                return self.move_onto_next_right_handed(1)
            elif self.maze_side == MAZE_LEFT_HANDED:
                return self.move_onto_next_left_handed(-1)
        elif self.facing == LEFT:
            if self.maze_side == MAZE_RIGHT_HANDED:
                return self.move_onto_next_right_handed(2)
            elif self.maze_side == MAZE_LEFT_HANDED:
                return self.move_onto_next_left_handed(-2)
        elif self.facing == UP:
            if self.maze_side == MAZE_RIGHT_HANDED:
                return self.move_onto_next_right_handed(3)
            elif self.maze_side == MAZE_LEFT_HANDED:
                return self.move_onto_next_left_handed(-3)

    def move_onto_next_right_handed(self, index_shift):
        sides = deque([DOWN, RIGHT, UP, LEFT])
        sides.rotate(index_shift)
        for side in sides:
            cell = self.check_for(side)
            if cell:
                self.current_pos = cell
                return
        return "Trapped"

    def move_onto_next_left_handed(self, index_shift):
        sides = deque([UP, RIGHT, DOWN, LEFT])
        sides.rotate(index_shift)
        for side in sides:
            cell = self.check_for(side)
            if cell:
                self.current_pos = cell
                return
        return "Trapped"

    def check_for(self, side):
        global game_map
        if side == UP:
            new_pos = game_map[self.current_pos].current_position_delta(-1,0)
            return self.check_value(side, new_pos)
        elif side == DOWN:
            new_pos = game_map[self.current_pos].current_position_delta(1,0)
            return self.check_value(side, new_pos)
        elif side == RIGHT:
            new_pos = game_map[self.current_pos].current_position_delta(0,1)
            return self.check_value(side, new_pos)
        elif side == LEFT:
            new_pos = game_map[self.current_pos].current_position_delta(0,-1)
            return self.check_value(side, new_pos)

    def check_value(self, side, pos):
        global game_map
        if pos in game_map:
            if game_map[pos].value == '#':
                return False
            else:
                self.facing = side
                return pos


game_map = {}
cursor = None

width, height = [int(i) for i in input().split()]
for i in range(height):
    line = list(input())
    for j, value in enumerate(line):
        cell = Cell(i, j, value)
        if value in [RIGHT, DOWN, LEFT, UP]:
            cursor = Cursor(cell.current_position_delta(0,0), value)
        game_map["{0} {1}".format(i,j)] = cell
side = input()
cursor.set_maze_side(side)
cursor.complete_maze()
for i in range(height):
    for j in range(width):
        pos = "{0} {1}".format(i, j)
        if game_map[pos].value == '#':
            print(game_map[pos].value, end = '')
        else:
            print(game_map[pos].total_steps(), end = '')
    print('')
