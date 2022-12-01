import glob, pathlib, shutil
import os

CURRENT = pathlib.Path(__file__).resolve().parent

patterns = ["debug", "release", "Makefile*", ".qmake.stash", ".qtc_clangd"]
files = []

for pattern in patterns:
    pattern_files = glob.glob(f"**/{pattern}", recursive=True, root_dir=CURRENT)
    files.extend(pattern_files)

file_paths: list[pathlib.Path] = []

for file in files:
    file_paths.append(CURRENT.joinpath(file))

for file_path in file_paths:
    if file_path.is_dir():
        shutil.rmtree(str(file_path))
    elif file_path.is_file():
        os.remove(str(file_path))
