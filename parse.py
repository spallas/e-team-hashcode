from pathlib import Path


def parse(file_path):
    with Path(file_path).open('r') as f:
        a, b, c = f.readline().strip().split(' ')
        for line in f:
            d, e, f = line.strip().split(' ')

        print(a, b, c, d, e, f)
