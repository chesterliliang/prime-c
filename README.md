# How to get started with the code
## 1.Directory struct
```
.
|--src
    |--core //logic code to access the module.
    |--platform //uart api on diff platform
|--doc //necessary docs
|--tools //tools for test
|--test //test vectors
|--readme.md

```

## 2.Build
```
git clone https://github.com/chesterliliang/prime-c-lib.git

make
```

If you can run the code binary on you platform, here is the reference:
```
./prime
```
or you may need sudo to aceess uart
```
sudo ./prime
```
Check UART device on Linux and OSX
```
dmesg | grep tty.S*
ls /dev/tty.S*
```
## 3. Trouble Shooting

Submit issues on github.
