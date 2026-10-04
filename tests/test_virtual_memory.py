import pathlib
import shutil
import subprocess
import tempfile
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]

class VirtualMemoryTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.directory = tempfile.TemporaryDirectory()
        cls.root = pathlib.Path(cls.directory.name)
        cls.program = cls.root / 'simulator.exe'
        subprocess.run([shutil.which('gcc'), str(ROOT / 'virtual-memory-lru/main.c'), '-o', str(cls.program)], check=True)
    @classmethod
    def tearDownClass(cls):
        cls.directory.cleanup()
    def run_simulator(self, addresses, store=None):
        (self.root / 'addresses.txt').write_text(addresses)
        (self.root / 'BACKING_STORE.bin').write_bytes(store if store is not None else bytes((p*7+o*3)%256 for p in range(256) for o in range(256)))
        return subprocess.run([str(self.program)], cwd=self.root, capture_output=True, text=True, timeout=5)
    def test_repeated_page_and_short_input(self):
        result = self.run_simulator('0\n256\n0\n')
        self.assertEqual(result.returncode, 0, result.stderr)
        report = (self.root / 'output_report.txt').read_text()
        self.assertIn('Total Page Faults: 2', report)
        self.assertIn('Value: 7', report)
        self.assertNotIn('Page Table Snapshot', report)
    def test_invalid_empty_or_out_of_range_input_fails(self):
        for addresses in ('', 'invalid', '-1', '65536'):
            with self.subTest(addresses=addresses):
                self.assertNotEqual(self.run_simulator(addresses).returncode, 0)
    def test_truncated_backing_store_fails(self):
        self.assertNotEqual(self.run_simulator('256', b'short').returncode, 0)
