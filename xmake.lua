set_languages("c++23")

target("adn")
    set_kind("binary")
    add_files("src/**.cpp")

task("test")
    set_menu {
        usage = "xmake test"
    }
    on_run(function ()
        local current_dir = os.curdir()
        local input = path.join(current_dir, "examples", "test.adn")
        
        os.exec("xmake build -v adn")
        os.execv("xmake", { "run", "adn", input })
    end)