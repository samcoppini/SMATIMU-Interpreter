#!/usr/bin/env python3

# A translator for converting brainfuck to SMATIMU
# Give it a valid BF file to it on the command line, and it will output
# the equivalent SMATIMU program

import re
import sys
from typing import *

ADD_LENGTH = 1540
SUB_LENGTH = 1540
OUT_LENGTH = 1541
RGT_LENGTH = 7
LFT_LENGTH = 7
WHL_LENGTH = 1540
CODE_START = 1000
TAPE_STEP = 6
TAPE_PADDING = 9

def is_int(maybe_int: str) -> bool:
    for c in maybe_int:
        if c < '0' or c > '9':
            return False
    return True

def brackets_balanced(bf_commands: str) -> bool:
    bracket_level = 0
    for c in bf_commands:
        if c == '[':
            bracket_level += 1
        elif c == ']':
            bracket_level -= 1
            if bracket_level < 0:
                return False
    if bracket_level > 0:
        return False
    return True

def strip_nonbf_commands(bf_file: str) -> str:
    commands = re.compile(r'[-><\+\.\[\]]')
    bf_commands = ''.join(commands.findall(bf_file))
    if not brackets_balanced(bf_commands):
        sys.stderr.write("Error! Unbalanced brackets in BF code!")
        sys.exit()
    return bf_commands

def generate_add_command_block(add_start: int) -> str:
    code = [f'{add_start}. Swap +0 with {add_start}.']
    code.append(f'{add_start + 1}. Set next_jmp to +N.')
    code.append(f'{add_start + 2}. Swap {add_start + 2} with next_jmp.')
    code.append(f'{add_start + 3}. Swap {add_start + 3} with code_ptr.')

    for i in range(1, 257):
        step = add_start + TAPE_STEP * i + 1
        new_val = ((i % 256) + 1) * TAPE_STEP
        code.append(f'{step - 1}. Swap {step + 3} with {step - 1}.')
        code.append(f'{step + 1}. Replace tape_ptr with Set N to {new_val}.')
        code.append(f'{step + 2}. Set N to {new_val}.')
        code.append(f'{step + 3}. Swap {step + 3} with {step - 1}.')

    return '\n'.join(code)

def generate_sub_command_block(sub_start: int) -> str:
    code = [f'{sub_start}. Swap +0 with {sub_start}.']
    code.append(f'{sub_start + 1}. Set next_jmp to +N.')
    code.append(f'{sub_start + 2}. Swap {sub_start + 2} with next_jmp.')
    code.append(f'{sub_start + 3}. Swap {sub_start + 3} with code_ptr.')

    for i in range(1, 257):
        step = sub_start + TAPE_STEP * i + 1
        new_val = (((i - 2) % 256) + 1) * TAPE_STEP
        code.append(f'{step - 1}. Swap {step + 3} with {step - 1}.')
        code.append(f'{step + 1}. Replace tape_ptr with Set N to {new_val}.')
        code.append(f'{step + 2}. Set N to {new_val}.')
        code.append(f'{step + 3}. Swap {step + 3} with {step - 1}.')

    return '\n'.join(code)

def generate_out_command_block(out_start: int) -> str:
    code = [f'{out_start}. Swap +0 with {out_start}.']
    code.append(f'{out_start + 1}. Set next_jmp to +N.')
    code.append(f'{out_start + 2}. Swap {out_start + 2} with next_jmp.')
    code.append(f'{out_start + 3}. Swap {out_start + 3} with code_ptr.')

    for i in range(1, 257):
        step = out_start + TAPE_STEP * i + 1
        diff = (i - 1) - (step + 2)
        code.append(f'{step - 1}. Swap {step + 4} with {step - 1}.')
        code.append(f'{step + 1}. Swap +0 through +2 with {diff} through {diff + 2}.')
        code.append(f'{step + 2}. Output this block\'s position.')
        code.append(f'{step + 3}. Swap -2 through +0 with {step + 1} through {step + 3}.')
        code.append(f'{step + 4}. Swap {step + 4} with {step - 1}.')

    return '\n'.join(code)

def generate_left_command_block(lft_start: int) -> str:
    code = [f'{lft_start}. Swap +0 with {lft_start}.']
    code.append(f'{lft_start + 1}. Set next_jmp to 0.')
    code.append(f'{lft_start + 2}. Swap {lft_start + 2} with tape_ptr.')
    code.append(f'{lft_start + 3}. Swap +0 with {lft_start + 3}.')
    code.append(f'{lft_start + 4}. Swap {lft_start + 5} with tape_ptr.')
    code.append(f'{lft_start + 6}. Swap {lft_start + 5} with tape_ptr.')
    code.append(f'{lft_start + 7}. Swap {lft_start + 7} with code_ptr.')
    return '\n'.join(code)

