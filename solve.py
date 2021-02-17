import argparse
from pathlib import Path

from parse import parse


def solve(data_structure):
    solution = []

    return solution


def write_solution(problem_name, solution_items):
    with (Path('outputs') / (problem_name + '.out')).open('w') as f:
        for i in solution_items:
            # elaborate item
            print(i, file=f)


def main():
    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group()
    group.add_argument('-i', type=str)
    group.add_argument('-a', action='store_true')
    args = parser.parse_args()

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
