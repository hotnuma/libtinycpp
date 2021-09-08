#!/usr/bin/bash

#os.environ["DESTDIR"] = "D:/DevFiles/build"
#mk.setconfigpath("D:/DevFiles/build")

meson build -Dbuildtype=plain
ninja -C build
sudo ninja -C build install


