from tools import mk
import os

os.environ["DESTDIR"] = "D:/DevFiles/build"
os.environ["CC"] = "clang.exe -target x86_64-pc-windows-gnu"
os.environ["CXX"] = "clang++.exe -target x86_64-pc-windows-gnu"
mk.setconfigpath("D:/DevFiles/build")

app = mk.project(__file__)
app.clean()
app.execute("meson build -Dbuildtype=plain")
app.execute("ninja -C build")
app.execute("ninja -C build install")


