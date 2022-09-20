# c-hot-reload
C auto compile and execute

## How to build
```
cc main.c -o tool
```
or
```
make build
```
than mv the tool to the directory of the file. In this case
```
cd examples
./tool example.c
```

Each time example.c is changed and saved it will recompile and run the program.

## Known limitations

Not yet implemented argument passing to the hot reload tool. The program that it hot reloads cannot have any arguments yet.
Not yet implemented safety checks. Does minimal (mem) safety checks
