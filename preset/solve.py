import argparse
from pathlib import Path

from parse import parse


def solve_smart(data_structure):
    solution = []

    return solution


def solve_stupid(data_structure):
    solution = []

    return solution


def solve_greedy(data_structure):
    solution = []

    return solution


def write_solution(problem_name, solution_items):
    with (Path('outputs') / (problem_name + '.out')).open('w') as f:
        for i in solution_items:
            # elaborate item
            print(i, file=f)

# ==================================================================


SOLVER_LIBRARY = {
    'greedy': solve_greedy,
    'stupid': solve_stupid,
    'smart': solve_smart
}


def main():
    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group()
    group.add_argument('-i', type=str)
    group.add_argument('-a', action='store_true')
    parser.add_argument('-s', type=str, choices=SOLVER_LIBRARY.keys(), required=True)
    args = parser.parse_args()

    solve = SOLVER_LIBRARY[args.s]

    if args.a:
        inputs = Path('inputs')
        for input_file in inputs.iterdir():
            if input_file.is_file():
                data_structure = parse(input_file)
                solution = solve(data_structure)
                write_solution(input_file.stem, solution)
    else:
        input_file = Path(args.i)
        data_structure = parse(input_file)
        solution = solve(data_structure)
        write_solution(input_file.stem, solution)


if __name__ == '__main__':
    main()
