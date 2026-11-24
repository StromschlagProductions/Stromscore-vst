"""Read the headers belonging to a pinned revision, not today's source-file list."""
import subprocess

def header_snapshot(root, revision):
    if revision is None:
        return {p.name:p.read_bytes() for p in (root/'Source').glob('*.h')}
    names=subprocess.check_output(['git','ls-tree','--name-only',revision+':Source'],cwd=root).decode().splitlines()
    return {name:subprocess.check_output(['git','show',revision+':Source/'+name],cwd=root) for name in names if name.endswith('.h')}
