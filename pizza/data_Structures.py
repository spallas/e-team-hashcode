input_file = 'b_little_bit_of_everything.in'

def data_structures(input_file):

    pizzas_descr = {}

    with open('b_little_bit_of_everything.in') as fin:
        lines = fin.readlines()

        lines = list(map(lambda x:x.split(), lines))

        n_pizzas = int(lines[0][0])
        nt2 = int(lines[0][1])
        nt3 = int(lines[0][2])
        nt4 = int(lines[0][3])

        for idx, line in enumerate(lines[1:]):
            pizzas_descr[idx] = set(line[1:])

    n_pizzas

    pizzas_descr

    ingredients = set().union(*pizzas_descr.values())

    n_ingredients = len(ingredients)


    import numpy as np
    overlaps = np.zeros([n_pizzas, n_pizzas], dtype=int)

    from itertools import product

    for i, j in product(range(n_pizzas), range(n_pizzas)):
        overlaps[i][j] = len(pizzas_descr[i].intersection(pizzas_descr[j]))

    return dict(overlaps=overlaps, pizzas_descr=pizzas_descr,ingredients=ingredients)
