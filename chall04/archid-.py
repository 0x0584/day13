# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    archid-.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/24 12:57:30 by archid-           #+#    #+#              #
#    Updated: 2024/11/24 15:26:43 by archid-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from typing import List
import os, sys

def read_grid(n: int) -> List[str]:
    grid: List[str] = []
    for _ in range(n):
        row = input()
        assert len(row) == n
        grid.append(row)
    return grid

def substitute_char_at_index(s: str, c: str, idx: int) -> str:
    return s[:idx] + c + s[idx+1:]

def grid_swap_cells(grid: List[str], row_idx: int, col_idx: int):
    s, t = grid[row_idx], grid[row_idx + 1]
    grid[row_idx] = substitute_char_at_index(s, t[col_idx], col_idx)
    grid[row_idx + 1] = substitute_char_at_index(t, s[col_idx], col_idx)

def advance_state(grid: List[str], row_idx) -> bool:
    state_changed: bool = False
    for col_idx in range(len(grid)):
        if grid[row_idx][col_idx] == '.' and grid[row_idx + 1][col_idx] == ' ':
            state_changed = True
            grid_swap_cells(grid, row_idx, col_idx)
    return state_changed

def loop(grid: List[str]):
    state_changed: bool = True
    while state_changed:
        for row_idx in range(0, len(grid) - 1):
            state_changed = advance_state(grid, row_idx)
            if state_changed:
                print()
                print("\n".join([row for row in grid]))

if __name__ == '__main__':
    N: int = int(input())
    assert 1 < N < 80
    grid = read_grid(N)
    if not os.isatty(sys.stdin.fileno()):
        print(N)
        print("\n".join([row for row in grid]))
    loop(grid)
