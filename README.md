# u6938702 COMP 3600 Project - Calculating escape routes from a fire and determining risk of COVID.

## Usage
The following instructions have been tested on a Debain distribution of Linux.

To compile the project
```
g++ -std=c++11 main.cpp -o escape_planner -lboost_program_options
```
Note you may also need to update your path variable to the folder you are working in so that it can find the `escape_planner` command. On most linux systems this can be done by setting `PATH="$HOME/path/to/file:$PATH"`.

To calculate the escape paths for *all* entities in a building
```
escape_planner --calculate-paths --building-file=tests/buildings/test-1.ttl --person-file=tests/buildings/test-1.ttl --escape-file=escape.ttl
```

To calculate the risk of covid given the escape paths
```
escape_planner --calculate-risk --building-file=tests/buildings/test-1.ttl --person-file=tests/buildings/test-1.ttl --escape-file=escape.ttl --risk-file=risk.ttl
```

We can also do both of the above in a single command
```
escape_planner --calculate-paths --calculate-risk --building-file=tests/buildings/test-1.ttl --person-file=tests/buildings/test-1.ttl --escape-file=escape.ttl --risk-file=risk.ttl
```
<!-- To calculate the escape paths for *specified* entities in a building
```
escape_planner building_x_architectrue.ttl persons_x_building_x.ttl ex:Alice http://example.org/Bob
``` -->

For more information about commands run
```
escape_planner --help
```

The most relevant commands are as follows

| arg         | Description                                                                                      |
| ----------- | -------------------------------------------------------------------------------------------------|
| c (calculate-paths)          | Calculate and write paths                                                                        |
| r (calculate-risk)          | Calculate and write risk of catching COVID - This can only be called *after* -p has been called  |
| d           | Show timing diagnostics - if no other options are speficied then paths and risk are calcualted                                                           |

If none are specified, `-cr` is run

### If boost package is unavailable

On some systems; the boost library may not be included by default, if this is the case install the `libboost-all-dev`; with the default debain package manager one can run
```
sudo apt-get install libboost-all-dev
```

## Note on testing files

We can compile the test suite as follows

```
g++ -std=c++11 tests/test-generator.cpp -o tests/tests
```

and run the test suite by running

```
tests/tests
```

to output the diagonstics to a file, specify the file to output the diagonsitics to using the `-d` flag.

TODO: Provide some alternatives for IRI's from testing files that can be used to run
TODO: Add information about the size of various testing files - person files etc

## Description
In the event of a fire in a large populated office space during the year 2020, two primary risk factors are present; the risk of burns from the fire, and the risk of COVID-19 transmission as large crowds exit the building en-masse. The company that owns the building has commissioned an app that is to be installed on each employees phone. In the event of a fire within the building, it will tell employees exactly when and where to move so as to exit the office safely whilst minimizing the likelihood of COVID-19 transmission.

## Usage
This software is being developed on Linux machine (SMP Debian 4.19.132-1) in C++11. The 64-bit machine being used has a Intel(R) Core(TM) i5-7200U CPU @ 2.50GHz and has 8GB of RAM. We intend for this software to be run on a Linux machine with at least 2GB of RAM.

## Additional Information
For additonal information see `Milestone_2.pdf` which is included in this repo.

## License
This software is built under the MIT licence. See (LICENSE)[LICENSE] for more information.
