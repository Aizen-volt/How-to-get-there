# How-to-get-there
A rectangular map is given. Each field on the map can be:
- empty '.'
- part of a road '#'
- city entrance '*'
- part of city name 

Movement is allowed between fields adjacent by sides only. Additionally, selected cities are connected by one-way air connections. \
The task is to return the shortest path between two cities given in query:
> source destination [0/1]
#####
0 - return path length only \
1 - print every city passed on the way

## Implementation notes
- standard string class and other standard library containers cannot be used
- it is however recommended to implement them on your own

## Structures implemented
- graph (adjacency list implementation)
- priority queue (min-heap implementation)
- chained hash array
- queue (list implementation)
- linked list
- vector
- string

## Performance
Overall performance is quite satisfying e.g. finding connections between two amongst 2500 cities with 3123750 air connections took approximately 3.8 seconds (time for parsing map and adding connections to adjacency list included)

## Tests description
- 1.in  - example
- 2.in  - minimum
- 3.in  - label reading correctness
- 4.in  - correctness
- 5.in  - simple test on a grid
- 6.in  - small fan
- 7.in  - small path
- 8.in  - small complete graph
- 9.in  - large map, few cities
- 10.in - large map, few cities
- 11.in - fan, array implementation may not fit in time
- 12.in - spiral, recursion implementation of search overflows the stack
- 13.in - long path, array implementation may not fit in time
- 14.in - many edges

## Example
### Input:
```
20 20
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.
0
3
KIELCE KRAKOW 0
KRAKOW GDANSK 0
KRAKOW GDANSK 1
```
### Output:
```
5
40
40 KIELCE SZCZECIN
```
