# c4ev3

C/C++ for EV3. Improved from [https://github.com/c4ev3](c4ev3).

### Installation

- Get the toolchain from [https://github.com/c4ev3/C4EV3.Toolchain/releases](https://github.com/c4ev3/C4EV3.Toolchain/releases)
- Go ahead and unpack it, then keep it somewhere. You may want to `export PATH='path/to/bin'` directly to the bin folder to be able to easily call the compilers.
- Link the entire `path/to/toolchain/arm-linux` folder to `/opt/cross/arm-linux` if on macOS, (unconfirmed for linux).
- Clone ev3duder from `git clone https://github.com/c4ev3/ev3duder.git`, and then `cd` into the directory and do `git submodule init`
- Go into `ev3duder/EV3-API/API`
- Update the Make file to not use Windows hardcoding.
- run `make`.

### Usage

either: 

- Use the `ev3build`, `ev3buildUpload` or `ev3Upload` scripts.

or:

- To compile your code, run `arm-none-linux-gnueabi-g++ "path/to/cpp-file" -L"path/to/EV3-API/API/" -lev3api -I"path/to/EV3-API/API/" -static -s -Os -o "path/to/binary"`.

- To upload and run your code, use the `ev3duder` binary from `ev3duder` repo.

```
$NAME="helloworld"  #project name

#Upload
ev3duder exec "rm -r ../prjs/$NAME/"                         # remove existing project if it exists
ev3duder up   "local/path/to/binary" "../prjs/$NAME/$NAME"   # copy binary to ev3
ev3duder mkrbf "../prjs/$NAME/$NAME" "$NAME.rbf"             # make a rbf file and copy it to local storage
ev3duder up "$NAME.rbf" "../prjs/$NAME/$NAME.rbf"            # upload the rbf file

#Run
ev3duder run "../prjs/$NAME/$NAME.rbf"
```
