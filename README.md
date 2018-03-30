# ByteOS

A simple hobby operating system for the x86_64 architecture, written in C.

![Screenshot](https://i.gyazo.com/cbd3707fdcc2e3e01776f62399c53a1b.png)

The design is heavily influenced by the Linux kernel, and as such you may find many similarities between the two.

This repository is licensed under the GPLv3. See `LICENSE.md` for more details.

If you have questions, you can open an issue on GitHub or find me on the [OSDev Discord](https://discord.gg/5TCadrT).

## Building

You will need:
* GNU `binutils` for `x86_64-elf`
* `gcc` for `x86_64-elf` with `-mno-red-zone` and C11 capabilities ([instructions](http://wiki.osdev.org/Libgcc_without_red_zone))
* Make
* NASM
* GRUB 2.02 (Multiboot2 compatible - may need to build from source)

Then, to build `byteos.iso`, simply run:
```sh
make
```

## Running

You will need (in addition to the above dependencies):
* QEMU `x86_64`

Then, to run in QEMU:
```sh
make run
```

## Debugging

Debugging requires a [specially patched version of GDB](http://wiki.osdev.org/QEMU_and_GDB_in_long_mode#Workaround_2%3A_Patching_GDB) for interoperability with QEMU. Once you have this installed, simply run the `debug` make target.

## Testing

First run the `update-modules` make target to download the necessary files. Then, simply run `make test`.

See [`Makefile`](https://github.com/64/ByteOS/blob/master/Makefile) for more details.

## Contributing

Feel free to open an issue if you have any questions/concerns or a pull-request if you would like to contribute some code.

Special thanks to [no92](https://github.com/no92) for massively cleaning up the build system.
