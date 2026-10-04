import pathlib, shutil, subprocess, tempfile, unittest
ROOT = pathlib.Path(__file__).resolve().parents[1]
class LinkedListTests(unittest.TestCase):
    def test_student_owns_copies_of_input_strings(self):
        with tempfile.TemporaryDirectory() as directory:
            path = pathlib.Path(directory)
            (path/'test.c').write_text('#include <assert.h>\n#include <stdlib.h>\n#include <string.h>\n#include "mylinkedlist.h"\nint main(void) {\n    char id[] = "ABC001", name[] = "Example Student";\n    student_cell_T *cell = NewStudentCell(id, 3.0, name);\n    assert(cell != NULL);\n    id[0] = \'Z\'; name[0] = \'Z\';\n    assert(strcmp(cell->id, "ABC001") == 0);\n    assert(strcmp(cell->name, "Example Student") == 0);\n    free(cell->id); free(cell->name); free(cell);\n    return 0;\n}\n')
            program = path/'test.exe'
            subprocess.run([shutil.which('gcc'), '-std=c11', '-Werror=implicit-function-declaration', '-I', str(ROOT/'linked-list-refresh'), str(path/'test.c'), str(ROOT/'linked-list-refresh/mylinkedlist.c'), '-o', str(program)], check=True)
            subprocess.run([str(program)], check=True, timeout=5)
