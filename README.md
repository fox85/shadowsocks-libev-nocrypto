# shadowsocks-libev-nocrypto with eBPF dataplane

This is a fork for the pupular proxifier software [shadowsocks-libev](https://github.com/shadowsocks/shadowsocks-libev) with eBPF kernel space socket redirector. This feature save some CPU resource and speed up the connection by avoiding packet copies between kernelspace and userspace.

## Important notes
* Encryption not work. Thats because the functionality built on top of kernel eBPF virtual machine. This is a VM with restricted instruction set and limited amount of helper calls, without encryption functions.
* Performance/functionality issues possible on some platform. eBPF is under active development, the sockmap/sk_redirect support [fairly new](https://lwn.net/Articles/731133/) and more bugfixes will be coming.
* For instrument the software at least **4.14** kernel version required. The latest subpatch version highly recommended, because of the backported bugfixes. Compile the kernel with BPF support, including `CONFIG_BPF_STREAM_PARSER=y` in the `.config`

## Building
Over the regular building method described [here](https://github.com/SPYFF/shadowsocks-libev-nocrypto) some additional steps required.

#### Install **libbpf** dependency
```
#Get the source of your kernel version
$ cd linux/tools/lib/bpf
$ make
$ make install
$ make install_headers
$ sudo cp libbpf.h /usr/local/include/bpf/
```

After that you can install other dependencies and build the software as usual. There are two files: `sockmap_parse.o.ebpf` and `sockmap_verdict.o.ebpf`. These are precompiled eBPF object files, required by `ss-redir`. The source code of these files also included (`sockmap_parse.c` and `sockmap_redir.c`) so if you can compile them if you dont trust these binaries. But I didn't want to add **clang** compiler as a dependency. 

## Usage
Run `ss-redir` as usual, but include `--ebpf` flag as argument, or `"ebpf" : "1"` into the config file. **Important**: if you install `ss-redir` somewhere else like `/usr/bin` or so, you should copy `sockmap_parse.o.ebpf` and `sockmap_verdict.o.ebpf` files to the same directory. **TODO: fix this issue by including the bytecode of the object files into the redir.c source file**
