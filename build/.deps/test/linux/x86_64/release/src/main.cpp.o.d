{
    files = {
        "src/main.cpp"
    },
    values = {
        "/usr/bin/g++",
        {
            "-m64",
            "-std=c++23"
        }
    },
    depfiles_format = "gcc",
    depfiles = "main.o: src/main.cpp\
"
}