def generate_right_command_block(rgt_start: int) -> str:
    code = [f'{rgt_start}. Swap +0 with {rgt_start}.']
    code.append(f'{rgt_start + 1}. Set next_jmp to 4.')
    code.append(f'{rgt_start + 2}. Swap {rgt_start + 2} with tape_ptr.')
    code.append(f'{rgt_start + 3}. Swap +0 with {rgt_start + 3}.')
    code.append(f'{rgt_start + 4}. Swap {rgt_start + 5} with tape_ptr.')
    code.append(f'{rgt_start + 6}. Swap {rgt_start + 5} with tape_ptr.')
    code.append(f'{rgt_start + 7}. Swap {rgt_start + 7} with code_ptr.')

    return '\n'.join(code)

def generate_while_command_block(whl_start: int) -> str:
    code = [f'{whl_start}. Set +0 with {whl_start}.']
    code.append(f'{whl_start + 1}. Set next_jmp to +N.')
    code.append(f'{whl_start + 2}. Swap +0 with next_jmp.')

    false_step = whl_start + TAPE_STEP + 2
    code.append(f'{false_step}. Swap {whl_start + 2} with next_jmp.')
    code.append(f'{false_step + 1}. Set next_jmp to +1.')
    code.append(f'{false_step + 2}. Swap +0 with false_jmp.')

    true_step = whl_start + TAPE_STEP * 256 + 2
    code.append(f'{true_step}. Swap {whl_start + 2} with next_jmp.')
    code.append(f'{true_step + 1}. Set next_jmp to +1.')
    code.append(f'{true_step + 2}. Swap +0 with true_jmp.')

    return '\n'.join(code)

def generate_cells(lft_start: int, rgt_start: int, tape_start: int) -> str:
    code = []

    code.append(f'{tape_start}. Set N to {TAPE_STEP}.')
    code.append(f'{tape_start + 1}. Swap +0 with +next_jmp.')

    code.append(f'{tape_start + 2}. Set tape_ptr to -{TAPE_PADDING + 2}.')
    code.append(f'{tape_start + 3}. Swap -3 with {lft_start + 2}.')
    code.append(f'{tape_start + 4}. Swap +0 with {lft_start + 3}.')

    code.append(f'{tape_start + 5}. Swap +0 with +next_jmp.')
    code.append(f'{tape_start + 6}. Swap +0 through +13 with +100 through +113.')
    code.append(f'{tape_start + 7}. Replace -101 with Set tape_ptr to +{TAPE_PADDING - 6}.')
    code.append(f'{tape_start + 8}. Replace -101 with Swap -7 with {rgt_start + 2}.')
    code.append(f'{tape_start + 9}. Replace -101 with Swap +0 with {rgt_start + 3}.')
    code.append(f'{tape_start + 10}. Replace -101 with Set N to {TAPE_STEP}.')
    code.append(f'{tape_start + 11}. Replace -101 with Swap +0 with +next_jmp.')
    code.append(f'{tape_start + 12}. Replace -101 with Set tape_ptr to -{TAPE_PADDING + 2}.')
    code.append(f'{tape_start + 13}. Replace -101 with Swap -3 with {lft_start + 2}.')
    code.append(f'{tape_start + 14}. Replace -101 with Swap +0 with {lft_start + 3}.')
    code.append(f'{tape_start + 15}. Replace -101 with Swap +0 with +next_jmp.')
    code.append(f'{tape_start + 16}. Swap -10 through +3 with -101 through -88.')
    code.append(f'{tape_start + 17}. Swap {rgt_start + 2} with tape_ptr.')
    code.append(f'{tape_start + 18}. Set end_jmp to +100.')
    code.append(f'{tape_start + 19}. Swap +0 with {rgt_start}.')

    return '\n'.join(code)

def match_brackets(bf_commands: str) -> Dict[int, int]:
    loop_stack = []
    brackets = {}

    for i, c in enumerate(bf_commands):
        if c == '[':
            loop_stack.append(i)
        elif c == ']':
            brackets[loop_stack[-1]] = i
            brackets[i] = loop_stack.pop()

    return brackets

