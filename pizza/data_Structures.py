input_file = 'b_little_bit_of_everything.in'

from tqdm import tqdm

def data_structures(input_file):
    pizzas_descr = {}

    with open(input_file) as fin:
        lines = fin.readlines()

        lines = list(map(lambda x: x.split(), lines))

        n_pizzas = int(lines[0][0])

        print(n_pizzas)
        nt2 = int(lines[0][1])
        nt3 = int(lines[0][2])
        nt4 = int(lines[0][3])

        for idx, line in enumerate(lines[1:]):
            pizzas_descr[idx] = set(line[1:])

    ingredients = set().union(*pizzas_descr.values())

    n_ingredients = len(ingredients)

    import numpy as np
    overlaps = np.zeros([n_pizzas, n_pizzas], dtype=int)

    from itertools import product

    for block in tqdm(range(int(n_pizzas / 100))):

        offset = block * 100
        for i, j in product(range(100), range(100)):
            overlaps[offset + i][offset + j] = len(pizzas_descr[offset + i].intersection(pizzas_descr[offset + j]))

    return dict(overlaps=overlaps, pizzas_descr=pizzas_descr, ingredients=ingredients)
