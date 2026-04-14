{
    files = {
        "src/main.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-std=c++23"
        }
    },
    depfiles_gcc = "main.o: src/main.cpp\
"
}