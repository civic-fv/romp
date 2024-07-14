#! /usr/bin/env python3

_debug = False

if _debug:
    import sys

    def dprint(s: str) -> None:
        print(s, file = sys.stderr)
else:
    def dprint(s: str) -> None:
        pass


def main(argv: list[str]) -> int:
    for filename in argv[1:]:
        dprint(f"Fixing {filename}...")

        with open(filename, 'r') as f:
            text = f.read()

        text = '\n'.join(map(str.rstrip, text.splitlines()))

        with open(filename, 'w') as f:
            f.write(text)

    return 0

if __name__ == '__main__':
    from sys import argv
    exit(main(argv))
