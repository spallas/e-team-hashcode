from pathlib import Path


def parse(file_path):
    with Path(file_path).open('r') as f:
        line = f.readline().strip().split(' ')
        n_pizzas = line.pop(0)
        teams = {}  # key = num members, val = num teams
        for i, n_teams in enumerate(line):
            teams[i+2] = int(n_teams)

        pizzas = {}
        for i, line in enumerate(f):
            line = line.strip().split(' ')
            n_ingredients = line.pop(0)
            pizzas[i] = line
        return teams, pizzas
