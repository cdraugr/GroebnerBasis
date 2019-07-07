#!/usr/bin/env python3
import argparse
import os
import subprocess


def compile_one(absolute_path):
    executable_absolute_path = absolute_path.rsplit('.', 1)[0] + ".out"
    print(f">>> compiling {format(os.path.basename(absolute_path))}")
    try:
        subprocess.run([
            "g++", "-std=c++17", "-Wall", "-Werror", "-Wextra",
            absolute_path, "-o", executable_absolute_path,
            "-fsanitize=address"
        ]).check_returncode()
    except subprocess.CalledProcessError:
        return 1
    return 0


def run_one(absolute_path):
    run_absolute_path = absolute_path.rsplit('.', 1)[0] + ".out"
    print(f">>> running {format(os.path.basename(run_absolute_path))}")
    run_absolute_path = "./" + run_absolute_path
    subprocess.run([
            run_absolute_path
    ])


def compile_all(directory):
    for path in os.listdir(directory):
        if path.endswith(".cpp"):
            compile_one(os.path.join(directory, path))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("path", default='.')
    args = parser.parse_args()
    if args.path.endswith(".cpp"):
        if not compile_one(args.path):
            run_one(args.path)
    else:
        compile_all(args.path)


if __name__ == "__main__":
    main()