def get_instruction_positions(bf_commands: str) -> List[int]:
    positions = []
    cur_pos = CODE_START + 3
    for command in bf_commands:
        if command in '+-><.':
            positions.append(cur_pos)
            cur_pos += 3
        elif command in '[]':
            positions.append(cur_pos)
            cur_pos += 5
    positions.append(cur_pos)
    return positions

def generate_instructions(bf_commands: str, cmd_locs: List[int], add_start: int, sub_start: int, out_start: int, lft_start: int, rgt_start: int, whl_start: int, tape_start: int) -> str:
    code = [f'{CODE_START}. Set N to {TAPE_STEP}.']
    code.append(f'{CODE_START + 1}. Set tape_ptr to {tape_start}.')
    code.append(f'{CODE_START + 2}. Set end_jmp to {tape_start + 100}.')
	
    brackets = match_brackets(bf_commands)

    for i, c in enumerate(bf_commands):
        cur_index = cmd_locs[i]
        if c == '+':
            code.append(f'{cur_index}. Set code_ptr to {cur_index + 2}.')
            code.append(f'{cur_index + 1}. Swap +0 with {add_start}.')
            code.append(f'{cur_index + 2}. Swap {add_start + 3} with code_ptr.')
        elif c == '-':
            code.append(f'{cur_index}. Set code_ptr to {cur_index + 2}.')
            code.append(f'{cur_index + 1}. Swap +0 with {sub_start}.')
            code.append(f'{cur_index + 2}. Swap {sub_start + 3} with code_ptr.')
        elif c == '>':
            code.append(f'{cur_index}. Set code_ptr to {cur_index + 2}.')
            code.append(f'{cur_index + 1}. Swap +0 with {rgt_start}.')
            code.append(f'{cur_index + 2}. Swap {rgt_start + 7} with code_ptr.')
        elif c == '<':
            code.append(f'{cur_index}. Set code_ptr to {cur_index + 2}.')
            code.append(f'{cur_index + 1}. Swap +0 with {lft_start}.')
            code.append(f'{cur_index + 2}. Swap {lft_start + 7} with code_ptr.')
        elif c == '.':
            code.append(f'{cur_index}. Set code_ptr to {cur_index + 2}.')
            code.append(f'{cur_index + 1}. Swap +0 with {out_start}.')
            code.append(f'{cur_index + 2}. Swap {out_start + 3} with code_ptr.')
        elif c == '[' or c == ']':
            true_jmp = cur_index + 3
            false_jmp = cmd_locs[brackets[i]] + 3

            if c == ']':
                true_jmp, false_jmp = false_jmp, true_jmp

            code.append(f'{cur_index}. Set true_jmp to {true_jmp}.')
            code.append(f'{cur_index + 1}. Set false_jmp to {false_jmp}.')
            code.append(f'{cur_index + 2}. Swap +0 with {whl_start}.')
            code.append(f'{cur_index + 4}. Swap -1 with next_jmp.')

    code.append(f'{cmd_locs[-1]}. Swap {cmd_locs[-1]} with end_jmp.')
    return '\n'.join(code)

def translate_bf(bf_commands: str) -> str:
    code = []

    cmd_locs = get_instruction_positions(bf_commands)

    # The steps where the various subroutines begin, which immediately follow
    # the commands in the generated code
    add_start = cmd_locs[-1] + 1
    sub_start = add_start + ADD_LENGTH + 1
    out_start = sub_start + SUB_LENGTH + 1
    lft_start = out_start + OUT_LENGTH + 1
    rgt_start = lft_start + LFT_LENGTH + 1
    whl_start = rgt_start + RGT_LENGTH + 1

    # The step number of the first tape cell
    tape_start = whl_start + WHL_LENGTH + 1

    code.append(generate_instructions(bf_commands, cmd_locs, add_start, sub_start, out_start, lft_start, rgt_start, whl_start, tape_start))
    code.append(generate_add_command_block(add_start))
    code.append(generate_sub_command_block(sub_start))
    code.append(generate_out_command_block(out_start))
    code.append(generate_left_command_block(lft_start))
    code.append(generate_right_command_block(rgt_start))
    code.append(generate_while_command_block(whl_start))
    code.append(generate_cells(lft_start, rgt_start, tape_start))

    return '\n'.join(code)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        sys.stderr.write("Please provide a BF file to translate!")
        sys.exit()
    with open(sys.argv[1], 'r') as file:
        bf_commands = strip_nonbf_commands(file.read())
        print(translate_bf(bf_commands))
