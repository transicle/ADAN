mod lexer;
mod tokens;

use lexer::Lexer;
use std::fs;
use clap::Parser;

const COMPILER_VERSION: &str = "version-1.0.2";

#[derive(Parser, Debug)]
#[command(
    about = "The ADAN programming language compiler.",
    long_about = None,
    disable_help_flag = true,
    disable_version_flag = true,
)]
struct Args {
    #[arg(required_unless_present_any = ["help", "version"])]
    filepath: Option<String>,

    #[arg(short = 'h', long = "help", action = clap::ArgAction::SetTrue)]
    help: bool,

    #[arg(short = 'v', long = "version", action = clap::ArgAction::SetTrue)]
    version: bool,
}

fn main() {
    let args = match Args::try_parse() {
        Ok(parsed_args) => parsed_args,
        Err(error) => {
            if error.kind() == clap::error::ErrorKind::MissingRequiredArgument {
                show_main_message();
                std::process::exit(1);
            }

            error.exit();
        }
    };

    if args.help {
        show_main_message();
    }

    if args.version {
        println!("Compiler on {}\n", COMPILER_VERSION);
    }

    let filepath = match args.filepath {
        Some(path) => path,
        None => {
            show_main_message();
            std::process::exit(1);
        }
    };

    let source = match fs::read_to_string(&filepath) {
        Ok(content) => content,
        Err(error) => {
            eprintln!("Couldn't read file: \"{}\": {}", filepath, error);
            std::process::exit(1);
        }
    };

    let mut lexer = Lexer::new(source.as_str());

    let tokens = lexer.lex();
    for token in &tokens {
        println!("{:?}", token);
    }
}

fn show_main_message() {
    println!(
        "\x1b[1mUsage:\x1b[0m adan \x1b[2m[options]\x1b[0m <file>
    
\x1b[1mArguments:\x1b[0m
    \x1b[32m--version\x1b[0m, \x1b[32m-v\x1b[0m     Get your version of ADAN that's on your machine.
    \x1b[32m--help\x1b[0m, \x1b[32m-h\x1b[0m        Display this message.
    
ADAN is in BETA and is a passion project of mine.

Support the development of ADAN by starring the
repository over on GitHub!

  ➤  \x1b[1;3;34mhttps://github.adan.sh/\x1b[0m

For reporting a bug, please create a new issue on GitHub.\n"
    );
}
