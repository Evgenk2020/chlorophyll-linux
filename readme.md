[![Version](https://img.shields.io/badge/version-1.0.4-blue)](https://github.com/Evgenk2020/chlorophyll-linux)
[![Latest Release](https://img.shields.io/github/v/release/Evgenk2020/chlorophyll-linux)](https://github.com/Evgenk2020/chlorophyll-linux/releases)
[![License](https://img.shields.io/github/license/Evgenk2020/chlorophyll-linux)](https://github.com/Evgenk2020/chlorophyll-linux/blob/main/LICENSE)
[![Last Commit](https://img.shields.io/github/last-commit/Evgenk2020/chlorophyll-linux)](https://github.com/Evgenk2020/chlorophyll-linux/commits)
[![Repo Size](https://img.shields.io/github/repo-size/Evgenk2020/chlorophyll-linux)](https://github.com/Evgenk2020/chlorophyll-linux)
[![Stars](https://img.shields.io/github/stars/Evgenk2020/chlorophyll-linux)](https://github.com/Evgenk2020/chlorophyll-linux/stargazers)
[![Forks](https://img.shields.io/github/forks/Evgenk2020/chlorophyll-linux)](https://github.com/Evgenk2020/chlorophyll-linux/network/members)
[![Top Language](https://img.shields.io/github/languages/top/Evgenk2020/chlorophyll-linux)](https://github.com/Evgenk2020/chlorophyll-linux)


# 🌿 Chlorophyll A and B maintenance

Lab utility for determining the maintenance of chlorophylls A and B in plant material

Run it in interactive mode

```

chloro

```
  
or run it with specified keys

```

chloro [options] -w <weight> -f <filt> -p <prob> -s <solv> --d665 <value> --d649 <value>

```

Using `-df` key you may write data to `*.csv` file for the next importing to LibreOffice Calc, MS Excell or Google Tables

![Google table data import](/.img/screen.png)

.sh file example to run in terminal

```SH

#!/bin/bash

echo "measurement 1"
chloro -w 1.3 -f 25 -p 3 -s 5 --d665 1.25 --d649 0.45
echo ""

echo "measurement 2"
chloro -w 1 -f 25 -p 3 -s 5 --d665 1.1 --d649 0.41
echo ""

exec $SHELL

```

.sh file example for writing to `.csv`

```SH

#!/bin/bash

chloro -w 1 -f 25 -p 3 -s 1 --d665 1.256 --d649 0.8 -df
chloro -w 1.5 -f 25 -p 3 -s 1 --d665 1.1 --d649 0.7 -df
chloro -w 1.3 -f 25 -p 3 -s 1 --d665 0.9 --d649 0.6 -df
chloro -w 2 -f 25 -p 3 -s 1 --d665 0.965 --d649 0.65 -df
chloro -w 1.5 -f 25 -p 3 -s 1 --d665 1.025 --d649 0.6 -df
chloro -w 1.5 -f 25 -p 3 -s 1 --d665 0.984 --d649 0.625 -df

exec $SHELL

```
<hr>

## 🛠 Dependencies

To build the project from source, you will need:
* A compiler with full **C++23** support (GCC >= 14, verified with GCC 16)
* **CMake** (>= 3.31)
* **RapidJSON** - a fast, header-only JSON parser and generator library
* **rpm-build** - for Fedora/CentOS Stream

## On Fedora based systems run

```SH

sudo dnf group install development-tools
sudo dnf install cmake rpm-build rapidjson-devel

```

## On Debian based systems run

```SH

sudo apt update
sudo apt install build-essential cmake rapidjson-dev

```

On other systems see the details of your distro

<hr>

## To compile and run the utility (Fedora/CentOS Stream)

1. Clone the Repository

```SH

git clone https://github.com/Evgenk2020/chlorophyll-linux
cd chlorophyll-linux

```

2. Build the Project with `.rpm` setup package for Fedora/CentOS Stream by default

```SH

./build.sh
cd build

```

3. Install `.rpm` package from build folder

```SH

sudo dnf install *.rpm

```

4. Run the application in terminal directly

```SH

chloro -h

```

<hr>

## If using other than Fedora/CentOS Stream

1. Clone the Repository

```SH

git clone https://github.com/Evgenk2020/chlorophyll-linux
cd chlorophyll-linux

```

2. Change the string `set(assemble_tgz OFF)` to `set(assemble_tgz ON)` in CMakeLists.txt

```SH

nano CMakeLists.txt

```

3. Build the Project

```SH

./build.sh

```

4. Move `.tar.gz` file from `build` folder to any folder and unpack it

5. Run the program to check it from unpacked folder

```SH

./chloro -h

```

For more convenience add the application path into `.bashrc` file

```SH

export PATH="$PATH:/path/to/application/folder"

```

This will allow you to run the application in terminal directly

```SH

chloro -h

```

<hr>

## 📑 Citation & Academic Use

If you use this utility or code in your scientific research, lab analysis, or publications, please cite it using the following format. 

GitHub automatically parses the `CITATION.cff` file, so you can easily copy the citation in **APA** or **BibTeX** format directly from the repository sidebar (look for the **"Cite this repository"** button).

### BibTeX Format
```bibtex
@software{chlorophyll_linux_2026,
  author       = {Kopilov, Evheny},
  title        = {chlorophyll-linux: Chlorophyll A and B determination for laboratory analysis},
  month        = may,
  year         = 2026,
  publisher    = {GitHub},
  version      = {1.0.4},
  url          = {https://github.com/Evgenk2020/chlorophyll-linux}
}