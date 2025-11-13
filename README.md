# Poblational metaheuristic for Maximum Idependent Subset Problem

## Compilación:

```bash
$ g++ benchmark.cpp -O2 --static -o ant_colony_MISP
```

## Uso:

```bash
Usage: ./ant_colony_MISP -i <path> [-t <time_limit_seconds>] [-e <evaporation_rate>] [-d <deposit_amount>] [-p <proportional_deposit_type>] [-v]

Parameters:
  -i <path>                : Path to the graph instance/s file/directory (required)
  -t <time_limit_seconds>  : Maximum execution time in seconds (default: 10.00)
  -e <evaporation_rate>    : Pheromone evaporation rate (default: 0.010000)
  -d <deposit_amount>      : Pheromone deposit amount (default: 10.00)
  -p <deposit_type>        : Pheromone deposit type: 'proportional' or 'fixed' (default: proportional = true)
  -v                       : Verbose output for improvements during search (On single file case)
```

Ejemplo:
```bash
$ ./ant_colony_MISP -i /tmp/dataset_grafos_no_dirigidos/new_1000_dataset/erdos_n1000_p0c0.1_1.graph -t 60 -e 0.226 -d 100 -p proportional -v
```