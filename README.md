# Network Duplication detection

The current one is a practice project. The goal is to find the duplications in the [network data](./data/network_utf8.csv).

_Note_: The original file is saved as [original_network.csv](./data/original_network.csv). However it is encoded with windows' encoding which means on linux I saw � symbols. \
Therefore I used the `iconv -f ISO-8859-1 -t UTF-8 original_network.csv -o network_utf8.csv` command.

## Build

```bash
cmake -S . -B build && \
cmake --build build
```

## Test

For testing I used [google test](https://google.github.io/googletest/). It can be executed with the command:

```bash
ctest --test-dir build --output-on-failure
```

## Run

```bash
./build/network_duplication
```
