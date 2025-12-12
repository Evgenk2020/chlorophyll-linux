<p align="center">
  <a href="https://github.com/Evgenk2020/chlorophyll-linux/blob/main/LICENSE">
    <img src="https://img.shields.io/github/license/Evgenk2020/chlorophyll-linux" alt="license">
  </a>
  <a href="https://github.com/Evgenk2020/chlorophyll-linux/commits">
    <img src="https://img.shields.io/github/last-commit/Evgenk2020/chlorophyll-linux" alt="last commit">
  </a>
  <a href="https://github.com/Evgenk2020/chlorophyll-linux">
    <img src="https://img.shields.io/github/repo-size/Evgenk2020/chlorophyll-linux" alt="repo size">
  </a>
  <a href="https://github.com/Evgenk2020/chlorophyll-linux/stargazers">
    <img src="https://img.shields.io/github/stars/Evgenk2020/chlorophyll-linux" alt="stars">
  </a>
  <a href="https://github.com/Evgenk2020/chlorophyll-linux/network/members">
    <img src="https://img.shields.io/github/forks/Evgenk2020/chlorophyll-linux" alt="forks">
  </a>
  <a href="https://github.com/Evgenk2020/chlorophyll-linux">
    <img src="https://img.shields.io/github/languages/top/Evgenk2020/chlorophyll-linux" alt="top language">
  </a>
  <a href="https://github.com/Evgenk2020/chlorophyll-linux/releases">
    <img src="https://img.shields.io/github/v/release/Evgenk2020/chlorophyll-linux" alt="latest release">
  </a>
  <!-- Added version badge -->
  <a href="https://github.com/Evgenk2020/chlorophyll-linux">
    <img src="https://img.shields.io/badge/version-1.0.1-blue" alt="version">
  </a>
</p>

# Chlorophyll A and B maintenance

Lab utility for determining the maintenance of chlorophylls A and B in plant material
  
Run it with specified keys

```

chloro -d | -df [data...]

```

Using `-df` key you may write data to `*.csv` file for the next importing to LibreOffice Calc, MS Excell or Google Tables

![Google table data import](/.img/screen.png)

.sh file example to run in terminal

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

git clone https://github.com/Evgenk2020/chlorophyll-linux

cd chlorophyll-linux

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

Then run `chloro -d | -df [data...]` in terminal from unpacked folder.

For more convenience you may add path to the application into `.bashrc` file

```SH

export PATH=$PATH:/%path_to_application_folder%/

```

In this case it will be possible to run `chloro -d | -df [data...]` in terminal directly.
