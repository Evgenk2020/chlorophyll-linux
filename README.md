# Chlorophylls

Lab utility for determining the maintenance of chlorophylls A and B in plant material
  
Run it with specified keys

```
  
chloro -d [mass_g] [filtrate_ml] [photoprobe_ml] [solvent_ml] [D_665] [D_649]

```

Using `-df` key you may write data to `*.csv` file for the next importing to LibreOffice Calc, MS Excell or Google Tables

![Google table data import](/img/screen.png)

Use `build.sh` and `run.sh` from the `src` folder to compile and run the application

For more convenience you may add path to the application into `.bashrc` file

```

export PATH=$PATH:/%path_to_application_folder%/

```

and then use simple SH schemes e.g.

```SH

#!/bin/bash


echo "вариант 1"
chloro -d 1 25 3 1 1.256 0.8
echo ""

echo "вариант 2"
chloro -d 1.5 25 3 1 1.1 0.7
echo ""

echo "вариант 3"
chloro -d 1.3 25 3 1 0.9 0.6
echo ""

echo "вариант 4"
chloro -d 2 25 3 1 0.965 0.65
echo ""

echo "вариант 5"
chloro -d 1.5 25 3 1 1.025 0.6
echo ""

echo "вариант 6"
chloro -d 1.5 25 3 1 0.984 0.625

exec $SHELL

```

or for writing `chlor-dada.csv` use

```SH

#!/bin/bash

chloro -df 1 25 3 1 1.256 0.8
chloro -df 1.5 25 3 1 1.1 0.7
chloro -df 1.3 25 3 1 0.9 0.6
chloro -df 2 25 3 1 0.965 0.65
chloro -df 1.5 25 3 1 1.025 0.6
chloro -df 1.5 25 3 1 0.984 0.625

exec $SHELL

```

This program runs with `uk_UA.utf8` locale. It can be changed in `output.cpp`

```C++

std::locale m_loc("uk_UA.utf8");

```

To see locale list use

```SH

locale -a

```
