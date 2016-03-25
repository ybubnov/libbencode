# libbencode - The Bencode coding library

The Bencode library is an elementary template-based implementation of the data serialization into the Bencode format. The Bencode format is commonly used in the [BitTorrent](https://wiki.theory.org/BitTorrentSpecification) protocol to encode the metadata of torrents.

## Installation

The build mechanism of the library is based on the [CMake](https://cmake.org) tool. It could be either compiled from sources or installed from the distribution repository (e.g. for debian-based systems):
```bash
$ sudo apt-get install cmake
```

To keep the source tree clean, it would be good to create a separate folder were all compiled binaries and generated makefiles will reside:
```bash
$ mkdir build
```

As the directory created, all required build scripts will be generated inside by executing the following commands:
```bash
$ cd build
$ cmake ..
```

After successful scripts generation, the library could be compiled and optionally tested.
```bash
$ make
$ make test
```

By default library will be installed into the ```/usr/local``` directory. The destination path could be changed by specifying the ```-DCMAKE_INSTALL_PREFIX``` attribute on the step of makefile generation:
```bash
$ cmake -DCMAKE_INSTALL_PREFIX=/usr ..
```

The library consits only of the headers file, therefore the installation does not require any source code compilation:
```
$ make install
```

Optionally, the destination path could be overridden with ```DESTDIR``` environment variable:
```
$ make DESTDIR=/opt install
```

## Usage

### Examples

The usage is pretty straightforward. Here is an example of dictionary and a list creation:
```cpp
// Create an associative array of Bencode values.
bencode::dict d;

d["port wine"] = bencode::make_integer(777);
d["green"] = bencode::make_string("elephant");

// Create a 2-elements list of Bencode values.
bencode::list l(2);

l[0] = bencode::make_string("worsening");
l[1] = bencode::make_string("retaliation");
```

### Input-output stream

The library provides input and output classes derived from ```std::basic_istream``` and ```std::basic_ostream``` prespectively to perform the handfull values serialization.
```cpp
// Create a new Bencode output stream
bencode::ostream os(std::cout.rdbuf());

// Create a new Bencode value
bencode::string s("a string");

// output: `8:a string`
os << s;
```

### User-defined operators

To create polimorphic shared pointers to the Bencode values, the syntax of string literals could be used:
```cpp
// Create a bencode string.
auto s = "6:string"_bencode;

// Create a bencode integer.
auto i = "i777e"_bencode;

// Create a bencode list.
auto l = "li1ei2ei3ee"_bencode;

// Create a bencode dictionary.
auto d = "d5:first:i1e6:second:i2ee"_bencode;
```

## License

The Bencode library is distributed under MIT license, therefore you are free to do with code whatever you want. See the [LICENSE](LICENSE) file for full license text.
