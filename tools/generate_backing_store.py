"""Create a clearly synthetic 256-page backing store for the educational simulator."""
import argparse
import pathlib
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--output', type=pathlib.Path, default=pathlib.Path(__file__).resolve().parents[1] / 'virtual-memory-lru/BACKING_STORE.bin')
args = parser.parse_args()
args.output.parent.mkdir(parents=True, exist_ok=True)
args.output.write_bytes(bytes((page * 7 + offset * 3) % 256 for page in range(256) for offset in range(256)))
print('Created synthetic backing store: 65536 bytes.')
