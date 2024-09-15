# Chlorophyll A and B maintenance

Lab utility for determining the maintenance of chlorophylls A and B in plant material
  
Run it with specified keys

```
  
chloro -d [mass (g)] [filtrate (ml)] [photoprobe (ml)] [solvent (ml)] [D 665] [D 649]
chloro -df [mass (g)] [filtrate (ml)] [photoprobe (ml)] [solvent (ml)] [D 665] [D 649]

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


echo "measurement 1"
chloro -d 1 25 3 1 1.256 0.8
echo ""

echo "measurement 2"
chloro -d 1.5 25 3 1 1.1 0.7
echo ""

exec $SHELL

```

or for writing `.csv` use

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
