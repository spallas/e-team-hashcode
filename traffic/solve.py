import argparse
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List
from math import gcd

from parse import parse, Intersection, Street


@dataclass
class Schedule:
    inters: Intersection
    lights: Dict[Street, int]


def solve_smart(data_structure):
    solution = []

    return solution


def solve_stupid(data_structure):
    street_map, inters_map, car_map, path_map = data_structure
    solution: List[Schedule] = []

    for inters_id, inters in inters_map.items():
        lights = {}
        for s in inters.in_streets:
            lights[s] = 1  # seconds

        sched = Schedule(inters, lights)
        solution.append(sched)

    return solution


def solve_greedy(data_structure):
    street_map, inters_map, car_map, path_map = data_structure
    solution: List[Schedule] = []

    for inters_id, inters in inters_map.items():
        lights = {}
        densities = []
        for s in inters.in_streets:
            if s.name in path_map:
                densities.append(len(path_map[s.name]))
            else:
                densities.append(1)
        d_sum = sum(densities)
        densities = [round(100000 * d/d_sum) for d in densities]
        d_gcd = gcd(*densities)
        light_duration = [d//d_gcd for d in densities]
        for i, s in enumerate(inters.in_streets):
            lights[s] = light_duration[i]

        sched = Schedule(inters, lights)
        solution.append(sched)

    return solution


def write_solution(problem_name, solution_items):
    with (Path('outputs') / (problem_name + '.out')).open('w') as f:
        print(len(solution_items), file=f)
        for schedule in solution_items:
            print(schedule.inters.id_, file=f)
            print(len(schedule.lights), file=f)
            for street, light_duration in schedule.lights.items():
                print(f"{street.name} {light_duration}", file=f)
    return

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
