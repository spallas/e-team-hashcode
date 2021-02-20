import argparse
from collections import namedtuple
from itertools import combinations
from pathlib import Path

from parse import parse
import numpy as np

Delivery = namedtuple("Delivery", ['people', 'pizza_indices'])


def best_pizzas(pizza_list, look_ahead_steps, o):
    look_ahead_steps = min(len(pizza_list), look_ahead_steps)
    pizza_subset = []
    for indices in combinations(range(look_ahead_steps), o):
        overlap = set(pizza_list[indices[0]][1])
        for i in indices[1:]:
            overlap &= set(pizza_list[i][1])
        pizza_subset.append((indices, len(overlap)))
    bests = max(pizza_subset, key=lambda x: x[1])[0]
    return bests


def solve_smart(data_structure):
    look_ahead_steps = 4
    teams, pizzas = data_structure
    pizzas = [(p_i, ingredients) for p_i, ingredients in pizzas.items()]
    pizza_list = sorted(pizzas, key=lambda x: len(x[1]), reverse=True)
    order_teams = [4, 3, 2]
    deliveries = []

    for o in order_teams:
        num_teams = teams[o]
        for i in range(num_teams):
            if len(pizza_list) < o:
                break
            pizzas = []
            bests = best_pizzas(pizza_list, look_ahead_steps, o)
            for j in sorted(bests, reverse=True):
                pizzas.append(pizza_list[j][0])
                del pizza_list[j]
            delivery = Delivery(people=o, pizza_indices=pizzas)
            deliveries.append(delivery)

    solution = [len(deliveries)]
    for d in deliveries:
        s = str(d.people) + ' ' + ' '.join(map(str, d.pizza_indices))
        solution.append(s)
    return solution


def solve_stupid(data_structure):
    teams, pizzas = data_structure
    pizza_list = [(p_i, len(ingredients)) for p_i, ingredients in pizzas.items()]
    pizza_list = sorted(pizza_list, key=lambda x: x[1], reverse=True)
    order_teams = [2, 3, 4]
    deliveries = []

    for o in order_teams:
        num_teams = teams[o]
        for i in range(num_teams):
            pizzas_left = len(pizza_list)
            if pizzas_left < o:
                break
            pizzas = [pizza_list.pop(0)[0] for _ in range(o)]
            delivery = Delivery(people=o, pizza_indices=pizzas)
            deliveries.append(delivery)

    solution = [len(deliveries)]
    for d in deliveries:
        s = str(d.people) + ' ' + ' '.join(map(str, d.pizza_indices))
        solution.append(s)
    return solution


def solve_greedy(data_structure):
    teams, pizzas = data_structure
    solution = []  #
    deliveries = []
    order_teams = [2, 3, 4]
    M = np.zeros(shape=(len(pizzas), len(pizzas), 2), dtype=np.int64)
    for p, ingredients in pizzas.items():
        for pp, ingredients_ in pizzas.items():
            M[p, pp][0] = len(set(ingredients) & set(ingredients_))
            M[p, pp][1] = pp
    pizza_list = [(p_i, len(ingredients)) for p_i, ingredients in pizzas.items()]
    pizza_list = sorted(pizza_list, key=lambda x: x[1], reverse=True)

    # pizza_used = [0 for _ in range((len(pizza_list)))]

    for o in order_teams:
        num_teams = teams[o]
        for i in range(num_teams):
            print(f"\r{i}", end='', flush=True)
            pizzas_left = len(pizza_list)
            if pizzas_left < o:
                break
            delivery = Delivery(people=o, pizza_indices=[pizza_list[0][0]])
            ppp = pizza_list.pop(0)
            M = np.delete(M, axis=1, obj=(np.argmax(M[0, :, 1] == ppp[0])))

            for oo in range(o - 1):
                last_best = delivery.pizza_indices[-1]
                row = M[int(last_best), :, :]

                min_j = row[np.argmin(row, axis=0)[0], 1]

                delivery.pizza_indices.append(min_j)
                del_i = 0
                for k, pizza in enumerate(pizza_list):
                    if pizza[0] == min_j:
                        del_i = k
                        break
                pizza_list.pop(del_i)
                del_i = np.argmin(row, axis=0)[0]
                M = np.delete(M, axis=1, obj=del_i)
            deliveries.append(delivery)
    print()
    solution.append(len(deliveries))
    for d in deliveries:
        s = ''
        s += str(d.people) + ' ' + ' '.join(map(str, d.pizza_indices))
        solution.append(s)

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
        for input_file in sorted(inputs.iterdir(), key=lambda x: x.name):
            print(input_file.name)
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
