## dicethrow - Generate random numbers seeded with dice throws

This is the README file for dicethrow.

## Documentation

You can read the documentation without installing the
software:

    perldoc dicethrow.pod

If it is already installed, you can read the manual page:

    man dicethrow

## Installation

This software doesn't have any external dependencies, but
you need either BSD make or GNU make installed to build it.

First you need to check out the source code. Skip this, if
you have already done so:

    git clone git@github.com:TLINDEN/dicethrow.git

Next, change into the newly created directory 'dicethrow' and
compile the source code:

    cd dicethrow
    make

To install, type this command:

    sudo make install

This will install the binary to `$PREFIX/sbin/dicethrow` and
the manual page to `$PREFIX/man/man1/dicethrow.1`. You can
modify `$PREFIX` during installation time like this:

   make install PREFIX=/opt

If you want to install it somewhere without root privileges,
try this:

   make install PREFIX=$HOME/usr UID=bob GID=users

## Usage

    Usage: dice [-tcfvhd]
    Options: 
    -t --humantoss            Asks interactively for rolled dices
    -c --count <count>        Number of numbers (default: 4)
    -f --randfile <randfile>  Random source to use (default:
                              /dev/urandom)
    -l --minlen <count>       Minimum number (default: 1)
    -m --maxlen <count>       Maximum number (default: 256)
    -d --debug                Enable debug output
    -v --version              Print program version
    -h -? --help              Print this help screen

If you want to generate truly random numbers, use
the option -t. In that case you have to roll physical dices and
enter the results (dicethrow will ask you for them).

## Getting help

Although I'm happy to hear from dicethrow users in private email,
that's the best way for me to forget to do something.

In order to report a bug, unexpected behavior, feature requests
or to submit a patch, please open an issue on github:
https://github.com/TLINDEN/diceware/issues.

## License

This software is licensed under the GNU GENERAL PUBLIC LICENSE version 3.

## Author

T.v.Dein <tom AT vondein DOT org>

## Project homepage

https://github.com/TLINDEN/diceware
