# Linux Kernel Hook
This is just a small project to hook syscalls in an x86_64 Linux kernel.

Most of the other kernel hooks I've seen on the public internet use an outdated mechanism to grab the syscall table - the oldest tutorials relied on `sys_call_table` being exported as a public symbol, and slightly newer ones had a brute-forcing approach where they would try to find the syscall table in between two different symbols. This one doesn't do anything that fancy - the `load.sh` script just greps `/proc/kallsyms` for the syscall table addresses.

## Usage

```bash
make
sudo ./scripts/load.sh
```
