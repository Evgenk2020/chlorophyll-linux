# Statistical analysis of variance

This tool is designed for processing data sets that include more than two distinct variants, including cases with partial overlap. By default, it evaluates confidence intervals using the Student's t-test at a significance level of 0.05. This threshold can be adjusted to accommodate different precision requirements.

Run it with specified keys

```

stexp -d | -df [data...] [alf (0 <...< 1)]

```

Using `-df` key you may write data to `*.csv` file for the next importing to LibreOffice Calc, MS Excell or Google Tables

![Google table data import](/.img/screen.png)

.sh file example for running in terminal

```SH

#!/bin/bash

stexp -d 2.3 3.4 2.6 3.5
echo "----------------"
stexp -d 2.5 3.4 2.6 -- 8.9 11.2 13.5
echo "----------------"
stexp -d 2.3 3.4 2.6 3.5 alf 0.01
echo "----------------"
stexp -d 2.5 3.4 2.6 -- 8.9 11.2 13.5 alf 0.2

exec $SHELL

```

.sh file example for writing to `.csv`

```SH

#!/bin/bash

stexp -df 2.3 3.4 2.6 3.5
echo "----------------"
stexp -df 2.5 3.4 2.6 -- 8.9 11.2 13.5
echo "----------------"
stexp -df 2.3 3.4 2.6 3.5 alf 0.01
echo "----------------"
stexp -df 2.5 3.4 2.6 -- 8.9 11.2 13.5 alf 0.2

exec $SHELL

```

<hr>

> You need
> <br>
> [CMake](https://cmake.org/)
> <br>
> to be installed on your Linux system previously

<hr>

<b>To compile and run the utility</b>

1. Clone the Repository

```SH

git clone https://github.com/Evgenk2020/student-experiment

cd student-experiment

```

2. Check for `rpm-build` package to be installed in your system

```SH

rpm -q rpm-build

```

If so you will see `rpm-build-6.0.0-1.fc43.x86_64` or something like that.

If not it will be `package rpm-build is not installed`. Then install it from system repository

```SH

sudo dnf install rpm-build

```

3. Build the Project with `.rpm` setup package for Fedora/CentOS Stream by default

```SH

./build.sh

```

4. Install `.rpm` package from build folder

```SH

sudo dnf install *.rpm

```

If using either than Fedora/CentOS Stream change the first string `set(assemble_tgz OFF)` in CMakeLists.txt to `set(assemble_tgz ON)` before building the Project. Move `.tar.gz` file to any folder and unpack it.

Then run `./stexp -d | -df [data...] [alf (0 < alf <1)]` in terminal from unpacked folder.

For more convenience you may add path to the application into `.bashrc` file

```SH

export PATH=$PATH:/%path_to_application_folder%/


```

In this case it will be possible to run `stexp -d | -df [data...] [alf (0 < alf <1)]` in terminal directly.
