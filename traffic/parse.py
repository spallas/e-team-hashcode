from dataclasses import dataclass
from pathlib import Path
from typing import List, Dict


@dataclass
class Street:
    name: str
    a: int
    b: int
    duration: int

    def __hash__(self):
        return hash(self.name)


@dataclass
class Intersection:
    id_: int
    in_streets: List[Street]
    out_streets: List[Street]

    def __hash__(self):
        return hash(self.id_)


@dataclass
class Car:
    id_: int
    path: List[Street]

    def __hash__(self):
        return hash(self.id_)


def parse(file_path):
    with Path(file_path).open('r') as f:
        duration, intersections, streets, cars, points = f.readline().strip().split(' ')
        duration, intersections, streets, cars, points = map(int, [duration, intersections, streets, cars, points])
        street_map: Dict[str, Street] = {}
        inters_map: Dict[int, Intersection] = {}
        car_map: Dict[int, Car] = {}
        path_map: Dict[str, List[int]] = {}  # street_id, car_id

        for line in f:
            if streets > 0:
                streets -= 1
                a, b, name, duration = line.strip().split(' ')
                a, b, duration = int(a), int(b), int(duration)
                s = Street(name, a, b, duration)
                street_map[name] = s
                if b in inters_map:
                    inters_map[b].in_streets.append(s)
                else:
                    inters_map[b] = Intersection(b, in_streets=[s], out_streets=[])
                if a in inters_map:
                    inters_map[a].out_streets.append(s)
                else:
                    inters_map[a] = Intersection(a, in_streets=[], out_streets=[s])
            else:
                cars -= 1
                path_len, path = line.strip().split(' ', maxsplit=1)
                path = path.split(' ')
                path_ = []
                for name in path:
                    path_.append(street_map[name])
                    path_map.setdefault(name, []).append(cars)
                car_map[cars] = Car(cars, path_)

        return street_map, inters_map, car_map, path_map, duration
