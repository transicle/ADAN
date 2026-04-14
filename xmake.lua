set_languages("c++23")

target("test")
    set_kind("binary")

    add_files("src/**.cpp")
    add_headerfiles("src/**.h", "src/**.hpp")